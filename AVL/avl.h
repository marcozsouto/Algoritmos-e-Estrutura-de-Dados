typedef struct no{
  int valor;
  int alt;
  struct no *esq, *dir;  
}No; 

No* inserir(No* raiz, int valor);
No* remover(No* raiz, int valor);
int balanceamento(No* no);
No* rotacao_esquerda(No* no);
No* rotacao_direita(No* no);
No* aloca(int valor);
int maximo(int a, int b);
int altura(No* no);
No* maximo_no(No* raiz);
No* minimo_no(No* raiz);
void Pre_order(No* raiz);
