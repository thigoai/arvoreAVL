#include <stdio.h>
#include <stdlib.h>
#include "../include/arvore_avl.h"

int main() {
    // Criando a árvore
    arvore_avl* raiz = criar_novo_no(30);
    raiz->dir = criar_novo_no(40);
    raiz->esq = criar_novo_no(20);
    raiz->dir->dir = criar_novo_no(50);
    raiz->dir->esq = criar_novo_no(35);

    printf("Árvore antes da rotação:\n");

    printf("\n ArvoreAVL em ordem: \n");
    mostrarEmOrdem(raiz);
    printf("\n ArvoreAVL pos ordem: \n");
    mostrarPosOrdem(raiz);
    printf("\n ArvoreAVL pre ordem: \n");
    mostrarPreOrdem(raiz);
    
    raiz = rotacao_esquerda(raiz);

    printf("\n ArvoreAVL em ordem: \n");
    mostrarEmOrdem(raiz);
    printf("\n ArvoreAVL pos ordem: \n");
    mostrarPosOrdem(raiz);
    printf("\n ArvoreAVL pre ordem: \n");
    mostrarPreOrdem(raiz);

    // Exibindo o novo valor da raiz
    printf("\nNovo valor da raiz: %d\n", raiz->valor);

    return 0;
}

