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
  #endif

  socketServer sock(PORT);


  #ifdef TEST 
  return UNITY_END();
  #endif

  return 0;
}
