#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

static No* no_null;

No* irmao(No* no){
  if(eh_esquerdo(no))
    return no->pai->dir;
  else
    return no->pai->esq;
}

No* pai(No* no){
  return no->pai;
}

int maior(No* raiz){
  No* aux = raiz;
  while(aux && aux->dir != NULL){
    aux = aux->dir;
  }
  return aux->valor;
}

void reajustar(No** raiz, No* no) {
  if(eh_raiz(no)) {
    if(no == no_null) {
      *raiz = NULL;
    }else{
      no->cor = PRETO;
    }
    return;
  }

  //caso 2
  if(cor(irmao(no)) == VERMELHO){
    if(eh_esquerdo(no)){
      rotacao_esquerda(raiz,no->pai);
      no->pai->cor = VERMELHO;
      no->pai->pai->cor = PRETO;
    }
    if(eh_direito(no)){
      rotacao_direita(raiz,no->pai);
      no->pai->cor = VERMELHO;
      no->pai->pai->cor = PRETO;
    }
    reajustar(raiz,no);
    return;
  }

  //caso 3
  if(cor(irmao(no)) == PRETO && cor(pai(no)) == PRETO && cor(irmao(no)->esq) == PRETO && cor(irmao(no)->dir) == PRETO){
    no->pai->cor = DUPLO_PRETO;
    irmao(no)->cor = VERMELHO;
    if(eh_esquerdo(no)){
      no->pai->esq = NULL;
    }
    if(eh_direito(no)){
      no->pai->dir = NULL;
    }
    reajustar(raiz,no->pai);
    return;
  }

  //caso 4
  if(cor(pai(no)) == VERMELHO && cor(irmao(no)) == PRETO && cor(irmao(no)->esq) == PRETO && cor(irmao(no)->dir) == PRETO){ 
    no->cor = PRETO;
    pai(no)->cor = PRETO;
    irmao(no)->cor = VERMELHO;
    if(eh_esquerdo(no)){
      no->pai->esq = NULL;
    }
    if(eh_direito(no)){
      no->pai->dir = NULL;
    }
    return;
}
  
  //caso 5
  if(eh_esquerdo(no) && cor(irmao(no))== PRETO && cor(irmao(no)->esq) == VERMELHO && cor(irmao(no)->dir) == PRETO){
    rotacao_direita(raiz,irmao(no));
    irmao(no)->cor = PRETO;
    irmao(no)->dir->cor = VERMELHO;
    reajustar(raiz,no);
    return;
  }
  if(eh_direito(no) && cor(irmao(no))== PRETO && cor(irmao(no)->dir) == VERMELHO && cor(irmao(no)->esq) == PRETO){
    rotacao_esquerda(raiz,irmao(no));
    irmao(no)->cor = PRETO;
    irmao(no)->esq->cor = VERMELHO;
    reajustar(raiz,no);
    return;
  }

  //caso 6
  if(eh_esquerdo(no) && cor(irmao(no)) == PRETO && cor(irmao(no)->dir) == VERMELHO){
    rotacao_esquerda(raiz,pai(no));
    no->pai->pai->cor = cor(pai(no));
    no->cor = PRETO;
    no->pai->cor = PRETO;
    tio(no)->cor = PRETO;
    no->pai->esq = NULL;
    return;
  }
  if(eh_direito(no) && cor(irmao(no)) == PRETO && cor(irmao(no)->esq) == VERMELHO){
    rotacao_direita(raiz,pai(no));
    no->pai->pai->cor = cor(pai(no));
    no->cor = PRETO;
    no->pai->cor = PRETO;
    tio(no)->cor = PRETO;
    no->pai->dir = NULL;
    return;
  }
}

void remover(No** raiz, int valor){
  No *temp, *pai, *novo;
  temp = *raiz;
  pai = NULL;

  while(temp != NULL && temp->valor != valor) {
    pai = temp;
    if(valor > temp->valor){
      temp = temp->dir;
    }else{
      temp = temp->esq;
    }
  }
  
  if(temp == NULL)
    return ;

  if(temp->esq != NULL && temp->dir != NULL) {
    temp->valor = maior(temp->esq);
    int valor = temp->valor;
    remover(&temp->esq, temp->valor);
    temp->valor = valor;
    return ;
    }

  if(temp->esq != NULL && temp->dir == NULL) {
    No *filho = (No*)malloc(sizeof(No));
    No *pai = (No*)malloc(sizeof(No));
    pai = temp->pai;
    filho = temp->esq;
    if(eh_raiz(temp)){
      temp->valor = filho->valor;
      temp->dir = temp->esq = NULL;
    }
    if(eh_direito(temp)){
      pai->dir = filho;
    }else{
      pai->esq = filho;
    }
    filho->pai = pai;
    filho->cor = PRETO;
    return ;
    }

  if(temp->dir != NULL && temp->esq == NULL) {
    No *filho = (No*)malloc(sizeof(No));
    No *pai = (No*)malloc(sizeof(No));
    pai = temp->pai;
    filho = temp->dir;
    if(eh_raiz(temp)){
      temp->valor = filho->valor;
      temp->dir = temp->esq = NULL;
    }
    if(eh_direito(temp)){
      pai->dir = filho;
    }else{
      pai->esq = filho;
    }
    filho->pai = pai;
    filho->cor = PRETO;
    return ;
    
    }

  if(temp->cor == VERMELHO){
    if(eh_esquerdo(temp)){
      temp->pai->esq = NULL;
    }else{
      temp->pai->dir = NULL;  
    }
    return ;          
  }
  No* no_null = malloc(sizeof(No));
  no_null->cor = DUPLO_PRETO;
  no_null->esq = NULL;
  no_null->dir = NULL;
  no_null->pai = temp->pai;
  
  if(eh_raiz(temp)){
    temp = no_null;
  }
  else if(eh_esquerdo(temp)){
    temp->pai->esq = no_null;
  }else{
    temp->pai->dir = no_null;  
  }
  reajustar(raiz, no_null);
}

