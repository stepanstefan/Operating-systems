#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "erproc.h"
#include <string.h>
#include <signal.h>

#define BFSIZE 10000

int fd;

void sigHandler(int sig) {

    printf("%c",'\n');
    close(fd);
    exit(EXIT_FAILURE);
};

void sigExit(int sig) {
    exit(EXIT_SUCCESS);
}

int main() {

    fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34535);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);

    signal(SIGINT, sigHandler);
    signal(SIGTERM,sigExit);

    char message[256];

    while (1) {
        memset(message, '\0', sizeof(message));
        read(STDIN_FILENO, message, 256);
        char* trimmedMessage = trim(message);
        if (strcmp(trimmedMessage,"exit\n") == 0) {
            raise(SIGTERM);
            break;
        }
        if (strlen(trimmedMessage) == 1) {
            continue;
        }

        write(fd, trimmedMessage, sizeof(message));
        char buf[BFSIZE];
        memset(buf, 0, sizeof(buf));
        ssize_t nread;
        nread = read(fd, buf, BFSIZE);
        if (nread == -1) {
            perror("read failed");
            exit(EXIT_FAILURE);
        }
        if (nread == 0) {
            printf("EOF occured\n");
        }

        write(fileno(stdout), buf, nread);
    }

    return 0;
}
