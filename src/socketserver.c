#include "socketserver.h"


socketServer::socketServer(uint16_t port, uint16_t bufLen) {
  this->_port = port;
  this->_bufLen = bufLen;
  this->_buffer = (char*)malloc(this->_bufLen);
  LOG(LOG_INFO, "Allocated %d bytes for buffer on: %p", this->_bufLen, this->_buffer);
}
socketServer::~socketServer() {
  free(this->_buffer);
  LOG(LOG_INFO, "Deallocated buffer");
}
