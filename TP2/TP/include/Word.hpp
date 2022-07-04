#ifndef WORDH
#define WORDH

#include <string>
#include <fstream>

class OrderLexografic{
  public:
    OrderLexografic():countLettersOrder(26){inicialize();};
    void setLetter(char letter){
      countLettersOrder--;
      orderLexografic[(int)letter - 97] = 97 - countLettersOrder;
    };
    int getValue(char letter) const{return orderLexografic[((int)letter) - 97];};
    int operator()(char letter) const{return orderLexografic[((int)letter) - 97];};
  private:
    void inicialize();
    int orderLexografic[26];
    int countLettersOrder;
};

class Word{
  public:
    Word():_word(""), _freq(0),tableOrder(NULL){}
    std::string getWord() const {return _word;};
    int getFrequencia() const {return _freq;};
    void setWord(std::string str);
    void setFrequencia(int number);
    void setOrder(OrderLexografic *table){tableOrder = table;};
    void operator++(){_freq++;};
    void operator=(const Word& outro);
    bool operator<(const Word& outro) const;
    bool operator<=(const Word& outro) const;
    bool operator==(const Word& outro) const;
    void imprime(std::ofstream &arqSaida) const;
    std::string imprime() const;
  private:
    std::string _word;
    int _freq;
    OrderLexografic* tableOrder;
};

void OrderLexografic::inicialize(){
  for (int i = 0; i < 26; i++){
    orderLexografic[i] = 97 + i;
  }
}

void Word::setWord(std::string str){
  _word = str;
  _freq = 1;
}

void Word::setFrequencia(int number){
  _freq = number;
}

void Word::imprime(std::ofstream &arqSaida) const {
  arqSaida << getWord() << " " << getFrequencia() << "\n";
}

std::string Word::imprime() const {  
  return getWord() + " " + std::to_string(getFrequencia()) + "\n";
}

bool Word::operator<(const Word& outro) const{
  if(tableOrder==NULL) return getWord() < outro.getWord();
	auto lhs = _word.begin();
	auto rhs = outro._word.begin();
  int lhs_val = 0, rhs_val = 0;

	for (; lhs != _word.end() && rhs != outro._word.end(); ++lhs,++rhs){
		// lhs_val = (*tableOrder)(*lhs);
		lhs_val = tableOrder->getValue(*lhs);
		// rhs_val = (*tableOrder)(*rhs);
		rhs_val = tableOrder->getValue(*rhs);
    if (lhs_val < rhs_val)
      return -1;
    else if (lhs_val > rhs_val)
      return 1;
	}

	if(lhs == _word.end()){
		if(rhs == outro._word.end()){
			return 0;
		}
		else return -1;
	}
	return 1;
}

bool Word::operator<=(const Word& outro) const {
	return (*this == outro || *this < outro);
}

bool Word::operator==(const Word& outro) const {
	return getWord() == outro.getWord();
}

void Word::operator=(const Word& outro) {
  setWord(outro.getWord());
	// _word = outro._word;
  setFrequencia(outro.getFrequencia());
  // _freq = outro._freq;
}

#endif