#ifndef ERPROC_H
#define ERPROC_H

#include <sys/types.h>
#include <sys/socket.h>
#include <vector>
#include <iostream>

int Socket(int domain, int type, int protocol);

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

void Inet_pton(int af, const char *src, void *dst);

char* trim(std::string s);

char** split(char* str);

char* concat(char *s1, char *s2);

#endif
