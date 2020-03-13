#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include "utils.h"
#include "../directory/directory.h"

struct tm time_now(void) {
  time_t t = time(NULL);
  struct tm* _time_now = localtime(&t);

  return *_time_now;
}

static void __tree(Directory* wd) {
  if(wd == NULL)
    return;

  // representa a identação do diretório para facilitar visualização
  static size_t indent = 0;

  if(indent > 0) {
    for(int x = 1; x < indent; x++) {
      if(x % 2 == 0)
        putchar('|');
      putchar(' ');
    }
    printf(" `-- ");
  }
  printf("%s/\n", wd->name);
  Directory* aux = wd->sub_dirs;
  while(aux) {
    indent += 2;
    __tree(aux);
    aux = aux->next;
    indent -= 2;
  }
}

void tree(void) {
  // como wd é uma variável static de directory.c, é necessário usar a função pwd para pegar sua referência
  Directory* wd = pwd();
  puts("Arvore de diretorios:\n");

  __tree(wd);
}

char* make_fullpath(const char* wd_fullpath, const char* name) {
  // ponteiro que será a referência para a string do fullpath; será retornado no final da função
  char* fullpath = NULL;
  
  // tamanho do fullpath do diretório pai
  size_t wd_fullpath_size = strlen(wd_fullpath);

  // tamanho do nome do arquivo/diretório
  size_t name_size = strlen(name);

  // tamanho do fullpath do diretório pai + '/' + tamanho do nome do diretório/arquivo + '\0'
  size_t new_fullpath_size = wd_fullpath_size + 1 + name_size + 1;
  // aloca memória suficiente para o fullpath do diretório filho
  fullpath = calloc(new_fullpath_size, 1);

  // faz a montagem do fullpath do diretório/arquivo
  memcpy(fullpath, wd_fullpath, wd_fullpath_size); // inicia a montagem; fullpath do diretório/arquivo herda o fullpath do diretório pai
  fullpath[wd_fullpath_size] = '/'; // adiciona barra divisora
  strcat(fullpath + wd_fullpath_size + 1, name); // concatena ao fullpath o nome do diretório/arquivo]

  return fullpath;
}