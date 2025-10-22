#include <stdlib.h>

#include "socketserver.h"
#include "requestParser.h"

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
    socketServer ss = {0};
    setUpSocketServer(&ss, 8080);
    socketServerSuperLoop(&ss);

    return 0;
  #endif
}
