#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include "utils.h"

struct tm time_now(void) {
  time_t t = time(NULL);
  struct tm* _time_now = localtime(&t);

  return *_time_now;
}