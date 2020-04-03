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
    int posicao;
    struct lista* prox;
}lista;

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

int a, b;
Grafo grafo[MAX];
int tempo;
void imprimir(lista *p){
    while(p!=NULL){
        printf("%c ",p->vertice);
        p = p->prox;
    }
}


lista* inserir(lista *cabeca, char vertice, int posicao){
    lista* aux, *p;
    aux = (lista*)malloc(sizeof(lista));
    aux->vertice = vertice;
    aux->posicao = posicao;
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
        grafo[c1].lista = inserir(grafo[c1].lista, vertices[c2],c2);
        grafo[c2].lista = inserir(grafo[c2].lista, vertices[c1],c1);
    }
    for(int o = 0; o<a;o++){
        printf("%c: ",grafo[o].vertice);
        imprimir(grafo[o].lista);
        printf("\n");
    }
}

void busca_largura(int inicio){
    int u = 0;
    for(int i=0;i<a;i++){
        if(i!= inicio){
            grafo[i].cor = 0;
            grafo[i].pai = NIL;
            grafo[i].distancia = 0;
        }
    }
    grafo[inicio].cor = 1;
    grafo[inicio].pai = NIL;
    grafo[inicio].distancia = 0;
    fila *q = NULL;
    lista *aux = NULL;
    q = push(q, inicio);
    
    while(q!=NULL){
        u = q->vertice;
        q = pop(q);
        aux = grafo[u].lista;
        while(aux!=NULL){
            if(grafo[aux->posicao].cor == 0){
                grafo[aux->posicao].cor = 1;
                grafo[aux->posicao].distancia = grafo[u].distancia + 1;
                grafo[aux->posicao].pai = grafo[u].vertice;
                q = push(q,aux->posicao);
            }
            aux = aux->prox;
        }
       grafo[u].cor = 2; 
    }
    printf("\nBusca por largura distancia apartir do vertice %c\n",grafo[inicio].vertice);
    for(int i=0;i<a;i++){
       printf("%c = %d\n",grafo[i].vertice,grafo[i].distancia);
    }
}

void visita(int u){
    grafo[u].cor = 1;
    tempo++;
    grafo[u].tempo_abertura = tempo;
    lista *aux = NULL;
    aux = grafo[u].lista;
    while(aux!=NULL){
        if(grafo[aux->posicao].cor == 0){
            grafo[aux->posicao].pai; 
            visita(aux->posicao);
        }
        aux = aux->prox;
    }
    grafo[u].cor = 3;
    tempo++;
    grafo[u].tempo_fechamento = tempo;
}

void busca_profundidade(int inicio){
    for(int i=0;i<a;i++){
        grafo[i].cor = 0;
    }
    tempo = 0;
    if(grafo[inicio].cor == 0){
            visita(inicio);
        }
    for(int i=0;i<a;i++){
        if(grafo[i].cor == 0){
            visita(i);
        }
    }
    printf("\nBusca por profundiade Ti/Tf apartir do vertice %c\n",grafo[inicio].vertice);
    
    for(int i = 0; i<a;i++){
        printf("%c = %d/%d\n",grafo[i].vertice,grafo[i].tempo_abertura,grafo[i].tempo_fechamento);
    }
}

int main(void){
    carregar_arquivo();
    //busca_largura(1);
    busca_profundidade(1);
}