#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define FREE_AND_NULL(pointer) \
do {                           \
  free(pointer);               \
  pointer = NULL;              \
}while(0)

struct tm* time_now(void);

#endif // _UTILS_H_