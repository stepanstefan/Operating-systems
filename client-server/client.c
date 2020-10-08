#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "erproc.h"
#include <string.h>
#include <signal.h>

void sigHandler(int sig) {
    exit(EXIT_FAILURE);
};

int main() {
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34571);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);
    char message[256];
    signal(SIGINT, sigHandler);
    while (1) {
        memset(message, '\0', sizeof(message));
        read(STDIN_FILENO, message, 256);
        if (strlen(trim(message)) == 1) {
            continue;
        }
        write(fd, message, sizeof(message));
        char buf[10000];
        memset(buf, 0, sizeof(buf));
        ssize_t nread;
        nread = read(fd, buf, 10000);
        if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        if (nread == 0) {
            printf("EOF occured\n");
        }
        write(fileno(stdout), buf, nread);
    }
    sleep(10);
    close(fd);
    return 0;
}
