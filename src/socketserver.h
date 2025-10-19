#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>

#include "log.h"

#define BUFFER_LEN 512

static bool isErrorRaised = false;
typedef struct socketServer {
  uint16_t _port;
  int server_fd = 0;
  struct sockaddr_in address;
  int opt = 1;
  socklen_t addrlen = sizeof(address);

  void setUpSocket(void);
  void superLoop(void);

  socketServer(uint16_t port);
  ~socketServer();
} socketServer;
