#include "poker.hpp"

#define MIN_PINGO 50
#define MAX_JOGADOR 10

bool rodadaInvalida = false;

Carta::Carta(std::string str){
  valor = std::stoi(str.substr(0, str.size() - 1));
  naipe = str.substr(str.size() - 1);
};

void Carta::imprimeCarta(){
  std::cout << getValor() << getNaipe();
};

void Carta::apaga(){
  valor = 0;
  naipe = "";
};

void Jogador::getValores(){
  std::cout << getName() << " " << getAmount();
  for(int i = 0; i < NUM_CARTAS; i++){
    std::cout << " ";
    mao[i].imprimeCarta();
    LEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
    LEMEMLOG((long int)(&mao[i].naipe),sizeof(std::string),id);
  }
  std::cout << std::endl;
  return;
}

bool Jogador::isEqualNaipe(){
  LEMEMLOG((long int)(&mao[0].naipe),sizeof(std::string),id);
  LEMEMLOG((long int)(&mao[1].naipe),sizeof(std::string),id);
  LEMEMLOG((long int)(&mao[1].naipe),sizeof(std::string),id);
  LEMEMLOG((long int)(&mao[2].naipe),sizeof(std::string),id);
  LEMEMLOG((long int)(&mao[2].naipe),sizeof(std::string),id);
  LEMEMLOG((long int)(&mao[3].naipe),sizeof(std::string),id);
  LEMEMLOG((long int)(&mao[3].naipe),sizeof(std::string),id);
  LEMEMLOG((long int)(&mao[4].naipe),sizeof(std::string),id);
  return (mao[0].getNaipe() == mao[1].getNaipe()) &&
  			 (mao[1].getNaipe() == mao[2].getNaipe()) && 
  			 (mao[2].getNaipe() == mao[3].getNaipe()) &&  
				 (mao[3].getNaipe() == mao[4].getNaipe());
}

void Jogador::setMao(std::string strCarta[]){
  for(int i = 0; i < NUM_CARTAS; i++){
    mao[i] = Carta(strCarta[i]);
    ESCREVEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
    ESCREVEMEMLOG((long int)(&mao[i].naipe),sizeof(std::string),id);
  }
}

void Jogador::limpaMao(){
  for(int i = 0; i < NUM_CARTAS; i++){
    ESCREVEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
    ESCREVEMEMLOG((long int)(&mao[i].naipe),sizeof(std::string),id);
    mao[i].apaga();
  }
}

void Jogador::debitaPingo(int dinheiro){
  if(rodadaInvalida){return;}
  ESCREVEMEMLOG((long int)(&amount),sizeof(int),id);
  amount -= dinheiro;
}

void Jogador::debitaDinheiro(int dinheiro){
  ESCREVEMEMLOG((long int)(&mao[0].valor),sizeof(int),id);
  ESCREVEMEMLOG((long int)(&mao[0].naipe),sizeof(std::string),id);
  if(mao[0].isEmpty() || rodadaInvalida || dinheiro == 0){return;}
  ESCREVEMEMLOG((long int)(&amount),sizeof(int),id);
  amount -= dinheiro;
}

bool Jogador::contemCarta(int numero){
  for(int i = 0; i < NUM_CARTAS; i++){
    LEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
    if(mao[i].getValor() == numero){
      return true;
    }
  }
  return false;
}

int Jogador::numCartas(int numero){
  int i = 0, contador = 0;
  for(i = 0; i < NUM_CARTAS; i++){
    LEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
    if (mao[i].getValor() == numero){
      contador++;
    }
  }
  return contador;
}

int Jogador::getValorPar(int ordem){
  int i = 0, contador = 0;
  for (i = 14; i > 1; i--){
    if(numCartas(i) == 2)
      contador++;
    if(contador == ordem) 
      return i;
  }
  return 0;
}

int Jogador::getValorTripla(){
  for (int i = 14; i > 1; i--){
    if(numCartas(i) == 3)
      return i;
  }
  return 0;
}

int Jogador::getValorQuadra(){
  for (int i = 14; i > 1; i--){
    if(numCartas(i) == 4)
      return i;
  }
  return 0;
}

