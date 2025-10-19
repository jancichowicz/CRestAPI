#include "socketserver.h"

void *manageRequestToClient(void *sock);

void socketServer::setUpSocket(void) {
  if((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    LOG(LOG_PANIC, "Unable to create socket on port: %d", this->_port);
    exit(1);
  }
  LOG(LOG_INFO, "Created socket on port: %d", this->_port);

  if(setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &this->opt, sizeof(this->opt)) < 0) {
     LOG(LOG_PANIC, "Unable to attach socket to port: %d", this->_port);
  }
  LOG(LOG_INFO, "Attached socket to port");

  this->address.sin_family = AF_INET;
  this->address.sin_addr.s_addr = INADDR_ANY;
  this->address.sin_port = htons(this->_port);

  if(bind(this->server_fd, (struct sockaddr*)&this->address, sizeof(this->address)) < 0) {
    LOG(LOG_PANIC, "Unable to bind socket to port: %d", this->_port);
  }
  LOG(LOG_INFO, "Socket bound to port");
}
void socketServer::superLoop(void) {
  this->setUpSocket();

  
  while (isErrorRaised == false) {
    int client_fd = 0;
    if (listen(this->server_fd, 3) < 0) {
      LOG(LOG_PANIC, "Listen failed");
    } else {
      client_fd = accept(this->server_fd, (struct sockaddr*)&this->address, &this->addrlen);

      pthread_t newThread;
      // (void*)(intptr_t) is a workaround to pass arg by value. Alternative would be allocating client_fd dynamically
      if (pthread_create(&newThread, NULL, manageRequestToClient, (void*)(intptr_t)client_fd) != 0) {
        LOG(LOG_PANIC, "Unable to create thread for new connection");
      }
    }
  }
}
socketServer::socketServer(uint16_t port) {
  LOG(LOG_INFO, "Socket server instance created");
  this->_port = port;

  this->superLoop();
}
socketServer::~socketServer() {
  close(this->server_fd);
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
