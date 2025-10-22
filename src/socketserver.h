#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <assert.h>
#include <pthread.h>
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>

#include "log.h"

#define BUFFER_LEN 512

static bool isErrorRaised = false;
typedef struct socketServer {
  uint16_t _port;
  int server_fd;
  struct sockaddr_in address;
  int opt;
  socklen_t addrlen;


} socketServer;

void socketServerSuperLoop(socketServer *sockserv);
void setUpSocketServer(socketServer *sockserv, uint16_t port);
void tearDownSocketServer(socketServer *sockserv);
