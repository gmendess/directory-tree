#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_

#include <time.h>
#include "../file/file.h"

typedef struct directory {
  char* name;
  struct directory* next;     // diretórios irmãos
  struct directory* sub_dirs; // diretórios filhos
  struct file* files;         // arquivos presentes no diretório
  struct tm* creation_time;   // data de criação do diretório
} Directory;

typedef enum {
  MKDIR_SUCCESS,
  EEXIT, // Erro, diretório já existe
  EPATH  // pathname passado é inválido
} ret_t;

// Inicializa o diretório root e faz wd apontar para seu endereço
void init(void);

// Retorna uma cópia do diretório root
Directory get_root_dir(void);

// Retorna referência para o diretório atual (working directory)
Directory* pwd(void);

// Aloca espaço na memória para conter uma struct Directory
Directory* alloc_directory(const char* name);

// Simula um mkdir, ou seja, cria um novo diretório no 'wd' atual
ret_t mkdir(const char* pathname);

#endif // _DIRECTORY_H_