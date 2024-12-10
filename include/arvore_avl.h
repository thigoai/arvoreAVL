#pragma once

typedef struct arvore_avl {
  int valor;
  int altura;
  int altura_dir;
  int altura_esq;

  struct arvore_avl *esq;
  struct arvore_avl *dir;

} arvore_avl;

int calcular_altura(arvore_avl *arv);

arvore_avl *rotacao_esquerda(arvore_avl *raiz);

arvore_avl *rotacao_direita(arvore_avl *raiz);

arvore_avl *criar_novo_no(int valor);

arvore_avl *balancear_arvore(arvore_avl *raiz);

arvore_avl *inserir_no(arvore_avl *raiz, int valor);

arvore_avl *remover_no(arvore_avl *raiz, int valor);
