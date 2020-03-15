#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "directory.h"
#include "../file/file.h"
#include "../utils/utils.h"

// Variável que representa o diretório raiz da árvore de diretórios
static Directory root;

// Variável que armazena referência para o diretório atual (working directory)
static Directory* wd;

// Zera o conteúdo de um diretório, liberando memória dos membros alocados dinamicamente e zerando ponteiros
static void __clean_up(Directory* dir) {
  FREE_AND_NULL(dir->fullpath);
  FREE_AND_NULL(dir->name);
  dir->father   = NULL;
  dir->files    = NULL;
  dir->next     = NULL;
  dir->preview  = NULL;
  dir->sub_dirs = NULL;
}

// Zera o conteúdo de um diretório de forma recursiva, ou seja, entra em seus subdiretórios, limpando-os.
// Após zerar o conteúdo, a memória apontada por 'dir' é liberada
static void __clean_and_free_all(Directory* dir, int clean_next_brothers) {
  if(dir == NULL)
    return;

  // se a flag clean_next_brothers estiver configurada, os diretórios irmãos posteriores também serão limpos
  if(clean_next_brothers)
    __clean_and_free_all(dir->next, 1);

  __clean_and_free_all(dir->sub_dirs, 1);
  __clean_up(dir);
  free(dir);
}

/* ----------------------------------------------------------------------------------------- */

// Inicializa o diretório root e faz wd apontar para seu endereço
void init(void) {

  root.fullpath = "root";
  root.name = "root";
  root.father = NULL;
  root.preview = NULL;
  root.next = NULL;
  root.sub_dirs = NULL;
  root.files = NULL;
  root.creation_time = time_now();

  // inicialmente pwd aponta para o diretório raiz
  wd = &root;
}

// Retorna uma cópia do diretório root
Directory get_root_dir(void) {
  return root;
}

// Retorna referência para o diretório atual (working directory)
Directory* pwd(void) {
  return wd;
}

// Aloca espaço na memória para conter uma struct Directory e inicializa seus membros
Directory* alloc_directory(const char* name) {
  Directory* new_dir = malloc(sizeof(Directory));

  if(!new_dir) {
    fprintf(stderr, "Falha ao alocar memória para criação do diretório!\n");
    return NULL;
  }

  size_t size = strlen(name); // tamanho do nome do diretório
  new_dir->name = strdup(name); // copia parâmetro 'name' para 'new_dir->name'

  // tamanho do fullpath do diretório pai
  size_t wd_fullpath_size = strlen(wd->fullpath);

  // tamanho do fullpath do diretório pai + '/' + tamanho do nome do diretório filho + '\0'
  size_t new_fullpath_size = wd_fullpath_size + 1 + size + 1;
  new_dir->fullpath = calloc(new_fullpath_size, 1); // aloca memória suficiente para caber o fullpath do diretório filho

  // faz a montagem do fullpath do diretório filho
  memcpy(new_dir->fullpath, wd->fullpath, wd_fullpath_size); // inicia a montagem; fullpath do filho herda o fullpath do pai
  new_dir->fullpath[wd_fullpath_size] = '/'; // adiciona barra divisora de diretórios
  strcat(new_dir->fullpath + wd_fullpath_size + 1, name); // concatena ao fullpath o nome do diretório filho

  new_dir->creation_time = time_now();
  new_dir->files    = NULL;
  new_dir->father   = wd;   // diretório atual se torna o pai desse novo diretório
  new_dir->preview  = NULL;
  new_dir->next     = NULL;
  new_dir->sub_dirs = NULL;

  return new_dir;
}

// Simula um mkdir, ou seja, adiciona um novo diretório no 'wd' atual
ret_t mkdir(const char* pathname) {
  if(!pathname)
    return EPATH;

  Directory* save_wd = wd;
  Directory* new_dir = NULL;

  // cria cópia de pathname para ser usada na função strtok
  char* path_copy = strdup(pathname);
  
  // percorre cada diretório do path.
  char* token = strtok(path_copy, "/");
  while(token) {
    // verifica se o diretório de trabalho possui diretório filhos
    if(wd->sub_dirs) {
      Directory* prior_last = NULL;

      // tenta buscar pelo diretório contido em 'token'
      Directory* target_dir = __find(wd->sub_dirs, token, (void*) &prior_last);
      if(target_dir) // se o diretório foi encontrado
        wd = target_dir; // entra no diretório
      else { // diretório não existe, logo deve ser criado
        new_dir = alloc_directory(token);
        new_dir->preview = prior_last;
        prior_last->next = new_dir; // último filho do diretório de trabalho aponta para o novo diretório
        wd = new_dir; // entra nesse novo diretório
      }
    }
    else { // se o diretório de trabalho não tiver filhos, significa que já devo criar um diretório novo
      new_dir = alloc_directory(token);
      wd->sub_dirs = new_dir; // adiciona primeiro filho ao diretório de trabalho
      wd = new_dir; // entra no diretório filho recém criado.
    }

    token = strtok(NULL, "/"); // pega o nome do próximo diretório do path
  }

  wd = save_wd;

  free(path_copy);
  // se new_dir for um ponteiro válido, significa que um diretório foi criado. Caso contrário,
  // o caminho passado à mkdir já existe, logo, retorna o código de erro EEXIST.
  return new_dir ? SUCCESS : EEXIST;
}

