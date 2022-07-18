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
    void inserir(int chave, Email v);
    NO *buscar(Email chave);
    NO *getRaiz(){return raiz;};
    bool remover(int chave, Email v);
    std::string consulta(Email chave);
    // void caminhar();
    Email min();
    Email max();
  private:
    NO * rightRotation(NO * head);
    int altura(NO *atual);
    int folhas(NO *atual);
    int contarNos(NO *atual);
    NO *no_sucessor(NO *apaga);
    NO *raiz;
};