void inserir(No** raiz, int valor){
  No *pai, *temp, *novo;
  temp = *raiz;
  pai = NULL;
  
  while(temp!= NULL){
    pai = temp;
    if(valor > temp->valor){
      temp = temp->dir;
    }else{
      temp = temp->esq;
    }
  }

  novo = (No*)malloc(sizeof(No));
  novo->valor = valor;
  novo->esq = novo->dir = NULL;
  novo->cor = VERMELHO;
  novo->pai = pai;

  if(*raiz != NULL){
    if(valor > pai->valor){
      pai->dir = novo;
    }else{
      pai->esq = novo;
    }
  }
  else{
    *raiz = novo;
  }
  ajustar(raiz,novo);
}

void rotacao_direita(No** raiz, No* no){
  No* aux = no->esq;
  no->esq = aux->dir;

  if(no->esq != NULL){
    no->esq->pai = no;  
  }

  if(no->pai == NULL){
    aux->pai = NULL;
    *raiz = aux;
  }else{
    aux->pai = no->pai;
    if(eh_direito(no)){
      aux->pai->dir = aux;
    }else{
      aux->pai->esq = aux;
  }
}
  aux->dir = no;
  no->pai = aux;
    
}

void rotacao_esquerda(No** raiz, No* no){
  No* aux = no->dir;
  no->dir = aux->esq;

  if(no->dir != NULL){
    no->dir->pai = no;  
  }

  if(no->pai == NULL){
    aux->pai = NULL;
    *raiz = aux;
  }else{
    aux->pai = no->pai;
    if(eh_esquerdo(no)){
      aux->pai->esq = aux;
    }else{
      aux->pai->dir = aux;
  }
}
  aux->esq = no;
  no->pai = aux;
    
}

void rotacao_esq_dir(No**raiz, No* no){
  rotacao_esquerda(raiz,no->esq);
  rotacao_direita(raiz,no);
  recolorir(no->pai);
}

void rotacao_dir_esq(No**raiz,No* no){
  rotacao_direita(raiz,no->dir);
  rotacao_esquerda(raiz,no);
  recolorir(no->pai);
}

void recolorir(No* no){
  if(no != NULL)
    no->cor = PRETO;
  if(no->dir != NULL)
    no->dir->cor = VERMELHO;
  if(no->esq != NULL)
    no->esq->cor = VERMELHO;
}

void ajustar(No** raiz, No* novo){
  if(eh_raiz(novo)){
    novo->cor = PRETO;
    return;
  }

  if(novo->pai->cor == VERMELHO){
    
    if(cor(tio(novo)) == VERMELHO){
      novo->pai->cor = PRETO;
      tio(novo)->cor = PRETO;
      novo->pai->pai->cor = VERMELHO;
      ajustar(raiz,novo->pai->pai);
      return;
    }
    
    if(cor(tio(novo)) == PRETO){
      
      if(eh_esquerdo(novo) && eh_esquerdo(novo->pai)){
        rotacao_direita(raiz,novo->pai->pai);
        recolorir(novo->pai);
        return;    
      }
      if(eh_direito(novo) && eh_direito(novo->pai)){
        rotacao_esquerda(raiz,novo->pai->pai);
        recolorir(novo->pai);
        return;
      }
      if(eh_esquerdo(novo) && eh_direito(novo->pai)){
        rotacao_dir_esq(raiz,novo->pai->pai);
        return;
      }
      if(eh_direito(novo) && eh_esquerdo(novo->pai)){
        rotacao_esq_dir(raiz,novo->pai->pai);
        return;
      }
    }
  }
}

int cor(No* no){
  if(no == NULL || no->cor == PRETO)
    return PRETO;
  else 
    return VERMELHO;
}

int eh_esquerdo(No* no){
  if(no == no->pai->esq)
    return 1;
  else
    return 0;
}

int eh_direito(No* no){
  if(no == no->pai->dir)
    return 1;
  else
    return 0;
}

No* tio(No* no){
  if(eh_esquerdo(no->pai))
    return no->pai->pai->dir;
  else  
    return no->pai->pai->esq;
}

int eh_raiz(No* no){
  if(no->pai == NULL)
    return 1;
  else
    return 0;
}


void Pre_order(No* raiz){
  if(raiz == NULL) ;
    else{
      if(raiz->cor == PRETO)
    	  printf("\x1b[30m[%d]\x1b[0m", raiz->valor);
      else
    		printf("\x1b[31m[%d]\x1b[0m", raiz->valor);  
      Pre_order(raiz->esq);
      Pre_order(raiz->dir);
    }
}
