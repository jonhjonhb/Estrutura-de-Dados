#include <iostream>
#include <string>

using namespace std;

void buscaPalavras(std::string &texto, std::string palavra){
  int i = 0, pos = 0; 
  bool sim = false;
  while (texto.substr(i, 1) == " ") i++;
  for (i = 0; i <= texto.size(); i++){
    if (texto.substr(i, 1) == " " || texto.size() == i) {
      if (texto.substr(0, i) == palavra) {
        if(sim) cout << " ";
        cout << pos;
        sim = true;
      }
      pos += (i + 1);
      if (i == texto.size()) texto = texto.substr(i);
      else texto = texto.substr(i+1);
      i = 0;
    } 
  }
  if (sim){
    cout << endl;
  } else{
    cout << -1 << endl;
  }
}

int main() {
  int qtdTextos = 0;
  string texto, palavra;

  cin >> qtdTextos;

  for (int i = 0; i < qtdTextos; i++) {
    std::getline(cin, texto);
    if(texto == "") std::getline(cin, texto);
    cin >> palavra;
    buscaPalavras(texto, palavra);
  }
  return 0;
}