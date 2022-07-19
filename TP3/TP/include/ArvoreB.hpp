#include <iostream>
#include <stdlib.h>
#include "Email.hpp"

using namespace std;

class NO {
  public:
    NO():esq(NULL), dir(NULL), altura(0){}
    Email getData() const { LEMEMLOG((long int)(this),sizeof(NO*),0); return item;};
    void setData(Email const x) { ESCREVEMEMLOG((long int)(this),sizeof(NO*),0); item = x;};
    Email item;
    NO *esq;
    NO *dir;
    int altura;
};

class ArvoreBinaria {
  public:
    ArvoreBinaria():raiz(NULL){}
    void inserir(Email v){raiz = insereRecursivo(raiz, v);};
    void remover(Email v){raiz = removeRecursivo(raiz, v);};
    NO *buscar(Email chave);
    NO *getRaiz(){return raiz;};
    std::string consulta(Email chave);
  private:
    NO * insereRecursivo(NO * head, Email x);
    NO * removeRecursivo(NO * head, Email x);
    NO * rotacaoDireita(NO * head);
    NO * rotacaoEsquerda(NO * head);
    int altura(NO *atual);
    NO *no_sucessor(NO *apaga);
    NO *raiz;
};