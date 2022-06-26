#ifndef WORDH
#define WORDH

#include <string>

class Word{
  public:
    Word():_word(""), _freq(0){}
    Word(std::string str, int freq):_word(str), _freq(freq){}
    ~Word();
  private:
    std::string _word;
    int _freq;
};

#endif