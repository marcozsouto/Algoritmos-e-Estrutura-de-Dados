#include "bst.h"

No* buscar(No* raiz, int valor){
  if(raiz == NULL){
    return NULL;
  }
  if(raiz->valor == valor){
      return raiz;
  }
  if(valor <= raiz->valor){
    return buscar(raiz->esq,valor);
  }
  if(valor > raiz->valor){
    return buscar(raiz->dir,valor);
  }  
}

No* antecessor(No* raiz, int valor){

  No* aux = buscar(raiz,valor);

  if(aux == NULL){
    return NULL;
  }

  if(aux->esq != NULL){
    return maximo(aux->esq);
  }
  else{
    No* sucessor = raiz;
    No* anterior = NULL;
    while(sucessor != aux){
      if(aux->valor > sucessor->valor){
        anterior = sucessor;
        sucessor = sucessor->dir;
      }
      else{
        sucessor = sucessor->esq;
      }
    }
    return anterior;
  }

  return NULL;
}


No* sucessor(No* raiz, int valor){
  
  No* aux = buscar(raiz,valor);
  
  if(aux == NULL){
    return NULL;
  }

  if(aux->dir != NULL){
    return minimo(aux->dir);
  }
  else{
    No* sucessor = NULL;
    No* anterior = raiz;
    
    while(anterior != aux){
      if(aux->valor < anterior->valor){
          sucessor = anterior;
          anterior = anterior->esq;
      }
      else{
        anterior = anterior->dir;
      }
    }
    return sucessor;
  }
  return NULL;
}


No* procurar_pai(No* raiz, int valor){
  if(raiz == NULL || raiz->valor == valor){
    return NULL;
  }
  No* pai = NULL;
  while(raiz != NULL){
    if(valor < raiz->valor){
      pai = raiz;
      raiz = raiz->esq;
      if(raiz == NULL){
        return NULL;
      }
    }
    else if(valor > raiz->valor){
      pai = raiz;
      raiz = raiz->dir;
      if(raiz == NULL){
        return NULL;
      }
    }
    else{
      break;
    }
  }  
  return pai;
}

int altura(No* raiz){
  
  if(raiz == NULL){
    return 0;
  }
  else{
    int esq_alt = altura(raiz->esq);
    int dir_alt = altura(raiz->dir);
    if(esq_alt > dir_alt){
      return(esq_alt + 1); 
    }
    else{
      return(dir_alt + 1);
    }
  }
}

No* minimo(No* raiz){
  No* aux = raiz;
  while(aux && aux->esq != NULL){
    aux = aux->esq;
  }
  return aux;
}

No* maximo(No* raiz){
  No* aux = raiz;
  while(aux && aux->dir != NULL){
    aux = aux->dir;
  }
  return aux;
}

No* aloca(int valor){
    No *novo = malloc(sizeof(No));
    novo->esq = novo->dir = NULL;
    novo->valor = valor;
    return novo;
}

No* inserir(No* raiz, int valor){
    if(raiz == NULL){
        raiz = aloca(valor);
        return raiz;
      }
    if(raiz->valor >= valor){
        raiz->esq = inserir(raiz->esq,valor);
      }
    else{
        raiz->dir = inserir(raiz->dir,valor);
      }
    return raiz;
}

No* remover(No* raiz, int valor){
  if(raiz == NULL){
    return raiz; 
  }
  else if(valor < raiz->valor){
    raiz->esq = remover(raiz->esq,valor);
  }
  else if(valor > raiz->valor){
    raiz->dir = remover(raiz->dir,valor);
  }
  else{
    if(raiz->esq == NULL && raiz->dir == NULL){
      free(raiz);
      raiz = NULL;
      return raiz;      
    }
    else if(raiz->esq == NULL){
      No* novo = raiz;
      raiz = raiz->dir;
      free(novo);
      return raiz;
    }
    else if(raiz->dir == NULL){
      No* novo = raiz;
      raiz = raiz->esq;
      free(novo);
      return raiz;
    }
    else{
      No* novo = minimo(raiz->dir);
      raiz->valor = novo->valor;
      raiz->dir = remover(raiz->dir,novo->valor);
    }
  }
  return raiz;
}

void In_order(No* raiz){
    if(raiz != NULL){
        In_order(raiz->esq); 
        printf("[%d]",raiz->valor); 
        In_order(raiz->dir);
      }
}

void Pos_order(No* raiz){
    if(raiz != NULL){
        Pos_order(raiz->esq); 
        Pos_order(raiz->dir);
        printf("[%d]",raiz->valor); 
      }
}

void Pre_order(No* raiz){
    if(raiz != NULL){
        printf("[%d]",raiz->valor);
        Pre_order(raiz->esq);          
        Pre_order(raiz->dir);
      }
}
