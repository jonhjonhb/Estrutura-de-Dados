#include "poker.hpp"

#define MIN_PINGO 50

Carta::Carta(std::string str){
  valor = std::stoi(str.substr(0, str.size() - 1));
  naipe = str.substr(str.size() - 1);
};

void Carta::imprimeCarta(){
  std::cout << valor << naipe;
};

void Poker::alocarJogadores(){
  // erroAssert(this->amount < 50,"O jogador não possui dinheiro suficiente!");
  jogadores = (Jogador*)malloc(numPlayers*sizeof(Jogador));
}

void Poker::setNumJogadores(int num){
  numPlayers = num;
  alocarJogadores();
}

void Poker::incluiJogador(Jogador *newPlayer){
  int i = 0;
  while(!(jogadores[i].isVazio()) && (i < numPlayers)){
    i++;
  }
  jogadores[i] = *newPlayer;
}

void Poker::leLinha(std::string str){
  
}

void Jogador::getValores(){
  std::cout << this->name << " " << this->amount;
  for(int i = 0; i < 5 ; i++){
    std::cout << " ";
    this->mao[i].imprimeCarta();
  } 
  std::cout << std::endl; 
  return;
}

void Jogador::setMao(std::string *strCarta){
  int i = 0;
  for (i = 0; i < 5; i++){
    mao[i] = Carta(strCarta[i]);
  }
}

void Jogador::limpaMao(){
  int i = 0;
  for (i = 0; i < 5; i++){
    mao[i].apaga();
  }
}

int Jogador::getPingo(){
  int pingo = 0;
  // erroAssert(this->amount < 50,"O jogador não possui dinheiro suficiente!");
  if(getAmount() == MIN_PINGO){
    amount -= MIN_PINGO;
    return MIN_PINGO;
  }
  pingo = MIN_PINGO * (rand() % (amount/MIN_PINGO) + 1); 
  amount -= pingo;
  return pingo;
}

void Poker::getInfoJogadores(){
  for(int i = 0; i < numPlayers ; i++){
    jogadores[i].getValores();
  }
  return;
}

void Poker::iniciaJogo(){
  int dinInicial = 0, rodadas = 0, i = 0;  
  int numPlayers = 0, pingo = 0, aposta = 0,  j = 0;  
  std::string nome = "";
  std::string c[NUM_CARTAS];
  srand(time(NULL));
  std::cin >> rodadas >> dinInicial;
  for (i = 0; i < rodadas; i++){
    std::cin >> numPlayers >> pingo;
    setNumJogadores(numPlayers);
    setPingo(pingo);
    for (j = 0; j < numPlayers; j++){
      std::cin >> nome >> aposta >> c[0] >> c[1] >> c[2] >> c[3] >> c[4];
      incluiJogador(new Jogador(nome, dinInicial, c));
    }
  }
  std::cout << std::endl;
  getInfoJogadores();
}
