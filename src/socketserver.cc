#include "socketserver.h"


socketServer::socketServer(uint16_t port, uint16_t bufLen) {
  this->_port = port;
  this->_bufLen = bufLen;
  this->_buffer = (char*)malloc(this->_bufLen);
  printf("Allocated %d bytes for buffer on: %p\n", this->_bufLen, this->_buffer);
}
socketServer::~socketServer() {
  free(this->_buffer);
  printf("Deallocated buffer\n");
}
