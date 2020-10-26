
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <cerrno>
#include <iostream>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>
#include <fstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/sysctl.h>
#include <sys/user.h>
#include <pthread.h>


int i, mib[4];
size_t len = 4;
struct kinfo_proc kp;
int f = open("procChange.txt", O_WRONLY | O_APPEND);

void *end_of_procces( void *ptr )
{
    if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1)
        write(f,"Not Found\n",10);
    else if (len > 0) {
        while(true){
            if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1){
                write(f,"Died\n",5);
                break;
            }
            sleep(2);
        }
    }

        pthread_exit(0);

}

void *cpu_check( void *ptr )
{

    if (sysctl(mib, 4, &kp, &len, NULL, 0) > -1){
            int cpu = kp.ki_pctcpu;
        while(true){
            if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1){
                break;
            } else {
                if(kp.ki_pctcpu != cpu){
                    std::string s = "Old cpu: "
                        + std::to_string(cpu)
                        + "  new cpu: "
                        + std::to_string(kp.ki_pctcpu)
                        + "\n";
                    write(f,s.c_str(),s.length());
                    cpu = kp.ki_pctcpu;
                }
            }
            sleep(2);
        }
    }

        pthread_exit(0);

}

void *mem_check( void *ptr )
{

    if (sysctl(mib, 4, &kp, &len, NULL, 0) > -1){
            int mem = kp.ki_rssize;
        while(true){
            if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1){
                break;
            } else {
                if(kp.ki_rssize != mem){
                    std::string s = "Old mem: "
                        + std::to_string(mem)
                        + "  new mem: "
                        + std::to_string(kp.ki_rssize)
                        + "\n";
                    write(f,s.c_str(),s.length());
                    mem = kp.ki_rssize;
                }
            }
            sleep(2);
        }
    }

        pthread_exit(0);

}

int main(){
pthread_t thread1, thread2, thread3;
sysctlnametomib("kern.proc.pid", mib, &len);
mib[3] = 11;
len = sizeof(kp);

int iret1 = pthread_create( &thread1, NULL, end_of_procces, NULL);
int iret2 = pthread_create( &thread2, NULL, cpu_check, NULL);
int iret3 = pthread_create( &thread3, NULL, mem_check, NULL);


pthread_exit(0);

}