// Muda o diretório atual para um passado via parâmetro
ret_t cd(const char* pathname) {
  if(!pathname)
    return EPATH;

  Directory* save_wd = wd; // salva o diretório atual antes de percorrer 'pathname'
  Directory* target_dir = NULL;

  // cria uma copia da string contida em pathname
  char* path_copy = strdup(pathname);

  // percorre cada diretório do path até chegar no desejado. Se um dos diretórios não existir, retorna EPATH, pois o caminho é inválido
  char* token = strtok(path_copy, "/");
  while(token) {
    // verifica se é um comando para voltar um diretório
    if(strcmp(token, "..") == 0) {
      // verifica se o diretório atual é diferente de root. Se for, n faz nada, porque não há nada antes de root
      if(wd != &root)
        wd = wd->father; // diretório atual passa a ser seu diretório pai
    }
    else if(strcmp(token, "~") == 0) // se for um 'cd ~'
      wd = &root; // volta ao diretório raiz
    else {
      // busca pelo diretório em 'wd'
      target_dir = __find(wd->sub_dirs, token, NULL);

      // verifica se o diretório foi encontrado
      if(target_dir)
        wd = target_dir; // se sim, entra nesse diretório
      else {
        wd = save_wd; // se o caminho for inválido, wd retorna para o diretório inicial
        return EPATH;
      }
    }

    token = strtok(NULL, "/"); // pega o nome do próximo diretório do path
  }

  free(path_copy);
  return SUCCESS;
}

ret_t rmdir(const char* pathname) {
  if(!pathname)
    return EPATH;

  // Salva o working directory atual
  Directory* save_wd = wd;

  // Entra no último diretório do path
  if(cd(pathname) == EPATH)
    return EPATH; // se o path for inválido, retorna EPATH
  
  // No final da função o save_wd é usado para retornar ao diretório que chamou o comando rmdir. Isso causava um bug caso tentasse remover o próprio
  // diretório em que estava, pois ele retornaria para ele mesmo. Dessa forma, se save_wd for igual a wd, save_wd passa a ser o diretório pai
  if(save_wd == wd)
    save_wd = wd->father;

  // Caso seja possível acessar o path, o diretório apontado por wd mudará (devido ao cd).

  // Não deve ser possível remover o diretório root!
  if(wd == &root)
    return EROOT;

  // Directory auxiliar que aponta para o diretório que será removido
  Directory* aux = wd;

  // se wd->sub_dirs for diferente de NULL, significa que esse diretório possui filhos, dessa forma, é perguntado
  // se o usuário deseja ou não fazer uma exclusão recursiva (excluir todo o conteúdo do diretório, incluindo os
  // subdiretórios de seus diretórios filhos).
  if(wd->sub_dirs != NULL) {
    printf("O diretorio \"%s\" nao esta vazio, deseja realizar uma exclusao recursiva (S/n)? ", wd->name);
    char response = 0;
    scanf("%c", &response);
    getchar();
    if(response != 'S') {
      puts("rmdir cancelado!");
      wd = save_wd;
      return CANCEL; // se a resposta for diferente de 'S', a operação de excluir o diretório é cancelada
    }
  }

  // Se o diretório irmão anterior do diretório a ser excluído for igual a NULL, significa que ele é o primeiro filho de seu
  // diretório pai. Com isso, o diretório pai deve apontar para seu segundo filho
  if(wd->preview == NULL)
    wd->father->sub_dirs = wd->next;
  else
    wd->preview->next = wd->next; // se não, o irmão anterior aponta para o irmão posterior do diretório a ser excluido

  __clean_and_free_all(aux, 0); // limpa o conteúdo do diretório, liberando memória de seus membros

  wd = save_wd;

  return SUCCESS;
}