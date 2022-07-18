#include "ArvoreB.hpp"

void ArvoreBinaria::inserir(int chave, Email v) {
  NO *novo = new NO();
  novo->item = v; // atribui o valor recebido ao item de dados do Nó
  novo->dir = NULL;
  novo->esq = NULL;
  if (raiz == NULL) raiz = novo;
  else  { // se nao for a raiz
    NO *atual = raiz;
    NO *anterior;
    while(true) {
      anterior = atual;
      if (v <= atual->item) { // ir para esquerda
        atual = atual->esq;
        if (atual == NULL) {
          anterior->esq = novo;
          return;
        } 
      }  // fim da condição ir a esquerda
      else { // ir para direita
          atual = atual->dir;
          if (atual == NULL) {
            anterior->dir = novo;
            return;
          }
      } // fim da condição ir a direita
    } // fim do laço while
  } // fim do else não raiz
}

NO * ArvoreBinaria::buscar(Email chave) {  
  if (raiz == NULL) return NULL;
  NO *atual = raiz;
  while (atual->item != chave) {
    if(chave < atual->item ) atual = atual->esq;
    else atual = atual->dir;
    if (atual == NULL) return NULL;
  }
  return atual;
}

std::string ArvoreBinaria::consulta(Email chave) {
  NO *atual = buscar(chave);
  if(atual == NULL) return "MENSAGEM INEXISTENTE";
  else return atual->item.getMensagem();
}

bool ArvoreBinaria::remover(int chave, Email v) {
  if (raiz == NULL) return false;
  NO *atual = raiz;
  NO *pai = raiz;
  bool filho_esq = true;
  while (atual->item != v) { // enquanto nao encontrou
    pai = atual;
    if(v < atual->item ) { // caminha para esquerda
      atual = atual->esq;
      filho_esq = true;
    }
    else { // caminha para direita
      atual = atual->dir; 
      filho_esq = false;
    }
    if (atual == NULL) return false; // encontrou uma folha -> sai
  }

  // se chegou aqui encontrou o valor (v)
  // atual: referencia ao No a ser eliminado
  // pai: referencia para o pai do No a ser eliminado
  // filho_esq: é verdadeiro se atual é filho a esquerda do pai

  // Se nao possui nenhum filho (é uma folha), elimine-o
  if (atual->esq == NULL && atual->dir == NULL) {
    if (atual == raiz ) raiz = NULL; // se raiz
    else if (filho_esq) pai->esq = NULL; // se filho a esquerda do pai
          else pai->dir = NULL; // se filho a direita do pai
  }

  // Se é pai e nao possui um filho a direita, substitui pela subarvore a direita
  else if (atual->dir == NULL) {
      if (atual == raiz) raiz = atual->esq; // se raiz
      else if (filho_esq) pai->esq = atual->esq; // se for filho a esquerda do pai
          else pai->dir = atual->esq; // se for filho a direita do pai
  }
  
  // Se é pai e nao possui um filho a esquerda, substitui pela subarvore a esquerda
  else if (atual->esq == NULL) {
      if (atual == raiz) raiz = atual->dir; // se raiz
      else if (filho_esq) pai->esq = atual->dir; // se for filho a esquerda do pai
          else pai->dir = atual->dir; // se for  filho a direita do pai
  }

  // Se possui mais de um filho, se for um avô ou outro grau maior de parentesco
  else {
    NO *sucessor = no_sucessor(atual);
    // Usando sucessor que seria o Nó mais a esquerda da subarvore a direita do No que deseja-se remover
    if (atual == raiz) raiz = sucessor; // se raiz
    else if(filho_esq) pai->esq = sucessor; // se for filho a esquerda do pai
          else pai->dir = sucessor; // se for filho a direita do pai
    sucessor->esq = atual->esq; // acertando o ponteiro a esquerda do sucessor agora que ele assumiu 
                              // a posição correta na arvore   
  }

  return true;
}

NO * ArvoreBinaria::no_sucessor(NO *apaga) { // O parametro é a referencia para o No que deseja-se apagar
// O sucessor é o Nó mais a esquerda da subarvore a direita do No que foi passado como parametro do metodo
    NO *paidosucessor = apaga;
    NO *sucessor = apaga;
    NO *atual = apaga->dir; // vai para a subarvore a direita

    while (atual != NULL) { // enquanto nao chegar no Nó mais a esquerda
      paidosucessor = sucessor;
      sucessor = atual;
      atual = atual->esq; // caminha para a esquerda
    } 
    // *********************************************************************************
    // quando sair do while "sucessor" será o Nó mais a esquerda da subarvore a direita
    // "paidosucessor" será o o pai de sucessor e "apaga" o Nó que deverá ser eliminado
    // *********************************************************************************
    if (sucessor != apaga->dir) { // se sucessor nao é o filho a direita do Nó que deverá ser eliminado
      paidosucessor->esq = sucessor->dir; // pai herda os filhos do sucessor que sempre serão a direita
      // lembrando que o sucessor nunca poderá ter filhos a esquerda, pois, ele sempre será o
      // Nó mais a esquerda da subarvore a direita do Nó apaga.
      // lembrando também que sucessor sempre será o filho a esquerda do pai

      sucessor->dir = apaga->dir; // guardando a referencia a direita do sucessor para 
                                // quando ele assumir a posição correta na arvore
    }
    return sucessor;
}

