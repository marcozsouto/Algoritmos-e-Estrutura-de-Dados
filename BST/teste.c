#include "bst.h"

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
        In_order(arvore);
        printf("\n");
        break;
      case 4:
        Pos_order(arvore);
        printf("\n");
        break;
      case 5:
        scanf("%d",&valor);
        arvore = remover(arvore,valor);
        break;
      case 6:
        aux = maximo(arvore);
        printf("[%d]\n",aux->valor);
        break;
      case 7:
        aux = minimo(arvore);
        printf("[%d]\n",aux->valor);
        break;
      case 8:
        printf("%d\n",altura(arvore));
        break;
      case 9:
        scanf("%d",&valor);
        aux = procurar_pai(arvore,valor);
        if(aux == NULL){
          printf("-1\n");
          break;
        }  
        printf("%d\n",aux->valor);
        break;
      case 10:
        scanf("%d",&valor);
        aux = sucessor(arvore,valor);
        if(aux == NULL){
          printf("-1\n");
          break;
        }
        printf("%d\n",aux->valor);
        break;
      case 11:
        scanf("%d",&valor);
        aux = antecessor(arvore,valor);
        if(aux == NULL){
          printf("-1\n");
          break;
        }
        printf("%d\n",aux->valor);
        break;
      case 999:
        return 0; 
    }
  }
  return 0;
}
