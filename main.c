#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "file/file.h"
#include "directory/directory.h"
#include "utils/utils.h"

int main() {

  init();

  mkdir("teste");
  mkdir("teste/ola");
  mkdir("hello");
  mkdir("teste/ola/123");
  mkdir("teste/ola/321");
  mkdir("teste/ola/999");
  mkdir("teste/hey");
  mkdir("hello/seila");
  mkdir("hello/seila/teste/oi");
  mkdir("hello/seila/teste/123");
  mkdir("ish");
  mkdir("ish/vish");
  mkdir("ish/oxe");
  tree();

  return EXIT_SUCCESS;
}