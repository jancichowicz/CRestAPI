#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct request {
  char *resource;
  char *queryParams;
};

request parseRequest(char *req);


#endif
