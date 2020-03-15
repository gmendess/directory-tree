#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "file/file.h"
#include "directory/directory.h"
#include "utils/utils.h"

static void __temp_list_files(void) {
  Directory* wd = pwd();
  File* file = wd->files; 
  while(file) {
    puts(file->name);
    file = file->next;
  }
}

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
    else if(strcmp(token, "touch") == 0) {
      token = strtok(NULL, " ");
      ret_t ret = touch(token);
      if(ret == EEXIST)
        puts("Erro! Arquivo ja existe nesse diretorio!");
      else if(ret == ENAME)
        puts("Erro! Nome do arquivo inválido!");
    }
    else if(strcmp(token, "tree") == 0)
      tree();
    else if(strcmp(token, "lf") == 0)
      __temp_list_files();
    else
      printf("Comando \"%s\" nao encontrado!\n", token);

    wd = pwd();
  }

  return EXIT_SUCCESS;
}