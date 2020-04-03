#include <stdio.h>
#include "avl.h"

int main(void){
  No* arvore = NULL;
  int valor = 0;
  No* aux = NULL;
  int opcao = 0;
 
  while(1){
    scanf("%d", &opcao);
    switch(opcao){
      case 1:
        scanf("%d",&valor);
        arvore = inserir(arvore,valor);
        break;
      case 2:
        Pre_order(arvore);
        printf("\n");
        break;
      case 3:
        scanf("%d",&valor);
        arvore = remover(arvore,valor);
        break;
      case 999:
        return 0; 
    }
  }
  return 0;
}
