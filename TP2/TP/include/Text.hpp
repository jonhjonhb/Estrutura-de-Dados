#ifndef TEXTH
#define TEXTH

#include <iostream>
#include "listaEncadeada.hpp"
#include "msgassert.h"

class Text{
  public:
    Text():_text(""),countLettersOrder(0){inicializaOrdem();}
    Text(std::string str):_text(str){}
    void setValue(std::string str){_text = str;};
    void newOrder(char letter){
      countLettersOrder++;
      orderLexografic[(int)letter] = 96 + countLettersOrder;
    };
    void createList();
    void cleanText(){
      toLowerCase();
      toRemoveSpecial();
    };
    void Imprime(std::ofstream &arqSaida){words.Imprime(arqSaida);};
    std::string Imprime(){
      return words.Imprime() + "#FIM\n";
    };
    int operator()(char letter);
  private:
    bool isEmpty(){return (_text == "") ;};
    void inicializaOrdem();
    void toLowerCase();
    void toRemoveSpecial();
    std::string _text;
    ListaEncadeada words;
    int orderLexografic[26];
    int countLettersOrder;
};

void Text::inicializaOrdem(){
  for (int i = 0; i < 26; i++){
    orderLexografic[i] = 97 + i;
  }
}

void Text::createList(){
  std::string wordInText = "";
  Word aux;
  for (char letter : _text){
    if(letter == ' '){
      aux.setWord(wordInText);
      words.InsereInicio(aux);
      wordInText = "";
      continue;
    }
    wordInText += letter;
  }
  aux.setWord(wordInText);
  words.InsereInicio(aux);
}

void Text::toLowerCase(){
  erroAssert(!isEmpty(), "[Minuscula] - não há dados para converter");
  std::string newText = "";
  for(char aux: _text){
    newText += tolower(aux);
  }
  setValue(newText);
}

void Text::toRemoveSpecial(){
  std::string newText;
  std::string lastLetter;
  for (char letter : _text){
    if (letter == ' '){
      lastLetter = newText.substr(newText.size() - 1, 1);
      if(lastLetter == "," || lastLetter == "." || lastLetter == "!" || lastLetter == " " ||
         lastLetter == "?" || lastLetter == ":" || lastLetter == ";" || lastLetter == "_"){
        newText = newText.substr(0, newText.size() - 1);
      }
    }
    newText += letter;
  }
  lastLetter = newText.substr(newText.size() - 1, 1);
  if(lastLetter == "," || lastLetter == "." || lastLetter == "!" || lastLetter == " " ||
      lastLetter == "?" || lastLetter == ":" || lastLetter == ";" || lastLetter == "_"){
    newText = newText.substr(0, newText.size() - 1);
  }
  setValue(newText);
}

int Text::operator()(char letter){
  for(int i = 0; i < 26; i++){
    if(orderLexografic[i] == (int)letter){
      return i;
    }
  }
  return 0;
}

#endif