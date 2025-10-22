#include "socketserver.h"

void *manageRequestToClient(void *sock);

void setUpSocketServer(socketServer *sockserv, uint16_t port) {
  LOG(LOG_INFO, "Socket server instance created");
  sockserv->_port = port;
  sockserv->opt = 1;
  sockserv->server_fd = 0;
  if((sockserv->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    LOG(LOG_PANIC, "Unable to create socket on port: %d", sockserv->_port);
    exit(1);
  }
  LOG(LOG_INFO, "Created socket on port: %d", sockserv->_port);

  if(setsockopt(sockserv->server_fd, SOL_SOCKET, SO_REUSEADDR, &sockserv->opt, sizeof(sockserv->opt)) < 0) {
     LOG(LOG_PANIC, "Unable to attach socket to port: %d", sockserv->_port);
  }
  LOG(LOG_INFO, "Attached socket to port");

  sockserv->address.sin_family = AF_INET;
  sockserv->address.sin_addr.s_addr = INADDR_ANY;
  sockserv->address.sin_port = htons(sockserv->_port);
  sockserv->addrlen = sizeof(sockserv->address);

  if(bind(sockserv->server_fd, (struct sockaddr*)&sockserv->address, sizeof(sockserv->address)) < 0) {
    LOG(LOG_PANIC, "Unable to bind socket to port: %d", sockserv->_port);
  }
  LOG(LOG_INFO, "Socket bound to port");
}
void socketServerSuperLoop(socketServer *sockserv) {
  while (isErrorRaised == false) {
    int client_fd = 0;
    if (listen(sockserv->server_fd, 3) < 0) {
      LOG(LOG_PANIC, "Listen failed");
    } else {
      client_fd = accept(sockserv->server_fd, (struct sockaddr*)&sockserv->address, &sockserv->addrlen);

      pthread_t newThread;
      // (void*)(intptr_t) is a workaround to pass arg by value. Alternative would be allocating client_fd dynamically
      if (pthread_create(&newThread, NULL, manageRequestToClient, (void*)(intptr_t)client_fd) != 0) {
        LOG(LOG_PANIC, "Unable to create thread for new connection");
      }
    }
  }
}


void tearDownSocketServer(socketServer *sockserv){
  close(sockserv->server_fd);
  LOG(LOG_INFO, "Socket server instance deleted");
}

void *manageRequestToClient(void *sock) {
  LOG(LOG_INFO, "Created thread for client. ThreadID: %d", pthread_self());

  int client_fd = (int)(intptr_t)sock;
  char *buffer = (char*)malloc(1024);
  char responseMessage[] = "HTTP/1.1 200 OK\nContent-Type: text/plan\nContent-Length: 3\n\nres";
  if (buffer == NULL) {
    LOG(LOG_PANIC, "Unable to allocate memory for buffer");
    free(buffer);
    pthread_exit(0);
  }
  ssize_t valread = read(client_fd, buffer, 1023);
  if (valread == -1) {
    LOG(LOG_PANIC, "Unable to read from client. read() errno string: %s", strerror(errno));
    free(buffer);
    pthread_exit(0);
  }

  LOG(LOG_INFO, "Message from client: \n%s", buffer);

  if (send(client_fd, responseMessage, strlen(responseMessage), 0) == -1) {
    LOG(LOG_PANIC, "Unable to send to client. send() errno string: %s", strerror(errno));
    free(buffer);
    pthread_exit(0);
  }
  close(client_fd);
  free(buffer);

  LOG(LOG_INFO, "Thread exited successfully. ThreadID: %d", pthread_self());

  pthread_exit(0);
}
