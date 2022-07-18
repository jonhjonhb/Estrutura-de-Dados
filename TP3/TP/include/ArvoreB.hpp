#include <iostream>
#include <stdlib.h>
#include "Email.hpp"

using namespace std;

class NO {
  public:
    NO():esq(NULL), dir(NULL), altura(0){}
    int getAltura() const {return altura;};
    Email item;
    NO *esq;
    NO *dir;
    int altura;
};

class ArvoreBinaria {
  public:
    ArvoreBinaria():raiz(NULL){}
    void inserir(Email v);
    NO *buscar(Email chave);
    NO *getRaiz(){return raiz;};
    bool remover(Email v);
    std::string consulta(Email chave);
  private:
    NO * rotacaoDireita(NO * head);
    NO * rotacaoEsquerda(NO * head);
    int altura(NO *atual);
    NO *no_sucessor(NO *apaga);
    NO *raiz;
};