#ifndef _FILE_H_
#define _FILE_H_

#include <time.h>
#include "../directory/directory.h"

typedef struct file {
  char* name;
  struct file* next; // arquivos irmãos, presentes no mesmo diretório
  struct tm creation_time; // data de criação do arquivo
} File;


#endif // _FILE_H_