#include "requestParser.h"

void makeRequestInvalid(struct request *req) {
  req->resource = strdup("WRONG_QUERY");
  req->queryParams = strdup("WRONG_QUERY");
}

request parseRequest(char *req) {
  request retRequest = {0};
  
  if (strstr(req, "&") < strstr(req, "?")) {
    makeRequestInvalid(&retRequest);
  }
  else if (strstr(req, "GET") > strstr(req, "HTTP/1.1")) {
    makeRequestInvalid(&retRequest);
  }
  else if (strstr(req, "GET ") == NULL && strstr(req, "HTTP/1.1") == NULL) {
    makeRequestInvalid(&retRequest);
  } 
  else {
    char *line = strtok(req, "\n");
    while (line != NULL) {
      if (strstr(line, "GET ") != NULL && strstr(line, "HTTP/1.1") != NULL) {
        if (memcmp(line, "GET /", strlen("GET /")) != 0) {
          makeRequestInvalid(&retRequest);
          return retRequest;
        }
        char *fullResource = strdup(line + 4);
        fullResource[strlen(fullResource) - strlen(" HTTP/1.1")] = '\0';        
        retRequest.resource = strdup(fullResource);
        if (strchr(fullResource, '?') != NULL) {
          char *tmpResource = strdup(fullResource);
          char *path = strtok(tmpResource, "?");
          char *queries = strtok(NULL, "");
          if (path != NULL) {
            free(retRequest.resource);
            retRequest.resource = strdup(path);
          }
          if (queries != NULL) {
            retRequest.queryParams = strdup(queries);
          }
          free(tmpResource);
        }
        free(fullResource);
      }
      line = strtok(NULL, "\n");
    }
  }
  return retRequest;
}

