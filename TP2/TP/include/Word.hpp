#ifndef WORDH
#define WORDH

#include <string>

class Word{
  public:
    Word():_word(""), _freq(0){}
    Word(std::string str, int freq):_word(str), _freq(freq){}
    ~Word();
    std::string getWord(){return _word;};
    int getFrequencia(){return _freq;};
    void setWord(std::string str);
    void setFrequencia(int number);
    void operator++(){_freq++;};
  private:
    std::string _word;
    int _freq;
};

void Word::setWord(std::string str){
  _word = str;
}

void Word::setFrequencia(int number){
  _freq = number;
}

#endif