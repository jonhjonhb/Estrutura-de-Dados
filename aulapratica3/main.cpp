#include <iostream>
 
using namespace std;

class Elemento{
  public:
    Elemento() {}
  private:
    char item;
    Elemento *prox;
    friend class Pilha;
};

class Pilha{
  public:
    Pilha(): tamanho(0) {top = new Elemento();};
    ~Pilha(){ delete top;};
    int GetTamanho() {return tamanho;};
    bool Vazia() {return tamanho == 0;};
    void Empilha(char item);
    void Desempilha();
  private:
    int tamanho;
    Elemento * top;
};

void Pilha::Empilha(char item){
  Elemento *novo;
  novo = new Elemento();
  novo->item = item;
  novo->prox = top;
  top = novo;
  tamanho++;
}

void Pilha::Desempilha(){
  char aux;
  Elemento *p;
  
  if(this->Vazia()){
    return;
  } else {
    aux = top->item;
    p = top;
    top = top->prox;
    delete p;
    tamanho--;
  }
}

int main() {
  Pilha pendencias;
  char c;
  c = getchar();
  while(c != '\n'){
    if(c == '('){
      pendencias.Empilha(c);
    } else if(c == ')'){
      pendencias.Desempilha();
    }
    c = getchar();
  }
    if (!pendencias.Vazia()){
      cout << "Ainda temos " << pendencias.GetTamanho() << " assunto(s) pendente(s)!" << endl;
    } else {
      cout << "Partiu RU!" << endl;
    }
    return 0;
}