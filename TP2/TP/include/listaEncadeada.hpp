#ifndef LISTA_ENCADEADA
#define LISTA_ENCADEADA

#include "Word.hpp"

class Lista{
  public:
    Lista():tamanho(0){}
    int GetTamanho() {return tamanho;};
    virtual Word GetItem(int pos) = 0;
    bool Vazia() {return tamanho == 0;};
    virtual void SetItem(Word item, int pos) = 0;
    virtual void InsereInicio(Word item) = 0;
    virtual void InsereFinal(Word item) = 0;
    virtual void InserePosicao(Word item, int pos) = 0;
    virtual Word RemoveInicio() = 0;
    virtual Word RemoveFinal() = 0;
    virtual Word RemovePosicao(int pos) = 0;
    virtual Word Pesquisa(std::string c) = 0;
    virtual void Imprime(std::ofstream &arqSaida) = 0;
    virtual void Limpa() = 0;
  protected:
    int tamanho;
};

class TipoCelula{
  public:
    TipoCelula(){
      item.setWord("");
      item.setFrequencia(0);
      prox = NULL;
    }
    bool operator<(const TipoCelula& other) const;
    void operator=(const TipoCelula& other){item = other.item; prox = other.prox;}
    bool operator<=(const TipoCelula& other) const;
  private:
    Word item;
    TipoCelula *prox;
    friend class ListaEncadeada;
};

class ListaEncadeada : public Lista {
  public:
    ListaEncadeada();
    ~ListaEncadeada();
    void troca(int i, int j);
    Word GetItem(int pos);
    Word *getItem(int pos);
    TipoCelula *getCelula(int pos);
    void SetItem(Word item, int pos);
    void InsereInicio(Word item);
    void InsereFinal(Word item);
    void InserePosicao(Word item, int pos);
    Word RemoveInicio();
    Word RemoveFinal();
    Word RemovePosicao(int pos);
    Word Pesquisa(std::string c);
    void Imprime(std::ofstream &arqSaida);
    std::string Imprime();
    void Limpa();
    void assignmentOrder(OrderLexografic *table);
    void swapElement(TipoCelula *i, TipoCelula *j);
    void QuickSort(){Ordena(1, tamanho);}
  private:
    void Ordena(int Esq, int Dir);
    void Particao(int Esq, int Dir, int *i, int *j);
    TipoCelula* primeiro;
    TipoCelula* ultimo;
    TipoCelula* Posiciona(int pos, bool antes);
};

void ListaEncadeada::assignmentOrder(OrderLexografic *table){
  TipoCelula *p;
  p = primeiro->prox;
  while (p!=NULL) {
    p->item.setOrder(table);
    p = p->prox;
  }
}

bool TipoCelula::operator<(const TipoCelula& other) const {
	return item < other.item;
}

bool TipoCelula::operator<=(const TipoCelula& other) const {
	return item <= other.item;
}

TipoCelula* ListaEncadeada::Posiciona(int pos, bool antes=false){
  TipoCelula *p; int i;
  if ( (pos > tamanho) || (pos <= 0) )
    throw "ERRO: Posicao Invalida!";
  // Posiciona na célula anterior a desejada
  p = primeiro;
  for(i=1; i<pos; i++){
    p = p->prox;
  }
  // vai para a próxima 
  // se antes for false
  if(!antes)
    p = p->prox;
  return p;
}

ListaEncadeada::ListaEncadeada() : Lista() {
  primeiro = new TipoCelula();
  ultimo = primeiro;
}

ListaEncadeada::~ListaEncadeada(){
  Limpa();
  delete primeiro;
}

void ListaEncadeada::InsereInicio(Word item){
  TipoCelula *nova;
  nova = new TipoCelula();
  Word aux = Pesquisa(item.getWord());
  if (!(item.getWord() == aux.getWord())){
    nova->item = item;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;
    if(nova->prox == NULL)
      ultimo = nova;
  }
};

void ListaEncadeada::InsereFinal(Word item){
  TipoCelula *nova;
  nova = new TipoCelula();
  Word aux = Pesquisa(item.getWord());
  if (!(item.getWord() == aux.getWord())){
    nova->item = item;
    ultimo->prox = nova;
    ultimo = nova;
    tamanho++;
  }
};

void ListaEncadeada::InserePosicao(Word item, int pos) {
  TipoCelula *p, *nova;
  p = Posiciona(pos,true); // posiciona na célula anterior
  nova = new TipoCelula();
  nova->item = item;
  nova->prox = p->prox;
  p->prox = nova;
  tamanho++;
  if(nova->prox == NULL)
    ultimo = nova;
};

Word ListaEncadeada::GetItem(int pos){
  TipoCelula *p;
  p = Posiciona(pos);
  return p->item;
}

Word *ListaEncadeada::getItem(int pos){
  TipoCelula *p;
  p = Posiciona(pos);
  return &p->item;
}

