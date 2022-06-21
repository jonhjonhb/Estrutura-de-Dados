#ifndef POKER
#define POKER

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "memlog.hpp"
#include "msgassert.h"

#define NUM_CARTAS 5

enum clasificacao { 
  Royal_Straight_Flush = 10, 
  Straight_Flush = 9, 
  Four_of_a_kind = 8, 
  Full_House = 7, 
  Flush = 6, 
  Straight = 5, 
  Three_of_a_kind = 4, 
  Two_Pairs = 3, 
  One_Pair = 2, 
  High_Card = 1, 
  Invalid = 0
};

class Carta{
  public:
    Carta():valor(0), naipe(""){}
    Carta(std::string str);
    ~Carta(){}
    // funcoes
    void apaga();
    void imprimeCarta();
    bool isEmpty(){return valor == 0 && naipe == "";};
    //getters
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
    Jogador(std::string str, int din, std::string carta[], int _id): name(str), amount(din), id(_id){setMao(carta);};
    //funcoes
    bool isEmpty(){
      LEMEMLOG((long int)(&name),sizeof(std::string),id);
      LEMEMLOG((long int)(&amount),sizeof(int),id);
      return (name == "" && amount == 0);
    };
    bool isEqualNaipe();
    void limpaMao();
    bool contemCarta(int valor);
    int numCartas(int numero);
    void debitaDinheiro(int dinheiro);
    void debitaPingo(int dinheiro);
    void ordenarCartas();
    void aumentaCartaAs();
    void diminuirCartaAs();
    //setters
    void setAtributtes(std::string _name, double _amount){
      setName(_name);
      setAmount(_amount);
    };
    void setName(std::string _name){
      ESCREVEMEMLOG((long int)(&name),sizeof(std::string),id);
      name = _name;
    };
    void setAmount(int _amount){
      ESCREVEMEMLOG((long int)(&amount),sizeof(int),id);
      amount = _amount;
    };
    void setMao(std::string strCarta[]);
    //getters
    clasificacao getClassificacao();
    std::string getName(){
      LEMEMLOG((long int)(&name),sizeof(std::string),id);
      return name;
    };
    int getValorPar(int ordem = 1);
    int getValorTripla();
    int getValorQuadra();
    int getAmount(){
      LEMEMLOG((long int)(&amount),sizeof(int),id);
      return amount;
    };
    void getValores();
  private:
    std::string name;
    int amount;
    int id;
    Carta mao[NUM_CARTAS];
    friend class Poker;
};

class Poker{
  public:
    Poker(): jogadores(NULL), pote(0), pingoMinimo(0), numPlayers(0) {}
    ~Poker(){free(jogadores);};
    void alocarJogadores();
    void iniciaJogo();
    void limparCartas();
    void zerarPote(){pote = 0;};
    void ordenarJogadores();
    void ordenarNome(int posJogadores[]);
    void confereDebito(int aposta[]);
    void fazerApostas(int aposta[]);
    void incluiJogador(Jogador *newPlayer);
    int pesquisarJogador(std::string nomeJogador);
    void leLinha(std::string str);
    void somaPote(int pingo){pote += pingo;};
    void novaRodada(std::string nome, std::string carta[]);
    void desempate(clasificacao rank, int posJogador[]);
    void setNumJogadores(int num);
    void setPingo(int valorPingoMin);
    void getVencedor(std::ofstream &arqSaida);
    int getPingo();
    int getPote(){return pote;};
    void getInfoJogadores();
  private:
    Jogador *jogadores;
    int pote;
    int pingoMinimo;
    int numPlayers;
};

#endif