#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "file/file.c"
#include "directory/directory.c"
#include "utils/utils.c"

int main() {

  init();
  Directory* wd = pwd();
  char* token;

  mkdir("teste");
  mkdir("teste/ola");
  cd("teste/ola");

  return EXIT_SUCCESS;
}