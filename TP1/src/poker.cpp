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
  for(int i = 0; i < NUM_CARTAS; i++){
    std::cout << " ";
    this->mao[i].imprimeCarta();
  } 
  std::cout << std::endl; 
  return;
}

void Jogador::setMao(std::string *strCarta){
  int i = 0;
  for (i = 0; i < NUM_CARTAS; i++){
    mao[i] = Carta(strCarta[i]);
  }
}

void Jogador::limpaMao(){
  int i = 0;
  for (i = 0; i < NUM_CARTAS; i++){
    mao[i].apaga();
  }
}

void Jogador::debitaDinheiro(int dinheiro){
  // erroAssert(this->amount < dinheiro,"O jogador não possui dinheiro suficiente!");
  amount -= dinheiro;
}

bool Jogador::contemCarta(int numero){
  int i = 0;
  for (i = 0; i < NUM_CARTAS; i++){
    if (mao[i].valor == numero)
      return true;
  }
  return false;
}

int Jogador::numCartas(int numero){
  int i = 0, contador = 0;
  for (i = 0; i < NUM_CARTAS; i++){
    if (mao[i].valor == numero){contador++;}
  }
  return contador;
}

bool equalFour(int numero){return numero == 4;}
bool equalThree(int numero){return numero == 3;}
bool equalTwo(int numero){return numero == 2;}
bool equalOne(int numero){return numero == 1;}

std::string Jogador::getClassificacao(){
	bool naipesIguais = false, sequencia = false;
	bool quatroCartas = false, tresCartas = false;
	bool duasCartas = false;
  int numParesCartas = 0;
	naipesIguais = (mao[0].getNaipe() == mao[1].getNaipe()) &&
	 							 (mao[2].getNaipe() == mao[3].getNaipe()) && 
								 (mao[0].getNaipe() == mao[4].getNaipe()) && 
								 (mao[2].getNaipe() == mao[1].getNaipe());
	for (int i = 1; i < 14; i++){
    if(!sequencia){
      sequencia = this->contemCarta(i%13) && this->contemCarta((i+1)%13) && this->contemCarta((i+2)%13) && this->contemCarta((i+3)%13) && this->contemCarta((i+4)%13);
    }
    if(equalFour(this->numCartas(i))){quatroCartas = true;}
    if(equalThree(this->numCartas(i))){tresCartas = true;}
    if(equalTwo(this->numCartas(i))){
        numParesCartas++;
        duasCartas = true;
    }
  }

  if(naipesIguais){
		if(this->contemCarta(10) && this->contemCarta(11) && this->contemCarta(12) && this->contemCarta(13) && 
       this->contemCarta(1)){ // Royal Straight Flush [RSF]
			return "RSF";
		}else if(sequencia){return "SF";}// Straight Flush [SF]
     else {return "F";} // Flush [F]
	}else{ if(sequencia){return "S";} } // Straight [S]
  
  if(quatroCartas){return "FK";} // Four of a kind [FK]
  if(tresCartas && duasCartas){return "FH";} // Full House [FH]
  if(tresCartas && !duasCartas){return "TK";} // Three of a kind [TK]
  if(equalTwo(numParesCartas)){return "TP";} // Two Pairs [TP]
  if(equalOne(numParesCartas)){return "OP";} // One Pair [OP]
  return "";
}

void Poker::getInfoJogadores(){
  for(int i = 0; i < numPlayers ; i++){
    jogadores[i].getValores();
  }
}

void leCartas(std::string *line, std::string *carta){
  int j = 1;
  for (int i = 0; i < NUM_CARTAS; i++){
    carta[i] = "";
    for (j = 1; line->substr(line->size() - j, 1) != " " ; j++){}
    carta[i] = line->substr(line->size() - j + 1);
    *line = line->substr(0, line->size() - j);
  }
}

void leAposta(std::string *line, int *aposta){
  int j = 1;
  if(line->substr(line->size(), 1) == " "){
    *line = line->substr(0, line->size() - 1);
  }
  for (j = 1; line->substr(line->size() - j,1) != " "; j++){}
  *aposta = std::stoi(line->substr(line->size() - j + 1));
  *line = line->substr(0, line->size() - j);
}

void Poker::iniciaJogo(){
  int dinInicial = 0, rodadas = 0, i = 0;
  int numPlayers = 0, pingo = 0, aposta = 0,  j = 0;  
  std::ifstream file ("entrada.txt");
  std::string nome = "";
  std::string line = "";
  std::string carta[NUM_CARTAS];
  file >> rodadas >> dinInicial;
  srand(time(NULL));
  for (i = 0; i < rodadas; i++){
    file >> numPlayers >> pingo;
    setNumJogadores(numPlayers);
    setPingo(pingo);
    for (j = 0; j < numPlayers; j++){
      getline(file, line);
      if(line=="") getline(file, line);
      leCartas(&line, carta);
      leAposta(&line, &aposta);
      nome = line;
      incluiJogador(new Jogador(nome, dinInicial, carta));
    }
  }
  file.close();
  std::cout << std::endl;
  getInfoJogadores();
}