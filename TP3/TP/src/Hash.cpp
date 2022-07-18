#include "Hash.hpp"

HashLista::HashLista(int n) {
  avl = new ArvoreBinaria[n];
  ocupado = new bool[n];
  tam_max = n;
  for(int i=0; i<n; i++)
    ocupado[i] = false;
}

int HashLista::funcaohash(int chave) {
  return ( chave % tam_max );
}

int HashLista::insere(int chave, Email v) {
  int pos = funcaohash(chave);
  avl[pos].inserir(v); // insere item na lista
  if ( !ocupado[pos] ) ocupado[pos] = true;
  return pos;
}
  
bool HashLista::apaga(int chave, Email v) {
  int pos = busca(chave, v);
  if (pos == -1){
    return false;
  } else {
    avl[pos].remover(v);
    return true;
  }
}

int HashLista::busca(int chave, Email v) {
  int pos = funcaohash(chave);
  if ( avl[pos].buscar(v) ) 
    return pos;
  return -1;
}

std::string HashLista::request(std::string metod, int U, int E, std::string msg = ""){
  Email novo(U,E,msg);
  int pos;
  std::string resposta = "";
  if (metod == "ENTREGA") {
    pos = insere(U, novo);
    resposta = "OK: MENSAGEM " + to_string(E) + " PARA ";
    resposta += to_string(U) + " ARMAZENADA EM " + to_string(pos);
  } else if (metod == "CONSULTA") {
    pos = funcaohash(U);
    resposta = "CONSULTA " + to_string(U) + " " + to_string(E) + ": ";
    resposta += avl[pos].consulta(novo);
  } else if (metod == "APAGA") {
    if (apaga(U, novo)) resposta = "OK: MENSAGEM APAGADA";
    else resposta = "ERRO: MENSAGEM INEXISTENTE";      
  }
  return resposta + "\n";
}