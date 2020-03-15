#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "file.h"
#include "../directory/directory.h"
#include "../utils/utils.h"

File* alloc_file(const char* name) {
  Directory* wd = pwd(); // adquirindo referência para o diretório de trabalho

  // alocando memória para struct file
  File* new_file = malloc(sizeof(File));
  if(!new_file) {
    fprintf(stderr, "Falha ao alocar memória para criação do arquivo!\n");
    return NULL;
  }

  // cria o fullpath do arquivo. Exemplo: root/dir1/dir2/file.txt
  new_file->name = strdup(name);
  new_file->fullpath = make_fullpath(wd->fullpath, name);
  new_file->creation_time = time_now();
  new_file->next    = NULL;
  new_file->preview = NULL;

  return new_file;
}

ret_t touch(const char* pathname) {
  if(!pathname)
    return ENAME;

  // Pega a referência do diretório atual
  Directory* wd = pwd();
  Directory* save_wd = wd;

  char* path_copy = strdup(pathname); // cria cópia de pathname
  char* filename = NULL; // nome do arquivo

  // O pedaço de código abaixo é responsável por separar o caminho do nome do arquivo. Ou seja, se eu der
  // 'touch foo/bar/file.txt', o diretório que o arquivo 'file.txt' deve ser adiconado é o 'foo/bar/'
  
  char* bar_last_ocurrence = strrchr(path_copy, '/'); // procura a última ocorrência do caractere '/'
  // última ocorrência foi encontrada
  if(bar_last_ocurrence) {
    *bar_last_ocurrence = '\0'; // substitui a barra por um caractere de término ( 'foo/bar\0file.txt' )
    filename = bar_last_ocurrence + 1; // file.txt

    // tenta entrar no diretório que o arquivo deve ser adicionado. A função cd usa strtok para dar parse no caminho e
    // strtok lê uma string até o caractere de término, logo ele lerá apenas 'foo/bar\0'
    if(cd(path_copy) == EPATH)
      return EPATH; // caminho passado é inválido, retorna EPATH
    
    wd = pwd(); // atualiza a referência do diretório atual
  }
  else
    filename = path_copy; // se nenhum diretório foi passado, o nome do arquivo é o próprio pathname

  // Cria o arquivo
  File* new_file = alloc_file(filename);

  // verifica se o diretório de trabalho possui arquivos
  if(wd->files) {
    File* last = NULL; // caso o arquivo com nome 'name' não seja encontrado, o último arquivo da lista será apontado por 'last'
    File* target_file = __find(wd->files, filename, (void*) &last);
    if(target_file) // arquivo encontrado
      return EEXIST;
    else { // arquivo não encontrado
      new_file->preview = last;
      last->next = new_file;
    }
  }
  else
    wd->files = new_file;

  // Sim, isso é um put* gambiarra pra voltar pro diretório que invocou o comando 'touch'
  // Não posso manipular diretamente o variável wd, pois ela é static do arquivo directory.c
  // Ainda não sei como vou resolver isso.
  char* temp_fullpath = strdup(save_wd->fullpath);
  temp_fullpath[3] = '~';
  cd(temp_fullpath + 3);
  free(temp_fullpath);

  return SUCCESS; // arquivo inserido com sucesso!
}