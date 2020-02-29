#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "directory.h"
#include "../file/file.h"
#include "../utils/utils.h"

// Variável que representa o diretório raiz da árvore de diretórios
static Directory root;

// Variável que armazena referência para o diretório atual (working directory)
static Directory* wd;

/* ------------------------------ FUNÇÕES STATIC INTERNAS ---------------------------------- */

// Função interna que percorre uma lista encadeada de Directory buscando pelo diretório desejado.
// Obs:
//   - Não valida se 'dir' é um ponteiro válido.
//   - Se 'target_name' for NULL, procura pelo ultimo diretório
//   - Retorna NULL apenas caso não exista nenhum nó com nome 'target_name'
static Directory* __find_directory(Directory* dir, const char* target_name) {
  if(!target_name) {
    // percorre até o último nó
    for(; dir->next; dir = dir->next);
  }
  else {
    // busca pelo nó com nome igual 'target_name'
    while(dir && strcmp(dir->name, target_name) != 0)
      dir = dir->next;
  }

  return dir;
}

// abstração para __find_directory. Busca pelo último diretório na lista 'sub_dirs'
static Directory* __find_last_sub_directory(Directory* wd) {
  if(!wd)
    return NULL;
  else if(!wd->sub_dirs)
    return wd;

  return __find_directory(wd->sub_dirs, NULL);
}

// abstração para __find_last_directory. Busca pelo último diretório na lista 'next'
static Directory* __find_last_brother_directory(Directory* wd) {
  if(!wd || !wd->next)
    return NULL;
  else if(!wd->next)
    return wd;

  return __find_directory(wd->next, NULL);
}

/* ----------------------------------------------------------------------------------------- */

// Inicializa o diretório root e faz wd apontar para seu endereço
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

// Retorna uma cópia do diretório root
Directory get_root_dir(void) {
  return root;
}

// Retorna referência para o diretório atual (working directory)
Directory* pwd(void) {
  return wd;
}

// Aloca espaço na memória para conter uma struct Directory
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

// Simula um mkdir, ou seja, cria um novo diretório no 'wd' atual
ret_t mkdir(const char* pathname) {
  if(!pathname)
    return EPATH;

  Directory* new_dir = alloc_directory(pathname);
  Directory* last = __find_last_sub_directory(wd);

  if(last == wd)
    wd->sub_dirs = new_dir;
  else
    last->next = new_dir;

  return SUCCESS;
}

// Muda o diretório atual para o passado via parâmetro
ret_t cd(const char* pathname) {
  if(!pathname)
    return EPATH;

  Directory* target_dir = __find_directory(wd->sub_dirs, pathname);
  if(target_dir) {
    wd = target_dir;
    return SUCCESS;
  }
  else {
    fprintf(stderr, "Diretório não encontrado!\n");
    return ENEXIST;
  }
}