#include <stdlib.h>
#include <stdio.h>
#include "file/file.h"
#include "directory/directory.h"
#include "utils/utils.h"

int main() {

  init();
  
  Directory* wd = pwd();

  mkdir("dir1");
  mkdir("dir2");

  printf(
    "%s\n"     \
    " `- %s\n" \
    " `- %s\n", 
    wd->name, 
    wd->sub_dirs->name, 
    wd->sub_dirs->next->name
  );

  cd("dir2");
  wd = pwd(); // pegando referência do novo diretório atual
  printf("%s\n", wd->name);

  return EXIT_SUCCESS;
}