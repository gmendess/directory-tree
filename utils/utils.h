#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct tm* time_now(void);
void* make_ptr_copy(const void* ptr, size_t bytes);

#endif // _UTILS_H_