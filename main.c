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

  char command[50];
  while(1) {
    printf("%s> ", wd->name);
    scanf("%[^\n]", command);
    getchar();
    token = strtok(command, " ");
    if(strcmp(token, "cd") == 0) {
      token = strtok(NULL, " ");
      cd(token);
    }
    else if(strcmp(token, "mkdir") == 0){
      token = strtok(NULL, " ");
      mkdir(token);
    }
    else
      printf("Comando \"%s\" nao encontrado!\n", token);

    wd = pwd();
  }

  return EXIT_SUCCESS;
}