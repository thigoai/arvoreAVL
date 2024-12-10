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

arvore_avl* rotacao_esquerda(arvore_avl* raiz) {
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

arvore_avl* rotacao_direita(arvore_avl* raiz) {
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

arvore_avl* criar_novo_no(int valor) {
    arvore_avl* novo_no = (arvore_avl*) malloc(sizeof(arvore_avl));
    novo_no->valor = valor;
    novo_no->esq = novo_no->dir = NULL;
    novo_no->altura_esq = novo_no->altura_dir = 0;
    return novo_no;
}



int main() {
    // Criando a árvore
    arvore_avl* raiz = criar_novo_no(30);
    raiz->dir = criar_novo_no(40);
    raiz->esq = criar_novo_no(20);
    raiz->dir->dir = criar_novo_no(50);
    raiz->dir->esq = criar_novo_no(35);

    // Exibindo a árvore antes da rotação
    printf("Árvore antes da rotação:\n");
    printf("        %d\n", raiz->valor);
    printf("       /   \\\n");
    printf("     %d       %d\n", raiz->esq->valor, raiz->dir->valor);
    printf("           /   \\\n");
    printf("         %d       %d\n", raiz->dir->esq->valor, raiz->dir->dir->valor);
    
    // Realizando a rotação à esquerda
    raiz = rotacao_esquerda(raiz);

    // Exibindo a árvore após a rotação
    printf("\nÁrvore após rotação à esquerda:\n");
    printf("        %d\n", raiz->valor);
    printf("       /   \\\n");
    printf("     %d       %d\n", raiz->esq->valor, raiz->dir->valor);
    printf("    /   \\\n");
    printf("  %d       %d\n", raiz->esq->esq->valor, raiz->esq->dir->valor);

    // Exibindo o novo valor da raiz
    printf("\nNovo valor da raiz: %d\n", raiz->valor);

    return 0;
}