void Jogador::aumentaCartaAs(){
  LEMEMLOG((long int)(&mao[0].valor),sizeof(int),id);
  LEMEMLOG((long int)(&mao[0].naipe),sizeof(std::string),id);
  if(mao[0].isEmpty())
    return;
  for(int i = 0; i < NUM_CARTAS; i++){
    LEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
    if (mao[i].getValor() == 1){
      ESCREVEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
      mao[i].setValor(14);
    }
  }
}

void Jogador::diminuirCartaAs(){
  LEMEMLOG((long int)(&mao[0].valor),sizeof(int),id);
  LEMEMLOG((long int)(&mao[0].naipe),sizeof(std::string),id);
  if(mao[0].isEmpty())
    return;
  for(int i = 0; i < NUM_CARTAS; i++){
    LEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
    if (mao[i].getValor() == 14){
      ESCREVEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);;
      mao[i].setValor(1);
    }
  }
}

void Jogador::ordenarCartas(){
  int i = 0, j = 0, maior = 0;
  Carta aux;
  aumentaCartaAs();
  for(i = 0; i < NUM_CARTAS; i++){
    maior = i;
    for(j = i + 1; j < NUM_CARTAS; j++){
      LEMEMLOG((long int)(&mao[j].valor),sizeof(int),id);
      LEMEMLOG((long int)(&mao[maior].valor),sizeof(int),id);
      if(mao[j].getValor() > mao[maior].getValor())
        maior = j;
    }
    LEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
    LEMEMLOG((long int)(&mao[i].naipe),sizeof(std::string),id);
    ESCREVEMEMLOG((long int)(&mao[i].valor),sizeof(int),id);
    ESCREVEMEMLOG((long int)(&mao[i].naipe),sizeof(std::string),id);
    LEMEMLOG((long int)(&mao[maior].valor),sizeof(int),id);
    LEMEMLOG((long int)(&mao[maior].naipe),sizeof(std::string),id);
    ESCREVEMEMLOG((long int)(&mao[maior].valor),sizeof(int),id);
    ESCREVEMEMLOG((long int)(&mao[maior].naipe),sizeof(std::string),id);
    aux = mao[i];
    mao[i] = mao[maior];
    mao[maior] = aux;
  }
  diminuirCartaAs();
}

bool equalFour(int numero){return numero == 4;}
bool equalThree(int numero){return numero == 3;}
bool equalTwo(int numero){return numero == 2;}
bool equalOne(int numero){return numero == 1;}

clasificacao Jogador::getClassificacao(){
	bool sequencia = false, duasCartas = false;
	bool quatroCartas = false, tresCartas = false;
  int numParesCartas = 0;
	for (int i = 0; i < 14; i++){
    if(!sequencia && (!quatroCartas || !tresCartas || !duasCartas) ){
      sequencia = contemCarta(i%13+1) && contemCarta((i+1)%13+1) && contemCarta((i+2)%13+1) && contemCarta((i+3)%13+1) && contemCarta((i+4)%13+1);
    }
    if(equalFour(numCartas(i))){quatroCartas = true;}
    if(equalThree(numCartas(i))){tresCartas = true;}
    if(equalTwo(numCartas(i))){
        numParesCartas++;
        duasCartas = true;
    }
  }
  
  if(isEqualNaipe()){
		if(contemCarta(10) && contemCarta(11) && contemCarta(12) && contemCarta(13) && 
       contemCarta(1)){ // Royal Straight Flush [RSF]
			return Royal_Straight_Flush;
		}else if(sequencia){return Straight_Flush;}// Straight Flush [SF]
     else {return Flush;} // Flush [F]
	}else if(sequencia){return Straight;} // Straight [S]
  if(quatroCartas){return Four_of_a_kind;} // Four of a kind [FK]
  if(tresCartas && duasCartas){return Full_House;} // Full House [FH]
  if(tresCartas && !duasCartas){return Three_of_a_kind;} // Three of a kind [TK]
  if(equalTwo(numParesCartas)){return Two_Pairs;} // Two Pairs [TP]
  if(equalOne(numParesCartas)){return One_Pair;} // One Pair [OP]
  return High_Card;
}

void Poker::alocarJogadores(){
  jogadores = (Jogador*)malloc(numPlayers*sizeof(Jogador));
  erroAssert(jogadores!=NULL,"Malloc falhou");
}

