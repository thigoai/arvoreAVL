#include "../include/arvore_avl.h"

#include <stdio.h>
#include <stdlib.h>

int calcular_altura(arvore_avl *arv) {
  if (arv == NULL) {
    return 0;
  }
  int altura_esq = arv->esq ? arv->esq->altura_esq : 0;
  int altura_dir = arv->dir ? arv->dir->altura_dir : 0;
  return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

void mostrarEmOrdem(arvore_avl *arv){

  if(arv != NULL){
    mostrarEmOrdem(arv->esq);
    printf("  %d", arv->valor);
    mostrarEmOrdem(arv->dir); 
  }

}

void mostrarPreOrdem(arvore_avl *arv){

  if(arv != NULL){
    printf("  %d", arv->valor);
    mostrarPreOrdem(arv->esq);
    mostrarPreOrdem(arv->dir);
  }

}

void mostrarPosOrdem(arvore_avl *arv){

  if(arv != NULL){
    mostrarPosOrdem(arv->esq);
    mostrarPosOrdem(arv->dir);
    printf("  %d", arv->valor);
  }

}

arvore_avl *rotacao_esquerda(arvore_avl *raiz) {
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
  novo_no->valor = valor;
  novo_no->esq = novo_no->dir = NULL;
  novo_no->altura_esq = novo_no->altura_dir = 0;
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
    novo_no = criar_novo_no(valor);
  } else if (valor < raiz->valor) {
    raiz->esq = inserir_no(raiz->esq, valor);
  } else {
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

arvore_avl *remover_no(arvore_avl *raiz, int valor){
  arvore_avl *aux, *aux2;
  
  if(raiz->valor == valor){
    if(raiz->esq == NULL && raiz->dir == NULL){
      free(raiz);
      return NULL;
    }
    else if(raiz->esq == NULL){
      aux = raiz->dir;
      free(raiz);
      return aux;
    }
    else if(raiz->dir == NULL){
      aux = raiz->esq;
      free(raiz);
      return aux;
    }else{
      aux = raiz->dir;
      aux2 = raiz->dir;

      //encotrar o menor filhor da direita
      while(aux->esq != NULL){
        aux = aux->esq;
      }
      
      aux->esq = raiz->esq;
      free(raiz);
      return aux2;
    }
    
  }

  return raiz;
}