TipoCelula *ListaEncadeada::getCelula(int pos){
  TipoCelula *p;
  p = Posiciona(pos);
  return p;
}

void ListaEncadeada::SetItem(Word item, int pos){
  TipoCelula *p;
  p = Posiciona(pos);
  p->item = item;
}

Word ListaEncadeada::RemoveInicio(){
  Word aux;
  TipoCelula *p;
  if (tamanho == 0)
    throw "ERRO: Lista vazia!";
  p = primeiro->prox;
  primeiro->prox = p->prox;
  tamanho--;
  if(primeiro->prox == NULL)
    ultimo = primeiro;
  aux = p->item;
  delete p;
  return aux;
}

Word ListaEncadeada::RemoveFinal() {
  Word aux;
  TipoCelula *p;
  if (tamanho == 0)
    throw "ERRO: Lista vazia!";
  // posiciona p na celula anterior à última
  p = Posiciona(tamanho, true);
  p->prox = NULL;
  tamanho--;
  aux = ultimo->item;
  delete ultimo;
  ultimo = p;
  return aux;
}

Word ListaEncadeada::RemovePosicao(int pos) {;
  Word aux;
  TipoCelula *p, *q;
  if (tamanho == 0)
    throw "ERRO: Lista vazia!";
  // posiciona p na celula anterior à pos
  p = Posiciona(pos, true);
  q = p->prox;
  p->prox = q->prox;
  tamanho--;
  aux = q->item;
  delete q;
  if(p->prox == NULL)
    ultimo = p;
  return aux;
}

Word ListaEncadeada::Pesquisa(std::string c) {
  Word aux;
  TipoCelula *p;
  if (tamanho == 0) return aux;
  p = primeiro->prox;
  aux.setWord("");
  while (p!=NULL) {
    if (p->item.getWord() == c) {
      ++p->item;
      aux = p->item;
      break;
    }
    p = p->prox;
  }
  return aux;
};

void ListaEncadeada::Imprime(std::ofstream &arqSaida) {
  TipoCelula *p;
  p = primeiro->prox;
  while (p!=NULL) {
    p->item.imprime(arqSaida);
    p = p->prox;
  }
};

std::string ListaEncadeada::Imprime() {
  TipoCelula *p;
  std::string aux = "";
  p = primeiro->prox;
  while (p!=NULL) {
    aux = aux + p->item.imprime();
    p = p->prox;
  }
  return aux;
};

void ListaEncadeada::Limpa() {
  TipoCelula *p;
  p = primeiro->prox;
  while (p!=NULL) {
    primeiro->prox = p->prox;
    delete p;
    p = primeiro->prox;
  }
  ultimo = primeiro;
  tamanho = 0;
};

void ListaEncadeada::Ordena(int Esq, int Dir){
  int i, j;
  Particao(Esq, Dir, &i, &j);
  if (Esq < j) Ordena(Esq, j);
  if (i < Dir) Ordena(i, Dir);
}

void ListaEncadeada::Particao(int Esq, int Dir, int *i, int *j){
  TipoCelula *x, *celJ, *celI;
  *i = Esq; *j = Dir;
  x = Posiciona((*i + *j)/2); /* obtem o pivo x */
  do {
    celI = Posiciona(*i);
    while (!(x->item <= celI->item)) {
      if (*i < tamanho) {
        (*i)++;
      } else {break;}
      celI = Posiciona(*i);
    }
    celJ = Posiciona(*j);
    while (x->item < celJ->item) {
      if (*j > 1) {
        (*j)--;
      } else {break;}
      celJ = Posiciona(*j);
    }
    if (*i < *j) {
      // swapElement(Posiciona(*i, true), Posiciona(*j, true));
      troca(*i,*j);
      // w = A->posiciona(*i, false);
      // A->removePosicao(*i);
      // A->inserePosicao(A->posiciona((*j)-1, false)->item, *i);
      // //A[*i] = A[*j]; 
      // A->removePosicao(*j);
      // A->inserePosicao(w->item, (*j)-1);
      //A[*j] = w;
      (*i)++; 
      (*j)--;
    }
  } while (*i <= *j);
}

void ListaEncadeada::swapElement(TipoCelula *i, TipoCelula *j){
  TipoCelula *auxI, *auxJ;
  auxI = i;
  auxJ = j;
  auxI->prox = j->prox;
  auxI->prox->prox = i->prox->prox;
  auxJ->prox = i->prox;
  auxJ->prox->prox = j->prox->prox;
  i = auxI;
  j = auxJ;
}

void ListaEncadeada::troca(int i, int j) {
  TipoCelula *x, *y, *p, *q, *r, *s;
  // x e y as cel. anterior
  x = Posiciona(i, true);
  y =  Posiciona(j, true);
  // p e q sao as cel. que quero torcar
  p = x->prox; 
  q = y->prox;
  // r e s as cel. seguintes
  r = p->prox;
  s = q->prox;
                
  x->prox = q;
  q->prox = r;

  y->prox = p;
  p->prox = s;
}

#endif