#include <stdio.h>
#include <stdlib.h>

typedef struct arvore_avl {
    int valor;
    int altura_dir;
    int altura_esq;

    struct arvore_avl *esq;
    struct arvore_avl *dir;

} arvore_avl;

int calcular_altura(arvore_avl* arv) {
    if (arv == NULL) {
        return 0;
    }
    int altura_esq = arv->esq ? arv->esq->altura_esq : 0;
    int altura_dir = arv->dir ? arv->dir->altura_dir : 0;
    return (altura_esq > altura_dir ? altura_esq : altura_dir) + 1;
}

// Função de rotação à esquerda
arvore_avl* rotacao_esquerda(arvore_avl* raiz) {
    arvore_avl *novo_raiz = raiz->dir;           
    arvore_avl *subarvore_direita = novo_raiz->esq; 

    novo_raiz->esq = raiz;
    raiz->dir = subarvore_direita;

    raiz->altura_esq = calcular_altura(raiz->esq);
    raiz->altura_dir = calcular_altura(raiz->dir);

    novo_raiz->altura_esq = calcular_altura(novo_raiz->esq);
    novo_raiz->altura_dir = calcular_altura(novo_raiz->dir);

    return novo_raiz;
}

arvore_avl* criar_novo_no(int valor) {
    arvore_avl* novo_no = (arvore_avl*) malloc(sizeof(arvore_avl));
    novo_no->valor = valor;
    novo_no->esq = novo_no->dir = NULL;
    novo_no->altura_esq = novo_no->altura_dir = 0;
    return novo_no;
}

int main() {
    arvore_avl* raiz = criar_novo_no(10);
    raiz->dir = criar_novo_no(20);
    raiz->dir->dir = criar_novo_no(30);

    raiz = rotacao_esquerda(raiz);

    printf("Novo valor da raiz: %d\n", raiz->valor);

    return 0;
}
