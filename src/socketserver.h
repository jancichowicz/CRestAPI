#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct socketServer {
  char *_buffer;
  uint16_t _port, _bufLen;

  socketServer(uint16_t port, uint16_t bufLen);
  ~socketServer();
} socketServer;
