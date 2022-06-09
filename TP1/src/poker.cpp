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
  // erroAssert(this->amount < 50,"O jogador não possui dinheiro suficiente!");
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
  jogadores[i].ordenarCartas();
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

void Jogador::setMao(std::string strCarta[]){
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

void Jogador::debitaPingo(int dinheiro){
  // erroAssert(this->amount < dinheiro,"O jogador não possui dinheiro suficiente!");
  amount -= dinheiro;
}

void Jogador::debitaDinheiro(int dinheiro){
  if(mao[1].isEmpty()){return;}
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

int Jogador::getValorPar(int ordem = 1){
  int i = 0, contador = 0;
  for (i = 14; i > 0; i--){      
      if(numCartas(i) == 2)
        contador++;
      if(contador == ordem) 
        return i;
  }
}

int Jogador::getValorTripla(){
  int i = 0;
  for (i = 1; i < 15; i--){      
      if(numCartas(i) == 3)
        return i;
  }
}

int Jogador::getValorQuadra(){
  int i = 0;
  for (i = 1; i < 15; i--){      
      if(numCartas(i) == 4)
        return i;
  }
}

void Jogador::aumentaCartaAs(){
  int i = 0;
  for(i = 0; i < NUM_CARTAS; i++){
    if (mao[i].getValor() == 1){
      mao[i].setValor(14);
    }
  }
}

void Jogador::diminuirCartaAs(){
  int i = 0;
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
	naipesIguais = (mao[0].getNaipe() == mao[1].getNaipe()) &&
	 							 (mao[2].getNaipe() == mao[3].getNaipe()) && 
								 (mao[0].getNaipe() == mao[4].getNaipe()) && 
								 (mao[2].getNaipe() == mao[1].getNaipe());
	for (int i = 0; i < 14; i++){
    if(!sequencia){
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
		if(this->contemCarta(10) && this->contemCarta(11) && this->contemCarta(12) && this->contemCarta(13) && 
       this->contemCarta(1)){ // Royal Straight Flush [RSF]
			return Royal_Straight_Flush;
		}else if(sequencia){return Straight_Flush;}// Straight Flush [SF]
     else {return Flush;} // Flush [F]
	}else { if(sequencia){return Straight;} } // Straight [S]
  
  if(quatroCartas){return Four_of_a_kind;} // Four of a kind [FK]
  if(tresCartas && duasCartas){return Full_House;} // Full House [FH]
  if(tresCartas && !duasCartas){return Three_of_a_kind;} // Three of a kind [TK]
  if(equalTwo(numParesCartas)){return Two_Pairs;} // Two Pairs [TP]
  if(equalOne(numParesCartas)){return One_Pair;} // One Pair [OP]
  return Invalid;
}

void Poker::getInfoJogadores(){
  for(int i = 0; i < numPlayers ; i++){
    jogadores[i].getValores();
  }
}

void Poker::setPingo(int valorPingoMin){
  if (valorPingoMin % MIN_PINGO == 0){
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

void Poker::novaRodada(std::string nome, std::string carta[],int aposta){
  for (int i = 0; i < numPlayers; i++){
    if (jogadores[i].getName() == nome){
      jogadores[i].setMao(carta);
      jogadores[i].ordenarCartas();
      jogadores[i].debitaDinheiro(aposta);
      return;
    }
  }
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
  int i = 0, j = 0, k = 0, numVencedores = 0;
  for (i = 0; i < numPlayers; i++){
    jogadores[i].aumentaCartaAs();
    numVencedores = posJogador[i] != -1 ? numVencedores + 1: numVencedores;
  }
  switch(rank){
    case High_Card:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1)
          continue;
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            continue;
          for (i = 0; i < NUM_CARTAS; i++){
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
    case One_Pair:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1)
          continue;
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            continue;
          if(jogadores[posJogador[j]].getValorPar() > jogadores[posJogador[k]].getValorPar()){
            posJogador[k] = -1;
            continue;
          }else if(jogadores[posJogador[j]].getValorPar() < jogadores[posJogador[k]].getValorPar()){
            posJogador[j] = -1;
            continue;
          }
          for (i = 0; i < NUM_CARTAS; i++){
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
    case Two_Pairs:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1)
          continue;
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            continue;
          if(jogadores[posJogador[j]].getValorPar() > jogadores[posJogador[k]].getValorPar()){
            posJogador[k] = -1;
            continue;
          }else if(jogadores[posJogador[j]].getValorPar() < jogadores[posJogador[k]].getValorPar()){
            posJogador[j] = -1;
            continue;
          }
          if(jogadores[posJogador[j]].getValorPar(2) > jogadores[posJogador[k]].getValorPar(2)){
            posJogador[k] = -1;
            continue;
          }else if(jogadores[posJogador[j]].getValorPar(2) < jogadores[posJogador[k]].getValorPar(2)){
            posJogador[j] = -1;
            continue;
          }
          for (i = 0; i < NUM_CARTAS; i++){
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
    case Three_of_a_kind:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1)
          continue;
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            continue;
          if(jogadores[posJogador[j]].getValorTripla() > jogadores[posJogador[k]].getValorTripla()){
            posJogador[k] = -1;
            continue;
          }else if(jogadores[posJogador[j]].getValorTripla() < jogadores[posJogador[k]].getValorTripla()){
            posJogador[j] = -1;
            continue;
          }
          for (i = 0; i < NUM_CARTAS; i++){
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
    case Straight:
      break;
    case Flush:
      break;
    case Full_House:
      break;
    case Four_of_a_kind:
      while (j < numPlayers - 1){
        if(posJogador[j] == -1)
          continue;
        for (k = j+1; k < numPlayers; k++){
          if(posJogador[k] == -1)
            continue;
          if(jogadores[posJogador[j]].getValorQuadra() > jogadores[posJogador[k]].getValorQuadra()){
            posJogador[k] = -1;
            continue;
          }else if(jogadores[posJogador[j]].getValorQuadra() < jogadores[posJogador[k]].getValorQuadra()){
            posJogador[j] = -1;
            continue;
          }
          for (i = 0; i < NUM_CARTAS; i++){
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
    default:
      break;
  }
  for (i = 0; i < numPlayers; i++){
    jogadores[i].diminuirCartaAs();
  }
}

void Poker::getVencedor(std::ofstream &arqSaida){
  clasificacao ranking[numPlayers];
  int i = 0, numVencedores = 1;
  int posJogadorMaior[] = {-1,-1,-1,-1,-1};
  for (i = 0; i < numPlayers; i++){
    if (jogadores[i].mao[0].isEmpty()){
      ranking[i] = Invalid;
      continue;
    }
    ranking[i] = jogadores[i].getClassificacao();
  }
  for (i = 0; i < numPlayers; i++){
    posJogadorMaior[0] = ranking[i] > posJogadorMaior[0] ? i : posJogadorMaior[0];
  }
  for (i = 0; i < numPlayers; i++){
    if(posJogadorMaior[0] == i){continue;}
    if(ranking[i] == ranking[posJogadorMaior[0]]){
      posJogadorMaior[numVencedores] = i;
      numVencedores++;
    }
  }
  arqSaida << numVencedores << " " << getPote()/numVencedores << " ";
  arqSaida << converterClassificao(ranking[posJogadorMaior[0]]) << "\n";
  if(numVencedores > 1){
    desempate(ranking[posJogadorMaior[0]], posJogadorMaior);
  }
  for (i = 0; i < numVencedores; i++){
    arqSaida << jogadores[posJogadorMaior[i]].getName() << "\n";
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

void Poker::iniciaJogo(){
  int dinInicial = 0, rodadas = 0, i = 0;
  int numJogadores = 0, pingo = 0, aposta = 0,  j = 0;  
  int apost[MAX_JOGADOR];
  std::ifstream file ("entrada.txt");
  std::ofstream arqSaida("saida.txt");
  std::string nome = "";
  std::string line = "";
  std::string carta[NUM_CARTAS];
  file >> rodadas >> dinInicial;
  for (i = 0; i < rodadas; i++){
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
        jogadores[j].ordenarCartas();
        jogadores[j].debitaDinheiro(aposta);
        somaPote(aposta);
      }
    }else{
      for (j = 0; j < numJogadores; j++){
        getline(file, line);
        if(line=="") getline(file, line);
        leCartas(line, carta);
        leAposta(line, aposta);
        nome = line;
        novaRodada(nome,carta,aposta);
        somaPote(aposta);
      }  
    }
    somaPote(getPingo());
    getVencedor(arqSaida);
    limparCartas();
    zerarPote();
  }
  arqSaida << "####\n";
  ordenarJogadores();
  for (j = 0; j < numPlayers; j++){
    arqSaida << jogadores[j].getName() << " " << jogadores[j].getAmount() << "\n";
  }
  file.close();
  arqSaida.close();
  getInfoJogadores();
}