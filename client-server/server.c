#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "erproc.h"
#include <sys/wait.h>
#include <string.h>


int main() {
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34571);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    socklen_t adrlen = sizeof adr;
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);

    int link[2];
    char test[10000];
    char testError[10000];
    memset(test, 0, sizeof(test));
    char buf[256];
    pipe(link);

    while(1) {
        memset(test, 0, sizeof(test));
        memset(buf, '\0', sizeof(buf));
        pid_t pid = fork();

        if (pid == 0) {

            ssize_t nread;
            nread = read(fd, buf, 256);

            if (nread == -1) {
                perror("read failed");
                exit(EXIT_FAILURE);
            }
            if (nread == 0) {
                printf("END OF FILE occured\n");
            }
            printf("%s", buf);
            dup2(link[1], fileno(stdout));
            dup2(link[1], fileno(stderr));
            execl("/bin/sh", "sh", "-c", buf, (char *) NULL);

        } else {
            wait(NULL);
            read(link[0], test, sizeof(test));
            write(fd, test, sizeof(test));

            //wait(NULL);
        }
    }
    return 0;
}
