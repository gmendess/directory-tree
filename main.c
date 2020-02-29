#include <stdlib.h>
#include <stdio.h>
#include "file/file.h"
#include "directory/directory.h"
#include "utils/utils.h"

int main() {

  init();
  
  Directory* wd = pwd();

  mkdir("dir1");
  cd("dir1");
  mkdir("dir2");

  printf(
    "Diretorio: %s\n" \
    "Diretorio pai: %s\n" \
    "Diretorio avo: %s\n",
    wd->sub_dirs->sub_dirs->name,
    wd->sub_dirs->sub_dirs->father->name,
    wd->sub_dirs->sub_dirs->father->father->name
  );

  return EXIT_SUCCESS;
}