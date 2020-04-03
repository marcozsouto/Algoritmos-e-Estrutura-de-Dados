#include <stdio.h>
#include <stdlib.h>
#include "rb.h"


int main(void) {
    
    No* arvore = NULL;
    int opc,n;
    while(1){
        scanf("%d",&opc);
        switch (opc){
        case 1:
            scanf("%d",&n);
            inserir(&arvore,n);
            break;
        case 2:
            Pre_order(arvore);
            printf("\n");
            break;
        case 3:
            scanf("%d",&n);
            remover(&arvore,n);
            break;
        case 999:
            return 0;
        }
    }
}
