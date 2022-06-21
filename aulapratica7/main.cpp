#include <iostream>

void buscaPalavras();

int main() {
    
  return 0;
}

void buscaPalavras(std::string &texto, std::string palavra){
  int j = 1;
  if (texto.substr(texto.size() - j, 1) == " "){
    texto = texto.substr(0, texto.size() - j);
  } 
  for (int i = 0; i < 100; i++){
    palavra = "";
    for (j = 1; texto.substr(texto.size() - j, 1) != " " ; j++){}
    palavra = texto.substr(texto.size() - j + 1);
    texto = texto.substr(0, texto.size() - j);
  }
}