#include "poker.hpp"

#define MIN_PINGO 50
#define MAX_JOGADOR 10

bool rodadaInvalida = false;

Carta::Carta(std::string str){
  valor = std::stoi(str.substr(0, str.size() - 1));
  naipe = str.substr(str.size() - 1);
};

void Carta::imprimeCarta(){
  std::cout << valor << naipe;
};

void Carta::apaga(){
  valor = 0;
  naipe = "";
};

void Poker::alocarJogadores(){
  erroAssert(numPlayers <= MAX_JOGADOR,"Ha mais jogadores que o permitido no jogo.");
  erroAssert(numPlayers > 0,"Nao ha jogadores para o jogo!");
  jogadores = (Jogador*)malloc(numPlayers*sizeof(Jogador));
}

void Poker::setNumJogadores(int num){
  if(num <= MAX_JOGADOR){
    numPlayers = num;
    alocarJogadores();
  }
}

void Poker::incluiJogador(Jogador *newPlayer){
  int i = 0;
  while(!(jogadores[i].isEmpty()) && (i < numPlayers)){
    i++;
  }
  jogadores[i] = *newPlayer;
  jogadores[i].id = i;
  ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
  ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
  jogadores[i].ordenarCartas();
}

void Jogador::getValores(){
  LEMEMLOG((long int)(this),sizeof(double),id);
  std::cout << this->name << " " << this->amount;
  for(int i = 0; i < NUM_CARTAS; i++){
    std::cout << " ";
    this->mao[i].imprimeCarta();
  } 
  std::cout << std::endl;
  return;
}

bool Jogador::isEqualNaipe(){
  LEMEMLOG((long int)(this),sizeof(double),id);
  return (mao[0].getNaipe() == mao[1].getNaipe()) &&
  			 (mao[2].getNaipe() == mao[3].getNaipe()) && 
	       (mao[0].getNaipe() == mao[4].getNaipe()) && 
				 (mao[2].getNaipe() == mao[1].getNaipe());
}

void Jogador::setMao(std::string strCarta[]){
  int i = 0;
  for(i = 0; i < NUM_CARTAS; i++){
    mao[i] = Carta(strCarta[i]);
  }
}

void Jogador::limpaMao(){
  int i = 0;
  ESCREVEMEMLOG((long int)(this),sizeof(double),id);
  for(i = 0; i < NUM_CARTAS; i++){
    mao[i].apaga();
  }
}

void Jogador::debitaPingo(int dinheiro){
  if(rodadaInvalida){return;}
  ESCREVEMEMLOG((long int)(this),sizeof(double),id);
  amount -= dinheiro;
}

void Jogador::debitaDinheiro(int dinheiro){
  if(mao[0].isEmpty() || rodadaInvalida || dinheiro == 0){return;}
  // erroAssert(this->amount < dinheiro,"O jogador não possui dinheiro suficiente!");
  ESCREVEMEMLOG((long int)(this),sizeof(double),id);
  amount -= dinheiro;
}

bool Jogador::contemCarta(int numero){
  int i = 0;
  LEMEMLOG((long int)(this),sizeof(double),id);
  for(i = 0; i < NUM_CARTAS; i++){
    if (mao[i].valor == numero)
      return true;
  }
  return false;
}

int Jogador::numCartas(int numero){
  int i = 0, contador = 0;
  LEMEMLOG((long int)(this),sizeof(double),id);
  for(i = 0; i < NUM_CARTAS; i++){
    if (mao[i].valor == numero){contador++;}
  }
  return contador;
}

int Jogador::getValorPar(int ordem){
  int i = 0, contador = 0;
  LEMEMLOG((long int)(this),sizeof(double),id);
  for (i = 14; i > 1; i--){      
      if(numCartas(i) == 2)
        contador++;
      if(contador == ordem) 
        return i;
  }
  return 0;
}

int Jogador::getValorTripla(){
  int i = 0;
  LEMEMLOG((long int)(this),sizeof(double),id);
  for (i = 14; i > 1; i--){
      if(numCartas(i) == 3)
        return i;
  }
  return 0;
}

int Jogador::getValorQuadra(){
  int i = 0;
  LEMEMLOG((long int)(this),sizeof(double),id);
  for (i = 14; i > 1; i--){
      if(numCartas(i) == 4)
        return i;
  }
  return 0;
}

