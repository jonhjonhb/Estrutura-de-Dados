#ifndef TEXTH
#define TEXTH

#include <iostream>
#include "listaEncadeada.hpp"
#include "msgassert.h"

class Text{
  public:
    Text():_text(""){}
    ListaEncadeada* getList(){return &words;};
    void setValue(std::string str){_text = str;};
    void newOrder(char letter){tableOrder->setLetter(letter);};
    void QuickSort(){words.QuickSort();};
    void createList();
    void readInput(std::string fileNameInput, OrderLexografic &table);
    void assignmentOrder(){words.assignmentOrder(tableOrder);};
    void cleanText(){
      toLowerCase();
      toRemoveSpecial();
    };
    void Imprime(std::ofstream &arqSaida){words.Imprime(arqSaida);};
    std::string Imprime(){
      return words.Imprime() + "#FIM\n";
    };
  private:
    bool isEmpty(){return (_text == "") ;};
    void toLowerCase();
    void toRemoveSpecial();
    std::string _text;
    ListaEncadeada words;
    OrderLexografic *tableOrder;
};

void Text::readInput(std::string fileNameInput, OrderLexografic &table){
	std::string line = "",lineText = "";
	std::ifstream fileInput(fileNameInput);
	while (getline(fileInput, line) && line != ""){
		if (line == "#ORDEM"){
			while (getline(fileInput, line)){
				if (line == "#TEXTO"){break;}
				for(char letter: line){
					if(letter == ' '){continue;}
					table.setLetter(tolower(letter));
				}
			}
			while (getline(fileInput, line)){
				lineText += line;
				lineText += " ";
			}
			setValue(lineText);
		}else if (line == "#TEXTO"){
			while (getline(fileInput, line)){
				if (line == "#ORDEM"){break;}
				lineText += line;
				lineText += " ";
			}
			setValue(lineText);
			while (getline(fileInput, line)){
				for(char letter: line){
					if(letter == ' '){continue;}
					table.setLetter(tolower(letter));
				}
			}
		}
	}
	fileInput.close();
}

void Text::createList(){
  std::string wordInText = "";
  Word aux;
  for (char letter : _text){
    if(letter == ' '){
      aux.setWord(wordInText);
      aux.setOrder(tableOrder);
      words.InsereFinal(aux);
      wordInText = "";
      continue;
    }
    wordInText += letter;
  }
  aux.setWord(wordInText);
  words.InsereFinal(aux);
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

#endif