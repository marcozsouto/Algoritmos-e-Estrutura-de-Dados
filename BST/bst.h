#include <stdio.h>
#include <stdlib.h> 

typedef struct no No;

struct no{
  int valor;
  No *esq,*dir;
};

No* antecessor(No* raiz, int valor);

No* sucessor(No* raiz, int valor);

No* buscar(No* raiz, int valor);

No* procurar_pai(No* raiz, int valor);

int altura(No* raiz);

No* minimo(No* raiz);

No* maximo(No* raiz);

No* aloca(int valor);

No* inserir(No* raiz, int valor);

No* remover(No* raiz, int valor);

void In_order(No* raiz);

void Pos_order(No* raiz);

void Pre_order(No* raiz);
