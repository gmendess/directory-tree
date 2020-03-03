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

  while(1) {
    char command[50] = {0};
    printf("%s> ", wd->fullpath);
    scanf("%[^\n]", command);
    getchar();
    token = strtok(command, " ");
    if(!token)
      continue;
    if(strcmp(token, "cd") == 0) {
      token = strtok(NULL, " ");
      cd(token);
    }
    else if(strcmp(token, "mkdir") == 0) {
      token = strtok(NULL, " ");
      if(mkdir(token) == EEXIST)
        puts("Erro! Caminho passado ja existe!");
    }
    else if(strcmp(token, "rmdir") == 0) {
      token = strtok(NULL, " ");
      if(rmdir(token) == EPATH)
        puts("Erro! Caminho passado nao existe!");
    }
    else if(strcmp(token, "tree") == 0)
      tree();
    else
      printf("Comando \"%s\" nao encontrado!\n", token);

    wd = pwd();
  }

  return EXIT_SUCCESS;
}