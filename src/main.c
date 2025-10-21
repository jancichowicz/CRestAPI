#include <stdlib.h>
#include <cstdio>

#include "socketserver.h"
#include "requestParser.h"

#define PORT 8080

#ifdef TEST
#include "unity.h"

#include "tests/testRequestParser.h"

void setUp(void) {
}

void tearDown (void) {
}

#endif

int main(int argc, char* argv[]) {
  #ifdef TEST
    UNITY_BEGIN();
      RUN_TEST(test_requestParser_isParsingWorkingCorrectly);
      RUN_TEST(test_requestParser_justResourceWithoutQueries);
      RUN_TEST(test_requestParser_wrongQuery);
      RUN_TEST(test_requestParser_noResourceGiven);
    return UNITY_END();
  #else
    //socketServer sock(PORT);
    char *foo = (char*)malloc(100);
    strcpy(foo, "GET /weather?city=Lodz HTTP/1.1\nHost: 127.0.0.1:127\nAccept: plain/text");
    struct request req = parseRequest(foo);
    free(foo);
    printf("accept: %s\n", req.accept);
    printf("host: %s\n", req.host);
    printf("resource: %s\n", req.resource);
   
    return 0;
  #endif
}