void Poker::setNumJogadores(int num){
  erroAssert(num <= MAX_JOGADOR,"Ha mais jogadores que o permitido no jogo.");
  erroAssert(num > 0,"Nao ha jogadores para o jogo!");
  numPlayers = num;
  alocarJogadores();
}

void Poker::incluiJogador(Jogador *newPlayer){
  int i = 0;
  // LEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
  while(!(jogadores[i].isEmpty()) && (i < numPlayers)){
    i++;
    // LEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
  }
  // ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
  jogadores[i] = *newPlayer;
}

void Poker::getInfoJogadores(){
  for(int i = 0; i < numPlayers ; i++){
    jogadores[i].getValores();
  }
}

void Poker::setPingo(int valorPingoMin){
  if (valorPingoMin >= MIN_PINGO && valorPingoMin % MIN_PINGO == 0){
    pingoMinimo = valorPingoMin;
  } else {
    rodadaInvalida = true;
  }
};

int Poker::getPingo(){
  int sum = 0;
  for (int i = 0; i < numPlayers; i++){
    // ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
    jogadores[i].debitaPingo(pingoMinimo); 
    sum += pingoMinimo;
  }
  return sum;
}

void leCartas(std::string &line, std::string carta[]){
  int j = 1;
  if (line.substr(line.size() - j, 1) == " "){
    line = line.substr(0, line.size() - j);
  } 
  for (int i = 0; i < NUM_CARTAS; i++){
    carta[i] = "";
    for (j = 1; line.substr(line.size() - j, 1) != " " ; j++){}
    carta[i] = line.substr(line.size() - j + 1);
    line = line.substr(0, line.size() - j);
  }
}

void leAposta(std::string &line, int &aposta){
  int j = 1;
  if(line.substr(line.size(), 1) == " "){
    line = line.substr(0, line.size() - 1);
  }
  for (j = 1; line.substr(line.size() - j,1) != " "; j++){}
  aposta = std::stoi(line.substr(line.size() - j + 1));
  line = line.substr(0, line.size() - j);
}

void Poker::limparCartas(){
  for (int i = 0; i < numPlayers ; i++){
    // ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
    jogadores[i].limpaMao();
  }
}

void Poker::novaRodada(std::string nome, std::string carta[]){
  for (int i = 0; i < numPlayers; i++){
    // LEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
    if (jogadores[i].getName() == nome){
      // ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
      jogadores[i].setMao(carta);
      // ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
      jogadores[i].ordenarCartas();
      return;
    }
  }
}

int Poker::pesquisarJogador(std::string nomeJogador){
  for (int i = 0; i < numPlayers; i++){
    // LEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
    if (jogadores[i].getName() == nomeJogador){
      return i;
    }
  }
  return 0;
}

std::string converterClassificao(clasificacao rank){
  switch(rank){
    case High_Card:
      return "HC";
    case One_Pair:
      return "OP";
    case Two_Pairs:
      return "TP";
    case Three_of_a_kind:
      return "TK";
    case Straight:
      return "S";
    case Flush:
      return "F";
    case Full_House:
      return "FH";
    case Four_of_a_kind:
      return "FK";
    case Straight_Flush:
      return "SF";
    case Royal_Straight_Flush:
      return "RSF";
    default:
      return "";
  }
}