void Jogador::aumentaCartaAs(){
  int i = 0;
  LEMEMLOG((long int)(this),sizeof(double),id);
  if(mao[0].isEmpty())
    return;
  ESCREVEMEMLOG((long int)(this),sizeof(double),id);
  for(i = 0; i < NUM_CARTAS; i++){
    if (mao[i].getValor() == 1){
      mao[i].setValor(14);
    }
  }
}

void Jogador::diminuirCartaAs(){
  int i = 0;
  LEMEMLOG((long int)(this),sizeof(double),id);
  if(mao[0].isEmpty())
    return;
  ESCREVEMEMLOG((long int)(this),sizeof(double),id);
  for(i = 0; i < NUM_CARTAS; i++){
    if (mao[i].getValor() == 14){
      mao[i].setValor(1);
    }
  }
}

void Jogador::ordenarCartas(){
  int i = 0, j = 0, maior = 0;
  Carta aux;
  aumentaCartaAs();
  ESCREVEMEMLOG((long int)(this),sizeof(double),id);
  for(i = 0; i < NUM_CARTAS; i++){
    maior = i;
    for(j = i + 1; j < NUM_CARTAS; j++){
      if(mao[j].getValor() > mao[maior].getValor())
        maior = j;
    }
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
	bool naipesIguais = false, sequencia = false;
	bool quatroCartas = false, tresCartas = false;
	bool duasCartas = false;
  int numParesCartas = 0;
	naipesIguais = isEqualNaipe();
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

  if(naipesIguais){
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
    jogadores[i].limpaMao();
  }
}

void Poker::novaRodada(std::string nome, std::string carta[]){
  for (int i = 0; i < numPlayers; i++){
    LEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
    if (jogadores[i].getName() == nome){
      jogadores[i].setMao(carta);
      ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
      jogadores[i].ordenarCartas();
      return;
    }
  }
}

int Poker::pesquisarJogador(std::string nomeJogador){
  for (int i = 0; i < numPlayers; i++){
    LEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
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
    jogadores[i].aumentaCartaAs();
    ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
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
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
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
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            posJogador[k] = -1;
            break;
          }else if(jogadores[posJogador[j]].getValorPar() < jogadores[posJogador[k]].getValorPar()){
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            posJogador[j] = -1;
            break;
          }
          for (i = 0; i < NUM_CARTAS; i++){  
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
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
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
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
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
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
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
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
          LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
          LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
          if(jogadores[posJogador[j]].mao[0].getValor() == jogadores[posJogador[k]].mao[0].getValor())
            continue;
          LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
          LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
          if(jogadores[posJogador[j]].mao[0].getValor() > jogadores[posJogador[k]].mao[0].getValor()){
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            if(jogadores[posJogador[j]].mao[0].getValor() == 14){
              posJogador[j] = -1;
              break;
            }else{
              posJogador[k] = -1;
              break;
            }
          }else {
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
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
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
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
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
            if(jogadores[posJogador[j]].mao[i].getValor() == jogadores[posJogador[k]].mao[i].getValor())
              continue;
            LEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
            LEMEMLOG((long int)(&(jogadores[k])),sizeof(double),jogadores[k].id);
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
    jogadores[i].diminuirCartaAs();
    ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
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
    LEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
    if (jogadores[i].mao[0].isEmpty()){
      ranking[i] = Invalid;
      continue;
    }
    ranking[i] = jogadores[i].getClassificacao();
    LEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
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
    LEMEMLOG((long int)(&(jogadores[posJogadorMaior[i]])),sizeof(double),jogadores[posJogadorMaior[i]].id);
    arqSaida << jogadores[posJogadorMaior[i]].getName() << "\n";
    ESCREVEMEMLOG((long int)(&(jogadores[posJogadorMaior[i]])),sizeof(double),jogadores[posJogadorMaior[i]].id);
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
    LEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
    LEMEMLOG((long int)(&(jogadores[maior])),sizeof(double),jogadores[maior].id);
    ESCREVEMEMLOG((long int)(&(jogadores[i])),sizeof(double),jogadores[i].id);
    ESCREVEMEMLOG((long int)(&(jogadores[maior])),sizeof(double),jogadores[maior].id);
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
        incluiJogador(new Jogador(nome, dinInicial, carta));
        apostaJogadores[j] = aposta;
        jogadores[j].ordenarCartas();
        ESCREVEMEMLOG((long int)(&(jogadores[j])),sizeof(double),jogadores[j].id);
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
      if (getPote() == 1950){
        int test = i;
        if (test > 330){
          test = 0;
        }
      }
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