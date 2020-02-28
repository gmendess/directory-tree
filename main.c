#include <stdlib.h>
#include <stdio.h>
#include "file/file.h"
#include "directory/directory.h"
#include "utils/utils.h"

int main() {

  init();
  Directory r = get_root_dir();
  printf("%s\n", r.name);

  Directory wd = pwd();
  printf("%s\n", wd.name);

  Directory* new_dir = alloc_directory("jogos");
  printf("%s\n", new_dir->name);

  return EXIT_SUCCESS;
}