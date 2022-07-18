#include <iostream>
#include "ArvoreB.hpp"

using namespace std;

class HashLista {
  public:
    HashLista(int n);
    int insere(int chave, Email v);
    bool apaga(int chave, Email v);
    int busca(int chave, Email v);
    std::string request(std::string metod, int U, int E, std::string msg);
  private:
    int funcaohash(int chave);
    ArvoreBinaria *avl;
    int tam_max;
};