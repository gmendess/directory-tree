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

// Essa struct é genérica, e pode representar tanto um Directory quanto um File.
// Ela possui membros que ambas as structs possuem, como name, fullpath, next e preview.
// É usada para percorrer uma lista de diretórios ou de arquivos
typedef struct generic {
  char* name;
  char* fullpath;
  struct generic* preview;
  struct generic* next;
} Generic;

struct tm time_now(void);

// imprime na tela a árvore de diretórios a partir do diretório de trabalho
void tree(void);

// cria o fullpath de diretórios e arquivos
char* make_fullpath(const char* wd_fullpath, const char* name);

// busca por um diretório ou um arquivo em uma lista de diretórios ou de arquivos
void* __find(void* _generic, const char* target_name, void** preview);

// lista o conteúdo de um diretório, ou seja, seus arquivos e diretórios filhos 
ret_t ls(void);

#endif // _UTILS_H_