#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "log.h"

typedef struct socketServer {
  char *_buffer;
  uint16_t _port, _bufLen;
  int server_fd, new_socket;
  ssize_t valread;
  struct sockaddr_in address;
  int opt = 1;
  socklen_t addrlen = sizeof(address);

  void setUpSocket(void);

  socketServer(uint16_t port, uint16_t bufLen);
  ~socketServer();
} socketServer;