void Poker::desempate(clasificacao rank, int posJogador[]){
  int i = 0, j = 0, k = 0;
  for (i = 0; i < numPlayers; i++){
    // ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
    jogadores[i].aumentaCartaAs();
  }
  switch(rank){
    case High_Card:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1){
          j++;
          continue;
        }
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            break;
          for (i = 0; i < NUM_CARTAS; i++){
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() > jogadores[posJogador[k]].mao[i].getValor()){
              posJogador[k] = -1;
              break;
            }else {
              posJogador[j] = -1;
              break;
            }
          }
        }
        j++;
      }
      break;
    case One_Pair:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1){
          j++;
          continue;
        }
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            continue;
          if(jogadores[posJogador[j]].getValorPar() > jogadores[posJogador[k]].getValorPar()){
            posJogador[k] = -1;
            break;
          }else if(jogadores[posJogador[j]].getValorPar() < jogadores[posJogador[k]].getValorPar()){
            posJogador[j] = -1;
            break;
          }
          for (i = 0; i < NUM_CARTAS; i++){
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() > jogadores[posJogador[k]].mao[i].getValor()){
              posJogador[k] = -1;
              break;
            }else {
              posJogador[j] = -1;
              break;
            }
          }
        }
        j++;
      }
      break;
    case Two_Pairs:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1){
          j++;
          continue;
        }
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            break;
          if(jogadores[posJogador[j]].getValorPar() > jogadores[posJogador[k]].getValorPar()){
            posJogador[k] = -1;
            break;
          }else if(jogadores[posJogador[j]].getValorPar() < jogadores[posJogador[k]].getValorPar()){
            posJogador[j] = -1;
            break;
          }
          if(jogadores[posJogador[j]].getValorPar(2) > jogadores[posJogador[k]].getValorPar(2)){
            posJogador[k] = -1;
            break;
          }else if(jogadores[posJogador[j]].getValorPar(2) < jogadores[posJogador[k]].getValorPar(2)){
            posJogador[j] = -1;
            break;
          }
          for (i = 0; i < NUM_CARTAS; i++){
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() > jogadores[posJogador[k]].mao[i].getValor()){
              posJogador[k] = -1;
              break;
            }else {
              posJogador[j] = -1;
              break;
            }
          }
        }
        j++;
      }
      break;
    case Three_of_a_kind:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1){
          j++;
          continue;
        }
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            break;
          if(jogadores[posJogador[j]].getValorTripla() > jogadores[posJogador[k]].getValorTripla()){
            posJogador[k] = -1;
            break;
          }else if(jogadores[posJogador[j]].getValorTripla() < jogadores[posJogador[k]].getValorTripla()){
            posJogador[j] = -1;
            break;
          }
          for (i = 0; i < NUM_CARTAS; i++){
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() > jogadores[posJogador[k]].mao[i].getValor()){
              posJogador[k] = -1;
              break;
            }else {
              posJogador[j] = -1;
              break;
            }
          }
        }
        j++;
      }
      break;
    case Straight:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1){
          j++;
          continue;
        }
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            break;
          for (i = 0; i < NUM_CARTAS; i++){
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() > jogadores[posJogador[k]].mao[i].getValor()){
              posJogador[k] = -1;
              break;
            }else {
              posJogador[j] = -1;
              break;
            }
          }
        }
        j++;
      }
      break;
    case Straight_Flush:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1){
          j++;
          continue;
        }
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            break;
          LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[0].valor)),sizeof(int),jogadores[posJogador[j]].id);
          LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[0].valor)),sizeof(int),jogadores[posJogador[k]].id);
          if(jogadores[posJogador[j]].mao[0].getValor() == jogadores[posJogador[k]].mao[0].getValor())
            continue;
          LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[0].valor)),sizeof(int),jogadores[posJogador[j]].id);
          LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[0].valor)),sizeof(int),jogadores[posJogador[k]].id);
          if(jogadores[posJogador[j]].mao[0].getValor() > jogadores[posJogador[k]].mao[0].getValor()){
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[0].valor)),sizeof(int),jogadores[posJogador[j]].id);
            if(jogadores[posJogador[j]].mao[0].getValor() == 14){
              posJogador[j] = -1;
              break;
            }else{
              posJogador[k] = -1;
              break;
            }
          }else {
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[0].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[k]].mao[0].getValor() == 14){
              posJogador[k] = -1;
              break;
            }else{
              posJogador[j] = -1;
              break;
            }
          }
        }
        j++;
      }
      break;
    case Flush:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1){
          j++;
          continue;
        }
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            break;
          for (i = 0; i < NUM_CARTAS; i++){
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() > jogadores[posJogador[k]].mao[i].getValor()){
              posJogador[k] = -1;
              break;
            }else {
              posJogador[j] = -1;
              break;
            }
          }
        }
        j++;
      }
      break;
    case Full_House:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1){
          j++;
          continue;
        }
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            break;
          if(jogadores[posJogador[j]].getValorTripla() > jogadores[posJogador[k]].getValorTripla()){
            posJogador[k] = -1;
            break;
          }else if(jogadores[posJogador[j]].getValorTripla() < jogadores[posJogador[k]].getValorTripla()){
            posJogador[j] = -1;
            break;
          }
          if(jogadores[posJogador[j]].getValorPar() > jogadores[posJogador[k]].getValorPar()){
            posJogador[k] = -1;
            break;
          }else if(jogadores[posJogador[j]].getValorPar() < jogadores[posJogador[k]].getValorPar()){
            posJogador[j] = -1;
            break;
          }
        }
        j++;
      }
      break;
    case Four_of_a_kind:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1){
          j++;
          continue;
        }
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            break;
          if(jogadores[posJogador[j]].getValorQuadra() > jogadores[posJogador[k]].getValorQuadra()){
            posJogador[k] = -1;
            break;
          }else if(jogadores[posJogador[j]].getValorQuadra() < jogadores[posJogador[k]].getValorQuadra()){
            posJogador[j] = -1;
            break;
          }
          for (i = 0; i < NUM_CARTAS; i++){
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[posJogador[j]].mao[i].valor)),sizeof(int),jogadores[posJogador[j]].id);
            LEMEMLOG((long int)(&(jogadores[posJogador[k]].mao[i].valor)),sizeof(int),jogadores[posJogador[k]].id);
            if(jogadores[posJogador[j]].mao[i].getValor() > jogadores[posJogador[k]].mao[i].getValor()){
              posJogador[k] = -1;
              break;
            }else {
              posJogador[j] = -1;
              break;
            }
          }
        }
        j++;
      }
      break;
    default:
      break;
  }
  for (i = 0; i < numPlayers; i++){
    // ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(Jogador),jogadores[i].id);
    jogadores[i].diminuirCartaAs();
  }
}

