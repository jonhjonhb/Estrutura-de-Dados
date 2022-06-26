#ifndef TEXTH
#define TEXTH

#include "listaEncadeada.hpp"

class Text{
  public:
    Text():_text(""){}
    Text(std::string str):_text(str){}
    ~Text();
  private:
    std::string _text;
    ListaEncadeada words;
};

#endif