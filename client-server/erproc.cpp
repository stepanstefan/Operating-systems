#include "erproc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <vector>

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        printf("inet_pton failed: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}

char* trim(std::string s) {

    int i = 0, j;
    while ((s[i] == ' ') || (s[i] == '\t')) {
        i++;
    }
    i--;

    while (i > -1) {
        s.erase(s.begin() + i);
        i--;
    }

    i = s.length() - 2;
    while((s[i] == ' ') || (s[i] == '\t')) {
        s.erase(s.begin() + i);
        i--;
    }
    char *cstr = new char[s.length() + 1];
    strcpy(cstr, s.c_str());

    return cstr;
}

char** split(char* str) {
  std::vector<char*> message;
  char *istr;
  istr = strtok (str, " ");
  while (istr != NULL) {
    printf("%s", str);
    message.push_back(istr);
    istr = strtok (NULL, " ");
  }
  message[message.size() - 1][strlen(message[message.size() - 1]) - 1] = '\0';
  char **argv = new char* [message.size() + 1];
  for (int i = 0; i < message.size(); i++)
    argv[i] = message[i];
  argv[message.size()] = NULL;
  return argv;
}

char* concat(char *s1, char *s2) {
  size_t len1 = strlen(s1);
  size_t len2 = strlen(s2);

  char *result = (char*)malloc(len1 + len2 + 1);

  if (!result) {
      fprintf(stderr, "malloc() failed: insufficient memory!\n");
      return NULL;
  }

  memcpy(result, s1, len1);
  memcpy(result + len1, s2, len2 + 1);

  return result;
}


