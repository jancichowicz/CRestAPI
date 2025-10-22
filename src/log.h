#include <stdlib.h>
#include <stdarg.h>


#define LOG_INFO    0x1
#define LOG_WARNING 0x2
#define LOG_PANIC   0x3

typedef uint8_t log_type;

static int LOG(log_type type, char const *message, ...) {
  if (type == LOG_INFO) printf("[INFO] ");
  else if (type == LOG_WARNING) printf("[WARNING] ");
  else if (type == LOG_PANIC) printf("[PANIC] ");
  else printf("[UNKNOWN] ");
  va_list va;
  va_start(va, message);
  vfprintf(stdout, message, va);
  printf("\n");
  return 0;
}
