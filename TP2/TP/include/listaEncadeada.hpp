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
    virtual void Imprime() = 0;
    virtual void Limpa() = 0;
  protected:
    int tamanho;
    friend class Word;
};

class ListaEncadeada : public Lista {
  public:
    ListaEncadeada();
    ~ListaEncadeada();
    Word GetItem(int pos);
    void SetItem(Word item, int pos);
    void InsereInicio(Word item);
    void InsereFinal(Word item);
    void InserePosicao(Word item, int pos);
    Word RemoveInicio();
    Word RemoveFinal();
    Word RemovePosicao(int pos);
    Word Pesquisa(std::string c);
    void Imprime();
    void Limpa();
  private:
    Word* primeiro;
    Word* ultimo;
    Word* Posiciona(int pos, bool antes);
};

#endif