#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "directory.h"
#include "../file/file.h"
#include "../utils/utils.h"

// Variável que representa o diretório raiz da árvore de diretórios
static Directory root;

// Variável que representa o diretório atual (working directory)
static Directory* wd;

/* ------------------------------ FUNÇÕES STATIC INTERNAS ---------------------------------- */

// função interna que percorre uma lista encadeada de Directory e retorna o último elemento´.
// É bom que essa função seja chamada por uma de suas abstrações, pois ela não faz verificação
// se 'dir' é um ponteiro válido
static Directory* __find_last_directory(Directory* dir) {
  while(dir->next)
    dir = dir->next;

  return dir;
}

// abstração para __find_last_directory
static Directory* __find_last_sub_directory(Directory* wd) {
  if(!wd)
    return NULL;
  else if(!wd->sub_dirs)
    return wd->sub_dirs;

  return __find_last_directory(wd->sub_dirs);
}

// abstração para __find_last_directory.
static Directory* __find_last_brother_directory(Directory* wd) {
  if(!wd || !wd->next)
    return NULL;

  return __find_last_directory(wd->next);
}

/* ----------------------------------------------------------------------------------------- */


void init(void) {
  time_t curr_time = time(NULL);

  root.name = "root";
  root.next = NULL;
  root.sub_dirs = NULL;
  root.files = NULL;
  root.creation_time = localtime(&curr_time);

  // inicialmente pwd aponta para o diretório raiz
  wd = &root;
}

Directory get_root_dir(void) {
  return root;
}

Directory* pwd(void) {
  return wd;
}

Directory* alloc_directory(const char* name) {
  Directory* new_dir = malloc(sizeof(Directory));

  if(!new_dir) {
    fprintf(stderr, "Falha ao alocar memória para criação do diretório!\n");
    return NULL;
  }

  size_t size = strlen(name) + 1; // tamanho da string + '\0'
  new_dir->name = malloc(size);
  memcpy(new_dir->name, name, size);

  new_dir->creation_time = time_now();
  new_dir->files    = NULL;
  new_dir->next     = NULL;
  new_dir->sub_dirs = NULL;

  return new_dir;
}

mkdir_ret mkdir(const char* pathname) {
  if(!pathname)
    return EPATH;

  Directory* new_dir = alloc_directory(pathname);
  Directory* last = __find_last_sub_directory(wd);

  if(last == wd->sub_dirs)
    wd->sub_dirs = new_dir;
  else
    last->next = new_dir;

  return MKDIR_SUCCESS;
}