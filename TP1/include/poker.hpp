#ifndef POKER
#define POKER

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <fstream>

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
    Jogador(std::string str, int din, std::string carta[]): name(str), amount(din){setMao(carta);};
    //funcoes
    bool isEmpty(){return (name == "" && amount == 0);};
    void limpaMao();
    bool contemCarta(int valor);
    int numCartas(int numero);
    void debitaDinheiro(int dinheiro);
    void debitaPingo(int dinheiro);
    void ordenarCartas();
    void aumentaCartaAs();
    void diminuirCartaAs();
    //setters
    void setAtributtes(std::string a, double b){setName(a), setAmount(b);};
    void setName(std::string a){name = a;};
    void setAmount(int b){amount = b;};
    void setMao(std::string strCarta[]);
    //getters
    clasificacao getClassificacao();
    std::string getName(){return name;};
    int getValorPar(int ocorrencia = 0);
    int getValorTripla();
    int getValorQuadra();
    int getAmount(){return amount;};
    void getValores();
  private:  
    std::string name;
    int amount;
    Carta mao[NUM_CARTAS];
    friend class Poker;
};

class Poker{
  public:
    Poker(): jogadores(NULL), pote(0), pingoMinimo(0), numPlayers(0) {}
    void alocarJogadores();
    void iniciaJogo();
    void limparCartas();
    void zerarPote(){pote = 0;};
    void ordenarJogadores();
    void incluiJogador(Jogador *newPlayer);
    void leLinha(std::string str);
    void somaPote(int pingo){pote += pingo;};
    void novaRodada(std::string nome, std::string carta[], int aposta);
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