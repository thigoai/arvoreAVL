#include <stdio.h>
#include <stdlib.h>

typedef struct arvore_avl {
    int valor;
    int altura_dir;
    int altura_esq;

    struct arvore_avl *esq;
    struct arvore_avl *dir;

} arvore_avl;

// Função para calcular a altura de uma árvore
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
    arvore_avl *novo_raiz = raiz->dir;            // O nó à direita de 'raiz' se torna a nova raiz
    arvore_avl *subarvore_direita = novo_raiz->esq; // O nó à esquerda de 'novo_raiz' é temporariamente 'subarvore_direita'

    // Realizando a rotação à esquerda
    novo_raiz->esq = raiz;
    raiz->dir = subarvore_direita;

    // Atualizando as alturas após a rotação
    raiz->altura_esq = calcular_altura(raiz->esq);
    raiz->altura_dir = calcular_altura(raiz->dir);

    novo_raiz->altura_esq = calcular_altura(novo_raiz->esq);
    novo_raiz->altura_dir = calcular_altura(novo_raiz->dir);

    // Retornando a nova raiz
    return novo_raiz;
}

// Função para criar um nó da árvore
arvore_avl* criar_novo_no(int valor) {
    arvore_avl* novo_no = (arvore_avl*) malloc(sizeof(arvore_avl));
    novo_no->valor = valor;
    novo_no->esq = novo_no->dir = NULL;
    novo_no->altura_esq = novo_no->altura_dir = 0;
    return novo_no;
}

int main() {
    // Exemplo de uso
    arvore_avl* raiz = criar_novo_no(10);
    raiz->dir = criar_novo_no(20);
    raiz->dir->dir = criar_novo_no(30);

    // Realiza a rotação à esquerda
    raiz = rotacao_esquerda(raiz);

    // Exibe o valor da nova raiz após a rotação
    printf("Novo valor da raiz: %d\n", raiz->valor);

    return 0;
}
