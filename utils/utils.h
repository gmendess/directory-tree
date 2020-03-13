#ifndef _UTILS_H_
#define _UTILS_H_

#include <time.h>

#define FREE_AND_NULL(pointer) \
do {                           \
  free(pointer);               \
  pointer = NULL;              \
}while(0)

typedef enum {
  SUCCESS,
  CANCEL,  // Operação cancelada
  EEXIST,  // Erro, diretório já existe
  ENEXIST, // Erro, diretório não existe
  EPATH,   // Erro, pathname passado é inválido
  ENAME,   // Erro, nome de arquivo inválido
  EROOT    // Erro, tentativa de realizar uma operação inválida com diretório root
} ret_t;

struct tm time_now(void);

// imprime na tela a árvore de diretórios a partir do diretório de trabalho
void tree(void);

// cria o fullpath de diretórios e arquivos
char* make_fullpath(const char* wd_fullpath, const char* name);

#endif // _UTILS_H_