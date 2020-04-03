enum cor{VERMELHO, PRETO, DUPLO_PRETO};

typedef struct no{
  int valor;
  struct no *esq, *dir, *pai;
  enum cor cor;

}No;

void inserir(No** raiz, int valor);
void Pre_order(No* raiz);
void ajustar(No** raiz, No* novo);
int eh_raiz(No* no);
No* tio(No* no);
int eh_direito(No* no);
int eh_esquerdo(No* no);
int cor(No* no);
void recolorir(No* no);
void rotacao_dir_esq(No**raiz,No* no);
void rotacao_esq_dir(No**raiz, No* no);
void rotacao_esquerda(No** raiz, No* no);
void rotacao_direita(No** raiz, No* no);
void remover(No** raiz, int valor);
void reajustar(No** raiz,No* no);
int maior(No* raiz);
No* irmao(No* no;);