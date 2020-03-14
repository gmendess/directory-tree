#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "file/file.h"
#include "directory/directory.h"
#include "utils/utils.h"

int main() {

  init();
  Directory* wd = pwd();
  char* token;

  mkdir("teste");
  mkdir("teste/ola");
  cd("teste/ola");

  return EXIT_SUCCESS;
}