void inicializaVetor(int vetor[], int n){
  for (int i = 0; i < MAX_JOGADOR; i++){
    vetor[i] = n;
  }
}

int numeroDeVencedores(int vetor[]){
  int sum = 0;
  for (int i = 0; i < MAX_JOGADOR; i++){
    if(vetor[i] != -1)
      sum++;
  }
  return sum;
}

void ordenarValidos(int posJogadores[]){
  for(int i = 0; i < MAX_JOGADOR; i++){
    if (posJogadores[i] == -1){
      for(int k = i+1; k < MAX_JOGADOR; k++){
        if (posJogadores[k] != -1){
          posJogadores[i] = posJogadores[k];
          posJogadores[k] = -1;
          break;
        }
      }
    }
  }
}

void Poker::ordenarNome(int posJogadores[]){
  int i = 0, j = 0, aux = 0;
  for(i = 0; i < numPlayers; i++){
    for (j = i+1; j < numPlayers; j++){
      if (posJogadores[i] == -1 || posJogadores[j] == -1){
        break;
      }
      if(jogadores[posJogadores[i]].getName() > jogadores[posJogadores[j]].getName()){
        aux = posJogadores[i];
        posJogadores[i] = posJogadores[j];
        posJogadores[j] = aux;
      }
    }
  }
}

void Poker::getVencedor(std::ofstream &arqSaida){  
  clasificacao ranking[numPlayers];
  int i = 0, numVencedores = 0;
  int posJogadorMaior[MAX_JOGADOR];
  inicializaVetor(posJogadorMaior, -1);
  for (i = 0; i < numPlayers; i++){
    LEMEMLOG((long int)(&(jogadores[i].mao[0].valor)),sizeof(int),jogadores[i].id);
    LEMEMLOG((long int)(&(jogadores[i].mao[0].naipe)),sizeof(std::string),jogadores[i].id);
    if (jogadores[i].mao[0].isEmpty()){
      ranking[i] = Invalid;
      continue;
    }
    ranking[i] = jogadores[i].getClassificacao();
  }
  clasificacao aux = Invalid;
  for (i = 0; i < numPlayers; i++){
    if(ranking[i] > aux){
      if (numVencedores > 0){
        inicializaVetor(posJogadorMaior, -1);
        numVencedores = 0;
      }
      aux = ranking[i];
      posJogadorMaior[numVencedores] = i;
      numVencedores++;
    }else if(ranking[i] == aux){
      posJogadorMaior[numVencedores] = i;
      numVencedores++;
    }
  }
  if(numVencedores > 1){
    desempate(ranking[posJogadorMaior[0]], posJogadorMaior);
    numVencedores = numeroDeVencedores(posJogadorMaior);
    ordenarValidos(posJogadorMaior);
  }
  if(numVencedores > 1){
    ordenarNome(posJogadorMaior);
  }
  arqSaida << numVencedores << " " << getPote()/numVencedores << " ";
  arqSaida << converterClassificao(ranking[posJogadorMaior[0]]) << "\n";
  for (i = 0; i < numPlayers; i++){
    if(posJogadorMaior[i] == -1){ continue; }
    arqSaida << jogadores[posJogadorMaior[i]].getName() << "\n";
    ESCREVEMEMLOG((long int)(&(jogadores[posJogadorMaior[i]].amount)),sizeof(int),jogadores[posJogadorMaior[i]].id);
    jogadores[posJogadorMaior[i]].amount += getPote()/numVencedores;
  }
}

