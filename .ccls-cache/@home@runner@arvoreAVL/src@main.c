#include "../include/arvore_avl.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int contador = 0;
  arvore_avl *raiz = NULL;
  int nos[] = {15, 18 ,20, 35, 32, 38, 30, 40, 32, 45, 48, 52, 60, 50};
  char arquivo[50];

  for(int i = 0; i < 14; i++) {
      raiz = inserir_no(raiz, nos[i]);

      sprintf(arquivo, "../outputDOT/arvore_avl%d.dot", contador);

      printf("\nExportando a árvore para um arquivo DOT...\n");
      exportar_para_dot(raiz, arquivo);
      printf("Arquivo gerado em '%s'\n", arquivo);

      contador++;
  }

  return 0;
}
