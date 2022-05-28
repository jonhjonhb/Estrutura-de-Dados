#include <iostream>

using namespace std;

class TipoNo {
  public:
    TipoNo();
    TipoNo(int a): TipoNo(), item(a) {}
  private:
    int item;
    TipoNo *esq;
    TipoNo *dir;
    friend class ArvoreBinaria;
    friend class Elemento;
};

class Elemento{
  private:
    TipoNo *cel;
    Elemento *prox;
    friend class Fila;
    friend class FilaArranjo;
  public:
    Elemento(): prox(NULL), cel(NULL) {}
    Elemento(TipoNo *a): cel(a), prox(NULL) {}
    int GetChave(){ return cel->item;}
    void SetItem(int chave){cel->item = chave;}
    TipoNo *GetNo(){return cel;}
};

class Fila {
  public:
    Fila() {tamanho = 0;}
    int GetTamanho() {return tamanho;}
    virtual bool Vazia() {return tamanho == 0;}
    virtual void Enfileira(TipoNo *itemNovo) = 0;
    virtual TipoNo Desenfileira() = 0;
    virtual void Limpa() = 0;
  protected:
    int tamanho;
};

class FilaArranjo : public Fila{
  public:
    FilaArranjo();
    void Enfileira(TipoNo *itemNovo);
    TipoNo Desenfileira();
    void Limpa();
  private:
    int frente;
    int tras;
    Elemento *itens;
};

void FilaArranjo::Enfileira(TipoNo *itemNovo){
  if (itemNovo == NULL)
    throw "Item vazio!";
  Elemento *novo;
  novo = new Elemento(itemNovo);
  tras > 0 ? itens[tras - 1].prox = novo : 0;
  itens[tras] = *novo;
  tras = tras + 1;
  tamanho++;
}

TipoNo FilaArranjo::Desenfileira(){
  Elemento *aux;
  if (tamanho == 0)
    throw "Fila está vazia!";
  aux = &itens[frente];
  tamanho--;
  return *aux->cel;
}

FilaArranjo::FilaArranjo() : Fila(){
  frente = 0;
  tras = 0;
}

void FilaArranjo::Limpa() {
  delete itens;
  frente = 0;
  tras = 0;
  tamanho = 0;
}

TipoNo::TipoNo(){
  item = -1;
  esq = NULL;
  dir = NULL;
}

class ArvoreBinaria {
  public:
    ArvoreBinaria(): raiz(NULL) {}
    ~ArvoreBinaria(){ Limpa();};
    void Insere(Elemento item);
    void Caminha(int tipo);
    void Limpa();
  private:
    void InsereRecursivo(TipoNo* &p, Elemento item);
    void ApagaRecursivo(TipoNo* p);
    void PorNivel();
    void PreOrdem(TipoNo* p);
    void InOrdem(TipoNo* p);
    void PosOrdem(TipoNo* p);
    void CaminhaNivel();
    TipoNo *raiz;
};

void ArvoreBinaria::Insere(Elemento item){
  InsereRecursivo(raiz,item);
}

void ArvoreBinaria::InsereRecursivo(TipoNo* &p, Elemento item){
  if(p==NULL){
    p = new TipoNo();
    p->item = item.GetChave();
  } else{
    if(item.GetChave() < p->item)
      InsereRecursivo(p->esq, item);
    else
      InsereRecursivo(p->dir, item);
  }
}

void ArvoreBinaria::CaminhaNivel(){
  FilaArranjo F; // fila de apontadores para nos
  TipoNo *p;
  F.Enfileira(raiz);
  while(!F.Vazia()) {
    *p = F.Desenfileira();
    if(p!=NULL) {
      F.Enfileira(p->esq);
      F.Enfileira(p->dir);
    }
  }
}

void ArvoreBinaria::Limpa(){
  ApagaRecursivo(raiz);
  raiz = NULL;
}

void ArvoreBinaria::ApagaRecursivo(TipoNo *p){
  if(p!=NULL){
    ApagaRecursivo(p->esq);
    ApagaRecursivo(p->dir);
    delete p;
  }
}

int main() {
  int C;
  int i, j, num;
  
  cin >> C;
  int N[C];
  if (C > 1000) { return 0;};
  
  ArvoreBinaria Arvore[C];
  FilaArranjo f[C];
  Elemento elem[C][500];
  for (j = 0; j < C; j++){
    cin >> N[j];
    for (i = 0; i < N[j]; i++){
      cin >> num;
      Arvore[j].Insere(TipoNo(num));
    }
  }
  for (j = 0; j < C; j++)
    for (i = 0; i < N[j]; i++)

  TipoNo aux;
  for (i = 1; i <= C; i++){
    cout << "Case " << i << ":" << endl;
    for (int j = 0; j < f[i].GetTamanho(); j++){
      // aux = f[i].Desenfileira();
    }
    cout << endl;
  }
  return 0;
}