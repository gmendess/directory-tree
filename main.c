#include <stdlib.h>
#include <stdio.h>
#include "file/file.h"
#include "directory/directory.h"
#include "utils/utils.h"

int main() {

  init();
  Directory r = get_root_dir();
  printf("%s\n", r.name);

  Directory* wd = pwd();
  printf("%s\n", wd->name);

  printf("%s\n", wd->name);
  mkdir("teste");
  printf("%s\n", wd->sub_dirs->name);
  mkdir("oi_outro_teste");
  printf("%s\n", wd->sub_dirs->next->name);


  return EXIT_SUCCESS;
}