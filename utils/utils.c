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

  printf("%*s%s\n", indent, "", wd->name);
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

