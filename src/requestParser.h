#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct request {
  char *resource;
  char *queryParams;
} request;

request parseRequest(char *req);
void makeRequestInvalid(struct request *req);


#endif
