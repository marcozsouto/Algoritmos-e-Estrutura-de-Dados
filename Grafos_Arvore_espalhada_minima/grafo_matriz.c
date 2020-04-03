#include <stdio.h>
#include <stdlib.h>
#define NIL -1
#define MAX 1000
typedef struct aresta{
    int vertice[2];
    int peso;
}aresta;
typedef struct grafo{
    int cor;
    int incidencia;
    int distancia;
    int tempo_abertura;
    int tempo_fechamento; 
    int pai;
    int peso;
}Grafo;

typedef struct fila{
    int vertice;
    struct fila *prox;
}fila;

int a, b;
Grafo grafo[MAX][MAX];
int tempo;

fila *inserir(fila *cabeca, int vertice){
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

fila *remover(fila *cabeca){
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

void carregar_arquivo(void){
    FILE *arq;
    int c1, c2;
    char linha[10];
    int i = 0, j = 0, k = 0;

    //abrir o arquivo e ler a quantidade de vertices e arestas.

    arq = fopen("arquivo.txt", "r");
    fscanf(arq, "%d %d", &a, &b);
    char vertices[a];
    char arestas[b][2];
    int pesos[b];

    //guardar no vetor o nome dos vertices e das arestas.

    fscanf(arq, "%*[^\n]");
    while (fgets(linha, 10, arq) != NULL){
        if (i > 0 && i <= a){
            vertices[j] = linha[0];
            j++;
        }
        if (i > a && k < b){
            arestas[k][0] = linha[0];
            arestas[k][1] = linha[1];
            pesos[k]= linha[2] - '0';
            k++;
        }
        i++;
    }

    fclose(arq);

    //criar grafo e inicializar


    for (int l = 0; l < a; l++){
        for (int m = 0; m < a; m++){
            if (l == m){
                grafo[l][m].incidencia = 1;
                grafo[l][m].peso = 0;
            }
            else{
                grafo[l][m].incidencia = 0;
                grafo[l][m].peso = 0;
            }
        }
    }

    

    //inserir as arestas

    for (int n = 0; n < b; n++){
        for (int o = 0; o < a; o++){
            if (arestas[n][0] == vertices[o]){
                c1 = o;
            }
            if (arestas[n][1] == vertices[o]){
                c2 = o;
            }
        }
        grafo[c1][c2].incidencia = 1;
        grafo[c2][c1].incidencia = 1;
        grafo[c1][c2].peso = pesos[n];
        grafo[c2][c1].peso = pesos[n];
    
    }
 
}

void selection_sort(aresta vet[], int tam) { 
  int i, j, min;
  aresta aux;
  for (i = 0; i < (tam-1); i++){
     min = i;
     for (j = (i+1); j < tam; j++) {
       if(vet[j].peso < vet[min].peso) 
         min = j;
     }
     if (vet[i].peso != vet[min].peso) {
       aux = vet[i];
       vet[i] = vet[min];
       vet[min] = aux;
     }
  }

}

int contem(aresta vet[], int d){
    int aux = 0;
    for(int i=0;i<a;i++){
        if(vet[i].vertice[0] == d ||vet[i].vertice[1] == d){
            return 1;
        }
    }
    return 0;
}

void algoritmo_kruskal(void){
    aresta arestas[b];
    int k=0;
    for(int i=0;i<a;i++){
        for(int j=0;j<a;j++){
            if(j!=i && grafo[i][j].peso !=0 && i>j){
                arestas[k].vertice[0] = j;
                arestas[k].vertice[1] = i;
                arestas[k].peso = grafo[i][j].peso; 
                k++;
            }
        }
    }
    selection_sort(arestas,b);
    aresta final[b];
    
    //limpar vetor com resultado
    for(int i=0;i<b;i++){
        final[i].peso = NIL;
        final[i].vertice[0] = final[i].vertice[1] = NIL;
    }
    

    int l = 0;
    for(int i=0;i<b;i++){
        if(contem(final,arestas[i].vertice[0]) == 0 || contem(final,arestas[i].vertice[1]) == 0){
            final[l].vertice[0] = arestas[i].vertice[0];
            final[l].vertice[1] = arestas[i].vertice[1];
            final[l].peso = arestas[i].peso;
            l++;
        }
    }

    printf("Imprimi os pares de arestas que formam a arvore espalhada minima pelo algoritmo de kruskal\n");
    for(int i=0;i<l;i++){
        printf("%d - %d =>%d\n",final[i].vertice[0],final[i].vertice[1],final[i].peso);
    } 
}



int main(void){
    carregar_arquivo();
    algoritmo_kruskal();
    return 0;
}