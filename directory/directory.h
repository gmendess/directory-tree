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

void init(void);
Directory get_root_dir(void);
Directory pwd(void);
Directory* alloc_directory(const char* name);

#endif // _DIRECTORY_H_