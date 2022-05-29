#ifndef POKER
#define POKER

#include <iostream>
#include <cstring>
#include <cstdlib>

#define NUM_CARTAS 5

class Carta{
  public:
    Carta():valor(0), naipe(""){}
    Carta(std::string str);
    ~Carta(){}
    // funcoes
    void apaga(){delete this;};
    void imprimeCarta();
    //getters
    Carta getCarta(){return *this;};
    int getValor(){return valor;};
    std::string getNaipe(){return naipe;};
    //setters
    void setValor(int x){valor = x;};
    void setNaipe(std::string strNaipe){naipe = strNaipe;};
  private:
    int valor;
    std::string naipe;
    friend class Jogador;
    friend class Poker;
};

class Jogador{
  public:
    Jogador(): name(""), amount(0) {}
    Jogador(std::string str, int din): name(str), amount(din) {}
    Jogador(std::string str, int din, std::string *c): name(str), amount(din){setMao(c);};
    //funcoes
    bool isVazio(){return (name == "" && amount == 0);};
    void limpaMao();
    //setters
    void setAtributtes(std::string a, double b){setName(a), setAmount(b);};
    void setName(std::string a){name = a;};
    void setAmount(int b){amount = b;};
    void setMao(std::string *strCarta);
    //getters
    std::string getName(){return name;};
    int getAmount(){return amount;};
    void getValores();
    int getPingo();
  private:  
    std::string name;
    int amount;
    Carta mao[5];
    friend class Poker;
};

class Poker{
  public:
    Poker(): jogadores(NULL), pote(0), pingoMinimo(0), numPlayers(0) {}
    void alocarJogadores();
    void iniciaJogo();
    void incluiJogador(Jogador *newPlayer);
    void leLinha(std::string str);
    void setNumJogadores(int num);
    void setPingo(int valorPingoMin){pingoMinimo = valorPingoMin;};
    void somaPote(int pingo){pote += pingo;};
    void zerarPote(){pote = 0;};
    int getPote(){return pote;};
    void getInfoJogadores();
  private:
    Jogador *jogadores;
    int pote;
    int pingoMinimo;
    int numPlayers;
};

#endif