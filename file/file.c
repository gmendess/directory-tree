#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "file.h"
#include "../directory/directory.h"
#include "../utils/utils.h"

File* alloc_file(const char* name) {
  Directory* wd = pwd(); // adquirindo referência para o diretório de trabalho

  // alocando memória para struct file
  File* new_file = (File*) malloc(sizeof(File));
  if(!new_file) {
    fprintf(stderr, "Falha ao alocar memória para criação do arquivo!\n");
    return NULL;
  }

  // cria o fullpath do arquivo. Exemplo: root/dir1/dir2/file.txt
  new_file->name = strdup(name);
  new_file->fullpath = make_fullpath(wd->fullpath, name);
  new_file->creation_time = time_now();
  new_file->next    = NULL;
  new_file->preview = NULL;

  return new_file;
}

ret_t touch(const char* name) {
  if(!name)
    return ENAME;

  // adquirindo referência para o diretório de trabalho
  Directory* wd = pwd();

  File* new_file = alloc_file(name);
  new_file->next = wd->files;
  wd->files = new_file;

  return SUCCESS;
}