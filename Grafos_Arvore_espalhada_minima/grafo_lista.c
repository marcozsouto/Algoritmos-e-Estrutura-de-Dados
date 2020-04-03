#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define NIL -1


typedef struct grafo{
    char vertice;
    int distancia;
    int pai;
    int cor;
    int tempo_abertura;
    int tempo_fechamento;
    struct lista *lista;
}Grafo;

typedef struct lista{
    char vertice;
    int peso;
    int posicao;
    struct lista* prox;
}lista;
int a, b;
Grafo grafo[MAX];
int tempo;
typedef struct fila{
    int vertice;
    struct fila* prox;
}fila;

fila *push(fila *cabeca, int vertice){
    fila *aux, *p;
    aux = (fila *)malloc(sizeof(fila));
    aux->vertice = vertice;
    if (cabeca == NULL){
        cabeca = aux;
        cabeca->prox = NULL;
    }
    else{
        p = cabeca;
        while (p->prox != NULL){
            p = p->prox;
        }
        p->prox = aux;
    }
    return cabeca;
}

fila *pop(fila *cabeca){
    int vertice;
    vertice = cabeca->vertice;
    fila *aux = NULL;
    if (cabeca == NULL || cabeca->prox == NULL){
        return NULL;
    }else{
        aux = cabeca;
        cabeca = aux->prox;
    }
    return cabeca;
}


void imprimir(lista *p){
    while(p!=NULL){
        printf("%c ",p->vertice);
        p = p->prox;
    }
}


lista* inserir(lista *cabeca, char vertice, int posicao, int peso){
    lista* aux, *p;
    aux = (lista*)malloc(sizeof(lista));
    aux->vertice = vertice;
    aux->posicao = posicao;
    aux->peso = peso;
    if(cabeca == NULL){
        cabeca = aux;
        cabeca->prox = NULL;
    }else{
        p = cabeca;
        while (p->prox != NULL){
            p = p->prox;
        }
        p->prox = aux;  
    }
    return cabeca;
}


void carregar_arquivo(void){
    FILE *arq;
    char linha[10];
    int i=0,j=0,k=0;
    int c1,c2;

    //abrir o arquivo e ler a quantidade de vertices e arestas.

    arq = fopen("arquivo.txt","r");
    fscanf(arq,"%d %d", &a, &b);
    char vertices[a];
    char arestas[b][2];
    int pesos[b];
    //guardar no vetor o nome dos vertices e das arestas.

    fscanf(arq, "%*[^\n]");
    while(fgets(linha,10,arq)!= NULL){
        if(i>0 && i<=a){
            vertices[j]=linha[0];
            j++;
        }
        if(i>a && k<b){
            arestas[k][0]=linha[0];
            arestas[k][1]=linha[1];
            pesos[k]= linha[2] - '0';
            k++;
        }
        i++;    
    }
    fclose(arq);

    //inserir arestas e vertices

    for(int l=0;l<a;l++){
        grafo[l].vertice = vertices[l];
        grafo[l].lista = NULL;

    }

    for(int m=0; m<b; m++){
        for(int n=0; n<a; n++){
            if(arestas[m][0] == vertices[n]){
                c1 = n;
            }
            if(arestas[m][1] == vertices[n]){
                c2 = n;
            }
        }

        grafo[c1].lista = inserir(grafo[c1].lista, vertices[c2],c2,pesos[m]);
        grafo[c2].lista = inserir(grafo[c2].lista, vertices[c1],c1,pesos[m]);
    }


    for(int o = 0; o<a;o++){
        printf("%c: ",grafo[o].vertice);
        imprimir(grafo[o].lista);
        printf("\n");
    }
}

void selectionSort(lista* cabeca){ 
    lista* temp = cabeca; 
  
    while (temp) { 
        lista* min = temp; 
        lista* r = temp->prox; 
        while(r){ 
            if(min->peso > r->peso){
                min = r;
            } 
            r = r->prox; 
        } 
  
        int peso = temp->peso;
        int posicao = temp->posicao;
        char vertice =temp->vertice;
        temp->peso = min->peso;
        temp->posicao = min->posicao;
        temp->vertice = min->vertice; 
        min->peso = peso;
        min->posicao = posicao;
        min->vertice = vertice;
        temp = temp->prox; 
    } 
} 

lista* concatena(lista* a, lista* b){
    lista* aux = b;
    while(aux !=NULL){
        a = inserir(a, aux->vertice, aux->posicao, aux->peso);
        aux = aux->prox;
    }  
    return a;
}

int contem(lista* cabeca, char vertice){
    lista* aux = cabeca;
    while(aux!=NULL){
        if(aux->vertice == vertice){
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}
void kruskal(){
    lista *sort = NULL;
    for(int i = 0; i < a;i++){
        sort = concatena(sort,grafo[i].lista);
    }
    selectionSort(sort);
    
    lista* final = NULL;
    for(lista* i=sort;i!=NULL;i = i->prox->prox){
        if((contem(final,i->vertice) == 0) || (contem(final,i->prox->vertice)==0)){
            final = inserir(final,i->vertice,i->posicao,i->peso);
            final = inserir(final,i->prox->vertice,i->prox->posicao,i->prox->peso);
        }
    }
    printf("Imprimi os pares de arestas que formam a arvore espalhada minima pelo algoritmo de kruskal\n");
    
    while(final!=NULL){
        printf("%c - %c\n",final->vertice, final->prox->vertice);
        final = final->prox->prox;
    }
}


int main(void){
    carregar_arquivo();
    kruskal();
}