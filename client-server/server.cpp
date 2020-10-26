#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include "erproc.h"
#include <sys/wait.h>
#include <string.h>
#include <cerrno>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>

#define BFSIZE 10000

struct memory{
char buff[BFSIZE];
int pid2;
};
struct memory* shmptr;

void daemonize() {
    pid_t pid;

    switch(pid = fork()) {
        case 0:
            setsid();
            break;
        case -1:
            perror("Failed to fork daemon\n");
            exit(1);
        default:
            exit(0);
    }
}

int main() {

    daemonize();

    //create server
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34535);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 1);
    socklen_t adrlen = sizeof adr;
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);

    //create shared memory
    const char* name = "/shmem";
    int shmfd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shmfd, 400000);
    shmptr = (struct memory*)mmap(0, 400000, PROT_WRITE | PROT_READ, MAP_SHARED, shmfd, 0);

    char buff[BFSIZE];
    memset(buff, 0, sizeof(buff));
    char mes[256];
    char** amd;

    pid_t loggerPid = fork();

    if (loggerPid == 0) {
            setsid();
            execl("log", "log", (char*)NULL);
    } else if (loggerPid < 0) {
        exit(EXIT_FAILURE);
    } else {

        sleep(2);

        while(1) {

            int link[2];
            pipe(link);
            memset(buff, 0, sizeof(buff));
            memset(mes, '\0', sizeof(mes));

            ssize_t nread;
            nread = read(fd, mes, 256);

            if (nread == -1) {
                perror("read failed");
                exit(EXIT_FAILURE);
            }
            if (nread == 0) {
                Listen(server, 1);
                fd = Accept(server, (struct sockaddr *) &adr, &adrlen);
                continue;
            }

            pid_t pid = fork();

            if (pid == 0) {
                char* trbuf= trim(mes);
                dup2(link[1], fileno(stdout));
                dup2(link[1], fileno(stderr));
                amd = split(trbuf);
                sprintf(shmptr->buff, "%s", mes);
                kill(shmptr->pid2, SIGUSR1);

                if(strcmp(mes,"sysinfo\n") == 0){
                    execl("sysinfo", "sysinfo", (char*)NULL);
                } else if (strcmp(mes,"ps\n") == 0){
                    execl("ps", "ps", (char*)NULL);
                } else if (strcmp(mes,"procChange\n") == 0){
                    if (fork() == 0){
                        setsid();
                        execl("change", "change", (char*)NULL);
                    }
                } else {
                    execvp(amd[0], (char**)amd);
                }

                write(fileno(stdout),strerror(errno),sizeof(strerror(errno)));
                exit(-1);

            } else {
                wait(NULL);
                read(link[0], buff, sizeof(buff));
                sprintf(shmptr->buff, "%s", buff);
                kill(shmptr->pid2, SIGUSR1);
                write(fd, buff, sizeof(buff));
            }
        }
    }
}
