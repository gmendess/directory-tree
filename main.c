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

  File* file = alloc_file("meu_arquivo.txt");
  printf("%s\n", file->name);
  printf("%s\n", file->fullpath);
  printf("%s\n", asctime(&file->creation_time));

  return EXIT_SUCCESS;
}