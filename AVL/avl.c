#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

No* minimo_no(No* raiz){
  No* aux = raiz;
  while(aux && aux->esq != NULL){
    aux = aux->esq;
  }
  return aux;
}

No* maximo_no(No* raiz){
  No* aux = raiz;
  while(aux && aux->dir != NULL){
    aux = aux->dir;
  }
  return aux;
}

int altura(No* no){ 
  if(no == NULL) 
    return 0; 
  else
    return no->alt; 
} 
  
int maximo(int a, int b){
  if(a > b)
    return a;
  else 
    return b;
} 

No* aloca(int valor){ 
  No* no = (No*)malloc(sizeof(No)); 
  no->valor = valor; 
  no->esq   = NULL; 
  no->dir  = NULL; 
  no->alt = 1;   
  return(no); 
} 
  
No* rotacao_direita(No* no){ 
  No* aux = no->esq; 
  No*T2 = aux->dir; 
  
  aux->dir = no; 
  no->esq = T2; 
  
  no->alt = maximo(altura(no->esq), altura(no->dir))+1; 
  aux->alt = maximo(altura(aux->esq), altura(aux->dir))+1; 
  
  return aux; 
} 
  
No* rotacao_esquerda(No* no){ 
  No* aux = no->dir; 
  No* T2 = aux->esq; 
  
  aux->esq = no; 
  no->dir = T2; 
  
  no->alt = maximo(altura(no->esq), altura(no->dir))+1; 
  aux->alt = maximo(altura(aux->esq), altura(aux->dir))+1; 
  
  return aux; 
} 
  
int balanceamento(No* no){
  if(no == NULL) 
    return 0; 
  else  
    return altura(no->esq) - altura(no->dir); 
} 
  
No* inserir(No *raiz, int valor){ 
  if(raiz == NULL) 
    return(aloca(valor)); 
  
  if(valor < raiz->valor) 
    raiz->esq  = inserir(raiz->esq, valor); 
  else if(valor > raiz->valor) 
    raiz->dir = inserir(raiz->dir, valor); 
  
  raiz->alt = 1 + maximo(altura(raiz->esq),altura(raiz->dir)); 
  
  int fb = balanceamento(raiz); 
  
  if(fb > 1 && valor < raiz->esq->valor) 
    return rotacao_direita(raiz); 
  
  if(fb < -1 && valor > raiz->dir->valor) 
    return rotacao_esquerda(raiz); 
  
  if(fb > 1 && valor > raiz->esq->valor){ 
    raiz->esq =  rotacao_esquerda(raiz->esq); 
    return rotacao_direita(raiz); 
  } 
  
  if(fb < -1 && valor < raiz->dir->valor){ 
    raiz->dir = rotacao_direita(raiz->dir); 
    return rotacao_esquerda(raiz); 
  } 
  return raiz; 
} 

No* remover(No* raiz, int valor){  
  if (raiz == NULL)  
    return raiz;  
  
  if(valor < raiz->valor)  
    raiz->esq = remover(raiz->esq, valor);  
  
  else if(valor > raiz->valor)  
    raiz->dir = remover(raiz->dir, valor);  
  
  else{  
    if( (raiz->esq == NULL) || (raiz->dir == NULL) ){  
      No *temp = raiz->esq ?  
      raiz->esq :  
      raiz->dir;  
    
      if (temp == NULL){  
        temp = raiz;  
        raiz = NULL;  
      }  
      else   
        *raiz = *temp;   
        free(temp);  
    }  
    else{  
      No* temp = minimo_no(raiz->dir);  
      raiz->valor = temp->valor;  
      raiz->dir = remover(raiz->dir,temp->valor);  
      }  
    }  
  
    if (raiz == NULL)  
      return raiz;  
  
    raiz->alt = 1 + maximo(altura(raiz->esq),altura(raiz->dir));  
    int fb = balanceamento(raiz);  
  
    if(fb > 1 &&  balanceamento(raiz->esq) >= 0)  
      return rotacao_direita(raiz);  
  
    if(fb > 1 && balanceamento(raiz->esq) < 0){  
      raiz->esq = rotacao_esquerda(raiz->esq);  
      return rotacao_direita(raiz);  
    }  
    if(fb < -1 && balanceamento(raiz->dir) <= 0)  
      return rotacao_esquerda(raiz);  
   
    if(fb < -1 && balanceamento(raiz->dir) > 0){  
        raiz->dir = rotacao_direita(raiz->dir);  
        return rotacao_esquerda(raiz);  
    }  
    return raiz;  
}

void Pre_order(No* raiz){
    if(raiz != NULL){
        printf("[%d,%d]",raiz->valor,balanceamento(raiz));
        Pre_order(raiz->esq);          
        Pre_order(raiz->dir);
      }
}
