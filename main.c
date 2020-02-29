#include <stdlib.h>
#include <stdio.h>
#include "file/file.h"
#include "directory/directory.h"
#include "utils/utils.h"

int main() {

  init();
  
  mkdir("teste");
  cd("teste");
  mkdir("teste2");
  cd("teste2");
  mkdir("teste3");
  cd("teste3");
  mkdir("teste4");

  Directory root = get_root_dir();

  printf(
    "%s\n" \
    " `- %s\n" \
    "     `- %s\n" \
    "         `- %s\n" \
    "             `- %s\n",
    root.name,
    root.sub_dirs->name,
    root.sub_dirs->sub_dirs->name,
    root.sub_dirs->sub_dirs->sub_dirs->name,
    root.sub_dirs->sub_dirs->sub_dirs->sub_dirs->name
  );

  return EXIT_SUCCESS;
}