void Poker::ordenarJogadores(){
  int i = 0, j = 0, maior = 0;
  Jogador aux;
  for(i = 0; i < numPlayers; i++){
    maior = i;
    for(j = i + 1; j < numPlayers; j++){
      if(jogadores[j].getAmount() > jogadores[maior].getAmount())
        maior = j;
    }
    aux = jogadores[i];
    jogadores[i] = jogadores[maior];
    jogadores[maior] = aux;
  }
}

void Poker::confereDebito(int aposta[]){
  int dinheiroApostado = 0;
  for (int i = 0; i < numPlayers; i++){
    dinheiroApostado = aposta[i] + pingoMinimo;
      if(jogadores[i].getAmount() <= dinheiroApostado || (dinheiroApostado) % MIN_PINGO != 0)
        rodadaInvalida = true;
  }
}

void Poker::fazerApostas(int aposta[]){
  for (int i = 0; i < numPlayers; i++){
    jogadores[i].debitaDinheiro(aposta[i]);
    somaPote(aposta[i]);
  }
}

void Poker::iniciaJogo(){
  int dinInicial = 0, rodadas = 0, i = 0;
  int numJogadores = 0, pingo = 0, aposta = 0,  j = 0;
  int apostaJogadores[MAX_JOGADOR];
  std::ifstream file ("entrada.txt");
  std::ofstream arqSaida("saida.txt");
  std::string strRodadaInvalida = "0 0 I";
  std::string nome = "";
  std::string line = "";
  std::string carta[NUM_CARTAS];
  char gprofSaida[] = "../temp/partidagprof.out";
  iniciaMemLog(gprofSaida);
  ativaMemLog();
  file >> rodadas >> dinInicial;
  for (i = 0; i < rodadas; i++){
    inicializaVetor(apostaJogadores, 0);
    rodadaInvalida = false;
    file >> numJogadores >> pingo;
    setPingo(pingo);
    if(i==0){
      setNumJogadores(numJogadores);
      for (j = 0; j < numJogadores; j++){
        getline(file, line);
        if(line=="") getline(file, line);
        leCartas(line, carta);
        leAposta(line, aposta);
        nome = line;
        incluiJogador(new Jogador(nome, dinInicial, carta, j));
        apostaJogadores[j] = aposta;
        jogadores[j].ordenarCartas();
      }
    }else{
      for (j = 0; j < numJogadores; j++){
        getline(file, line);
        if(line=="") getline(file, line);
        leCartas(line, carta);
        leAposta(line, aposta);
        nome = line;
        apostaJogadores[pesquisarJogador(nome)] = aposta;
        novaRodada(nome,carta);
      }
    }
    confereDebito(apostaJogadores);
    if (rodadaInvalida){
      arqSaida << "0 0 I\n";
    }else{
      somaPote(getPingo());
      fazerApostas(apostaJogadores);
      getVencedor(arqSaida);
    }
    limparCartas();
    zerarPote();
  }
  arqSaida << "####\n";
  ordenarJogadores();
  for (j = 0; j < numPlayers - 1; j++){
    arqSaida << jogadores[j].getName() << " " << jogadores[j].getAmount() << "\n";
  }
  arqSaida << jogadores[numPlayers - 1].getName() << " " << jogadores[numPlayers - 1].getAmount();
  desativaMemLog();
  finalizaMemLog();
  file.close();
  arqSaida.close();
}