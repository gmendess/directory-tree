#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../directory/directory.h"

#define FREE_AND_NULL(pointer) \
do {                           \
  free(pointer);               \
  pointer = NULL;              \
}while(0)

struct tm time_now(void);

// imprime na tela a árvore de diretórios a partir do diretório de trabalho
void tree(void);

// cria o fullpath de diretórios e arquivos
char* make_fullpath(const char* wd_fullpath, const char* name);

#endif // _UTILS_H_