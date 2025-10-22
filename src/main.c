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
    socketServer sock(PORT);
   
    return 0;
  #endif
}
