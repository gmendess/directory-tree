#ifndef _FILE_H_
#define _FILE_H_

#include <time.h>
#include "../directory/directory.h"

typedef struct file {
  char* name;
  char* fullpath;          // caminho completo do arquivo
  struct file* preview;    // arquivo irmão anterior (presente no mesmo diretório)
  struct file* next;       // próximo arquivo irmão (presente no mesmo diretório)
  struct tm creation_time; // data de criação do arquivo
} File;


#endif // _FILE_H_