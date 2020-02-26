#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "directory.h"
#include "../file/file.h"

// Variável que representa o diretório raiz da árvore de diretórios
static Directory root;

// Variável que representa o diretório atual (working directory)
static Directory* wd;

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

Directory pwd(void) {
  return *wd;
}