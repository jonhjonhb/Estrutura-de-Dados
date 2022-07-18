#include <iostream>
#include <stdlib.h>
#include "Email.hpp"

using namespace std;

class NO {
  public:
    NO():esq(NULL), dir(NULL), altura(0){}
    Email item;
    NO *esq;
    NO *dir;
    int altura;
};

class ArvoreBinaria {
  public:
    ArvoreBinaria():raiz(NULL){}
    void inserir(Email v){raiz = insertUtil(raiz, v);};
    void remover(Email v){raiz = removeUtil(raiz, v);};
    NO *buscar(Email chave);
    NO *getRaiz(){return raiz;};
    std::string consulta(Email chave);
  private:
    NO * insertUtil(NO * head, Email x);
    NO * removeUtil(NO * head, Email x);
    NO * rotacaoDireita(NO * head);
    NO * rotacaoEsquerda(NO * head);
    int altura(NO *atual);
    NO *no_sucessor(NO *apaga);
    NO *raiz;
};