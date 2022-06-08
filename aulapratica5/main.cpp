#include <iostream>
#include <cstring>
#include <sstream>

#define Troca(A, B) {std::string c = A; A = B; B = c; }

class Item {
  public:
    std::string vetor[50];
};

int main() {
	int N = 0, i = 0, j = 0, k = 0;
  std::string linha;
  std::string aux;
  std::cin >> N;
  Item casos[N];

  for(k = 0; k < N+1; k++){
	  getline(std::cin, aux);
    for (i = 0; i < 50; i++){
      if(aux.size()==0)
        break;
      for (j = 0; aux[j] != ' '; j++){ 
        if (aux[j] == '\0'){
          casos[k-1].vetor[i] = aux;
          break;
        }
      }
      if(aux[j] == '\0')
        break;
      casos[k-1].vetor[i] = aux.substr(0, j);
      aux = aux.substr(j + 1);
    }

  }
  for (k = 0; k < N; k++){
    for(i = 0; i < 50-1; i++)
      for(j = 1; j < 50-i; j++)
        if (casos[k].vetor[j].size() > casos[k].vetor[j-1].size() && casos[k].vetor[j-1] != "" && casos[k].vetor[j] != "") 
          Troca(casos[k].vetor[j-1], casos[k].vetor[j]);
  }
  
  for (k = 0; k < N; k++){
    for (i = 0; i < 50; i++){
      std::cout << casos[k].vetor[i];
      if(casos[k].vetor[i+1].size() != 0){
        std::cout << " ";
      } else {
        std::cout << std::endl;
        break;
      }
    }

  }
  return 0;
}