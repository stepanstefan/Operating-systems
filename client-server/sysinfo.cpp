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

int main() {
char str[256] = {0};
size_t size = sizeof(str);
sysctlbyname("hw.machine", str, &size, NULL, 0);
std::cout << "Machine - " << str << '\n';

memset(str, 0, sizeof(str));
size = sizeof(str);
sysctlbyname("hw.model", str, &size, NULL, 0);
std::cout << "Model - " << str << '\n';

long long num[4] = {0, 0, 0, 0};
size = sizeof(num);
sysctlbyname("hw.ncpu", num, &size, NULL, 0);
std::cout << "The number of cpus - " << *num << '\n';

memset(num, 0, sizeof(num));
size = sizeof(num);
sysctlbyname("hw.physmem", num, &size, NULL, 0);
std::cout << "Amount of physical memory - " << *num << '\n';

memset(num, 0, sizeof(num));
size = sizeof(num);
sysctlbyname("hw.usermem", num, &size, NULL, 0);
std::cout << "Amount of memory which is not wired - " << *num << '\n';
}
