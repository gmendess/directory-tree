#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "file/file.h"
#include "directory/directory.h"
#include "utils/utils.h"

int main() {

  init();

  mkdir("teste");
  mkdir("teste/oi");

  cd("teste/oi");

  touch("teste.txt");
  touch("hello.txt");

  Directory* wd = pwd();
  printf("%s/%s\n", wd->fullpath, wd->files->name);
  printf("%s/%s\n", wd->fullpath, wd->files->next->name);

  return EXIT_SUCCESS;
}