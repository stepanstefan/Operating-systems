
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

int main(int n, char ** s)
{

int i, mib[4];
size_t len;
struct kinfo_proc kp;
len = 4;
size_t rss = 0;

	   sysctlnametomib("kern.proc.pid", mib, &len);
        for (int i = 0; i < 100000; ++i){
                 mib[3] = i;
		   len = sizeof(kp);
		   if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1)
			   continue;
		   else	if (len	> 0)
            rss += kp.ki_rssize;
        }
        std::cout << rss;

	   for (i = 0; i < 100000;	i++) {
		   mib[3] = i;
		   len = sizeof(kp);
		   if (sysctl(mib, 4, &kp, &len, NULL, 0) == -1)
			   continue;
		   else	if (len	> 0)
			   std::cout
                    << "ID: " << kp.ki_pid << " "
                    << "%CPU: " << (double)kp.ki_pctcpu/100 << " "
                    << "COMMAND: " << kp.ki_comm << " "
                    << "%MEMORY: " << ((double)kp.ki_rssize/(double)rss*100) << " "
                    << "\n";
	   }
}
