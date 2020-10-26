#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <signal.h>



struct memory{
char buff[100000];
int status, pid1, pid2;
};
struct memory* shmptr;
int f = open("log.txt", O_WRONLY | O_APPEND);
void handler(int sig){

write(f,shmptr->buff,strlen(shmptr->buff));
}

int main() {


    int pid = getpid();

    const char* name = "/shmem";
    int shmfd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shmfd, 400000);
    shmptr = (struct memory*)mmap(0, 400000, PROT_WRITE | PROT_READ, MAP_SHARED, shmfd, 0);

    shmptr->pid2 = pid;

    int signo;
    signal(SIGUSR1, handler);
    while(true) {}



}
