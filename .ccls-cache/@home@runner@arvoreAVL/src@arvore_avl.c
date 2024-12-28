#include "../include/arvore_avl.h"
#include <sys/stat.h>
#include <sys/types.h>

int calcular_altura(arvore_avl *arv) {
  if (arv == NULL) {
    return 0;
  }
  int altura_esq = calcular_altura(arv->esq);
  int altura_dir = calcular_altura(arv->dir);
  return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

void mostrarEmOrdem(arvore_avl *arv) {

  if (arv != NULL) {
    mostrarEmOrdem(arv->esq);
    printf("  %d", arv->valor);
    mostrarEmOrdem(arv->dir);
  }
}

void mostrarPreOrdem(arvore_avl *arv) {

  if (arv != NULL) {
    printf("  %d", arv->valor);
    mostrarPreOrdem(arv->esq);
    mostrarPreOrdem(arv->dir);
  }
}

void mostrarPosOrdem(arvore_avl *arv) {

  if (arv != NULL) {
    mostrarPosOrdem(arv->esq);
    mostrarPosOrdem(arv->dir);
    printf("  %d", arv->valor);
  }
}

arvore_avl *rotacao_esquerda(arvore_avl *raiz) {
  if (raiz == NULL || raiz->dir == NULL) {
    return raiz;
  }

  arvore_avl *novo_raiz = raiz->dir;
  arvore_avl *subarvore_dir = novo_raiz->esq;

  novo_raiz->esq = raiz;
  raiz->dir = subarvore_dir;

  raiz->altura_esq = calcular_altura(raiz->esq);
  raiz->altura_dir = calcular_altura(raiz->dir);

  novo_raiz->altura_esq = calcular_altura(novo_raiz->esq);
  novo_raiz->altura_dir = calcular_altura(novo_raiz->dir);

  return novo_raiz;
}

arvore_avl *rotacao_direita(arvore_avl *raiz) {
  if (raiz == NULL || raiz->esq == NULL) {
    return raiz;
  }

  arvore_avl *novo_raiz = raiz->esq;
  arvore_avl *subarvore_esq = novo_raiz->dir;

  novo_raiz->dir = raiz;
  raiz->esq = subarvore_esq;

  raiz->altura_esq = calcular_altura(raiz->esq);
  raiz->altura_dir = calcular_altura(raiz->dir);

  novo_raiz->altura_esq = calcular_altura(novo_raiz->esq);
  novo_raiz->altura_dir = calcular_altura(novo_raiz->dir);

  return novo_raiz;
}

arvore_avl *criar_novo_no(int valor) {
  arvore_avl *novo_no = (arvore_avl *)malloc(sizeof(arvore_avl));
  if (novo_no == NULL) {
    fprintf(stderr, "Erro ao alocar memória para o nó.\n");
    exit(1);
  }
  novo_no->valor = valor;
  novo_no->altura_esq = 0;
  novo_no->altura_dir = 0;
  novo_no->esq = NULL;
  novo_no->dir = NULL;
  return novo_no;
}

arvore_avl *balancear_arvore(arvore_avl *raiz) {

  int diferenca, diferenca_subArvore;

  diferenca = raiz->altura_dir - raiz->altura_esq;

  if (diferenca > 1) {
    diferenca_subArvore = raiz->dir->altura_dir - raiz->dir->altura_esq;
    if (diferenca_subArvore >= 0) {
      raiz = rotacao_esquerda(raiz);
    } else {
      raiz->dir = rotacao_direita(raiz->dir);
      raiz = rotacao_esquerda(raiz);
    }
  } else if (diferenca < -1) {
    diferenca_subArvore = raiz->esq->altura_dir - raiz->esq->altura_esq;
    if (diferenca_subArvore <= 0) {
      raiz = rotacao_direita(raiz);
    } else {
      raiz->esq = rotacao_esquerda(raiz->esq);
      raiz = rotacao_direita(raiz);
    }
  }
  return raiz;
}

arvore_avl *inserir_no(arvore_avl *raiz, int valor) {
  arvore_avl *novo_no;

  if (raiz == NULL) {
    return criar_novo_no(valor);
  }

  if (valor < raiz->valor) {
    raiz->esq = inserir_no(raiz->esq, valor); 
  } else if (valor > raiz->valor) {
    raiz->dir = inserir_no(raiz->dir, valor); 
  }

  raiz->altura_esq = calcular_altura(raiz->esq);
  raiz->altura_dir = calcular_altura(raiz->dir);


  raiz = balancear_arvore(raiz);
  return raiz;
}

arvore_avl *buscar(arvore_avl *raiz, int valor) {

  if (raiz == NULL) {
    return 0;
  }

  if (valor < raiz->valor) {
    return buscar(raiz->esq, valor);
  }

  if (valor > raiz->valor) {
    return buscar(raiz->dir, valor);
  }

  if (valor == raiz->valor) {
    return raiz;
  }
  return NULL;
}

arvore_avl *remover_no(arvore_avl *raiz, int valor) {
  if (raiz == NULL) {
    return NULL;
  }

  if (valor < raiz->valor) {
    raiz->esq = remover_no(raiz->esq, valor);
  } else if (valor > raiz->valor) {
    raiz->dir = remover_no(raiz->dir, valor);
  } else {
    if (raiz->esq == NULL && raiz->dir == NULL) {
      free(raiz);
      return NULL;
    } else if (raiz->esq == NULL) {
      arvore_avl *aux = raiz->dir;
      free(raiz);
      return aux;
    } else if (raiz->dir == NULL) {
      arvore_avl *aux = raiz->esq;
      free(raiz);
      return aux;
    } else {
      arvore_avl *aux = raiz->dir;
      while (aux->esq != NULL) {
        aux = aux->esq;
      }
      raiz->valor = aux->valor;
      raiz->dir = remover_no(raiz->dir, aux->valor);
    }
  }

  raiz->altura_esq = calcular_altura(raiz->esq);
  raiz->altura_dir = calcular_altura(raiz->dir);

  return balancear_arvore(raiz);
}

void gerar_dot(FILE *arquivo, arvore_avl *raiz) {
  if (raiz) {
    if (raiz->esq) {
      fprintf(arquivo, "  %d -> %d;\n", raiz->valor, raiz->esq->valor);
      gerar_dot(arquivo, raiz->esq);
    }
    if (raiz->dir) {
      fprintf(arquivo, "  %d -> %d;\n", raiz->valor, raiz->dir->valor);
      gerar_dot(arquivo, raiz->dir);
    }
  }
}

void exportar_para_dot(arvore_avl *raiz, const char *nome_arquivo) {
  const char *pasta = "../outputDOT";
  struct stat st = {0};
  if (stat(pasta, &st) == -1) {
    if (mkdir(pasta, 0700) != 0) {
      fprintf(stderr, "Erro ao criar a pasta %s\n", pasta);
      exit(1);
    }
  }

  FILE *arquivo = fopen(nome_arquivo, "w");
  if (arquivo == NULL) {
    fprintf(stderr, "Erro ao abrir o arquivo %s\n", nome_arquivo);
    exit(1);
  }

  fprintf(arquivo, "digraph G {\n");
  gerar_dot(arquivo, raiz);
  fprintf(arquivo, "}\n");
  fclose(arquivo);
}
