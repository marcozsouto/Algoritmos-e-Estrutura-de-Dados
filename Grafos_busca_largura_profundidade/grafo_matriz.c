#include <stdio.h>
#include <stdlib.h>
#define NIL -1
#define MAX 1000

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
            }
            else{
                grafo[l][m].incidencia = 0;
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
    }
 
}

void busca_em_largura(int vertice_inicial){
    //busca em largura
    int u = 0;

    //pintar o grafo exceto.
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < a; j++)
        {
            if (i != vertice_inicial && j != vertice_inicial)
            {
                grafo[i][j].cor = 0;
                grafo[i][j].distancia = 0;
                grafo[i][j].pai = NIL;
            }
        }
    }

    //pintar origem.
    grafo[vertice_inicial][vertice_inicial].cor = 1;
    grafo[vertice_inicial][vertice_inicial].distancia = 0;
    grafo[vertice_inicial][vertice_inicial].pai = NIL;

    //criar fila;
    fila *q = NULL;
    q = inserir(q,vertice_inicial);


    while(q!=NULL){
        u = q->vertice;
        q =  remover(q);
        for(int i=0; i< a; i++){
            if(grafo[u][i].incidencia == 1){
                if(grafo[i][i].cor == 0){
                    grafo[i][i].cor = 1;
                    grafo[i][i].pai = u;
                    grafo[i][i].distancia = grafo[u][u].distancia + 1;
                    q = inserir(q,i);            
                }
            }
        }
        grafo[u][u].cor = 3;
    }

    printf("\nBusca por largura distancia apartir do vertice %d\n",vertice_inicial);
    for(int i=0;i<a;i++){
       printf("Vertice %d = %d\n",i,grafo[i][i].distancia);
    }
}

void visita(int u){
    grafo[u][u].cor = 1;
    tempo++;
    grafo[u][u].tempo_abertura = tempo;
    for(int i=0; i<a; i++){
        if(grafo[u][i].incidencia = 1){
            if(grafo[i][i].cor == 0 ){
                grafo[i][i].pai = u;
                visita(i);
            }
        }
    }
    grafo[u][u].cor = 3;
    tempo++;
    grafo[u][u].tempo_fechamento = tempo;
}

void busca_em_profundidade(int inicio){
    for(int i = 0; i < a; i++){
        grafo[i][i].cor = 0;
        grafo[i][i].distancia = NIL;
        grafo[i][i].pai = NIL;
    }
    tempo =0;
    if(grafo[inicio][inicio].cor == 0){
            visita(inicio);
        }
    for(int j = 0; j<a; j++){
        if(grafo[j][j].cor == 0){
            visita(j);
        }
    }
    printf("\nBusca por profundiade Ti/Tf apartir do vertice %d\n",inicio);
    
    for(int i = 0; i<a;i++){
        printf("%d = %d/%d\n",i,grafo[i][i].tempo_abertura,grafo[i][i].tempo_fechamento);
    }
}

void algoritmo_kruskal(void){
}

int main(void){
    carregar_arquivo();
    busca_em_largura(1);
    busca_em_profundidade(1);

    return 0;
}