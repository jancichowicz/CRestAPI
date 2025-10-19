#include <stdlib.h>
#include <cstdio>

#include "socketserver.h"

#define PORT 8080

#ifdef TEST
#include "unity.h"

void setUp(void) {
}

void tearDown (void) {
}

#endif

int main(int argc, char* argv[]) {
  #ifdef TEST
    UNITY_BEGIN();

    return UNITY_END();
  #else
    socketServer sock(PORT);

    return 0;
  #endif
}