int ArvoreBinaria::altura(NO *atual) {
    if(atual == NULL || (atual->esq == NULL && atual->dir == NULL))
      return 0;
    else {
  if (altura(atual->esq) > altura(atual->dir))
      return ( 1 + altura(atual->esq) );
  else
    return ( 1 + altura(atual->dir) );
    }
}

int ArvoreBinaria::folhas(NO *atual) {
  if(atual == NULL) return 0;
  if(atual->esq == NULL && atual->dir == NULL) return 1;
  return folhas(atual->esq) + folhas(atual->dir);
}

int ArvoreBinaria::contarNos(NO *atual) {
  if(atual == NULL)  return 0;
  else return ( 1 + contarNos(atual->esq) + contarNos(atual->dir));
}

Email ArvoreBinaria::min() {
  NO *atual = raiz;
  NO *anterior = NULL;
  while (atual != NULL) {
    anterior = atual;
    atual = atual->esq;
  }
  return anterior->item;
}

Email ArvoreBinaria::max() {
  NO *atual = raiz;
  NO *anterior = NULL;
  while (atual != NULL) {
    anterior = atual;
    atual = atual->dir;
  }
  return anterior->item;
}
/*
NO * ArvoreBinaria::rightRotation(NO * head){
  NO * newhead = head->esq;
  head->esq = newhead->dir;
  newhead->dir = head;
  head->altura = 1+max(getAltura(head->esq), getAltura(head->dir));
  newhead->altura = 1+max(getAltura(newhead->esq), getAltura(newhead->dir));
  return newhead;
}

NO * leftRotation(NO * head){
  NO * newhead = head->dir;
  head->dir = newhead->esq;
  newhead->esq = head;
  head->altura = 1+max(getAltura(head->esq), getAltura(head->dir));
  newhead->altura = 1+max(getAltura(newhead->esq), getAltura(newhead->dir));
  return newhead;
}

NO * insertUtil(NO * head, T x){
  if(head==NULL){
      n+=1;
      NO * temp = new NO(x);
      return temp;
  }
  if(x < head->key) head->esq = insertUtil(head->esq, x);
  else if(x > head->key) head->dir = insertUtil(head->dir, x);
  head->altura = 1 + max(getAltura(head->esq), getAltura(head->dir));
  int bal = getAltura(head->esq) - getAltura(head->dir);
  if(bal>1){
      if(x < head->esq->key){
          return rightRotation(head);
      }else{
          head->esq = leftRotation(head->esq);
          return rightRotation(head);
      }
  }else if(bal<-1){
      if(x > head->dir->key){
          return leftRotation(head);
      }else{
          head->dir = rightRotation(head->dir);
          return leftRotation(head);
      }
  }
  return head;
}

NO * removeUtil(NO * head, T x){
  if(head==NULL) return NULL;
  if(x < head->key){
      head->esq = removeUtil(head->esq, x);
  }else if(x > head->key){
      head->dir = removeUtil(head->dir, x);
  }else{
      NO * r = head->dir;
      if(head->dir==NULL){
          NO * l = head->esq;
          delete(head);
          head = l;
      }else if(head->esq==NULL){
          delete(head);
          head = r;
      }else{
          while(r->esq!=NULL) r = r->esq;
          head->key = r->key;
          head->dir = removeUtil(head->dir, r->key);
      }
  }
  if(head==NULL) return head;
  head->altura = 1 + max(getAltura(head->esq), getAltura(head->dir));
  int bal = getAltura(head->esq) - getAltura(head->dir);
  if(bal>1){
      if(getAltura(head->esq) >= getAltura(head->dir)){
          return rightRotation(head);
      }else{
          head->esq = leftRotation(head->esq);
          return rightRotation(head);
      }
  }else if(bal < -1){
      if(getAltura(head->dir) >= getAltura(head->esq)){
          return leftRotation(head);
      }else{
          head->dir = rightRotation(head->dir);
          return leftRotation(head);
      }
  }
  return head;
}*/