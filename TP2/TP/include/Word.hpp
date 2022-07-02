#ifndef WORDH
#define WORDH

#include <string>
#include <fstream>

class Word{
  public:
    Word():_word(""), _freq(0){}
    Word(std::string str, int freq):_word(str), _freq(freq){}
    std::string getWord(){return _word;};
    int getFrequencia(){return _freq;};
    void setWord(std::string str);
    void setFrequencia(int number);
    void operator++(){_freq++;};
    void imprime(std::ofstream &arqSaida);
    std::string imprime();
  private:
    std::string _word;
    int _freq;
};

void Word::setWord(std::string str){
  _word = str;
  _freq = 1;
}

void Word::setFrequencia(int number){
  _freq = number;
}

void Word::imprime(std::ofstream &arqSaida){
  arqSaida << getWord() << " " << getFrequencia() << "\n";
}

std::string Word::imprime(){  
  return getWord() + " " + std::to_string(getFrequencia()) + "\n";
}

#endif