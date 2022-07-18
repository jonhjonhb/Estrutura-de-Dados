#include "ArvoreB.hpp"

void ArvoreBinaria::inserir(Email v) {
  NO *novo = new NO();
  novo->item = v;
  novo->dir = NULL;
  novo->esq = NULL;
  if (raiz == NULL) raiz = novo;
  else  {
    NO *atual = raiz;
    NO *anterior;
    while(1) {
      anterior = atual;
      if (v <= atual->item) { // navegar para a esquerda
        atual = atual->esq;
        if (atual == NULL) {
          anterior->esq = novo;
          return;
        } 
      }
      else { // navegar para a direita
        atual = atual->dir;
        if (atual == NULL) {
          anterior->dir = novo;
          return;
        }
      }
    }
  }
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

bool ArvoreBinaria::remover(Email v) {
  if (raiz == NULL) return false;
  NO *atual = raiz;
  NO *pai = raiz;
  bool filho_esq = true;
  while (atual->item != v) { // enquanto diferente
    pai = atual;
    if(v < atual->item ) { // caminha para a aesquerda
      atual = atual->esq;
      filho_esq = true;
    }
    else { // caminha para a direita
      atual = atual->dir; 
      filho_esq = false;
    }
    if (atual == NULL) return false;
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

NO * ArvoreBinaria::no_sucessor(NO *apaga) {
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

NO * ArvoreBinaria::rotacaoDireita(NO * head){
  NO * novoHead = head->esq;
  head->esq = novoHead->dir;
  novoHead->dir = head;
  head->altura = altura(head);
  novoHead->altura = altura(novoHead);
  return novoHead;
}

NO * ArvoreBinaria::rotacaoEsquerda(NO * head){
  NO * novoHead = head->dir;
  head->dir = novoHead->esq;
  novoHead->esq = head;
  head->altura = altura(head);
  novoHead->altura = altura(novoHead);
  return novoHead;
}

NO * ArvoreBinaria::insertUtil(NO * head, Email x){
  if(head==NULL){
      NO * temp = new NO();
      temp->item = x;
      return temp;
  }
  if(x < head->item) head->esq = insertUtil(head->esq, x);
  else if(x > head->item) head->dir = insertUtil(head->dir, x);
  head->altura = altura(head);
  int fb = altura(head->esq) - altura(head->dir);
  if(fb > 1){
    if(x < head->esq->item){
        return rotacaoDireita(head);
    }else{
        head->esq = rotacaoEsquerda(head->esq);
        return rotacaoDireita(head);
    }
  }else if(fb < -1){
    if(x > head->dir->item){
        return rotacaoEsquerda(head);
    }else{
        head->dir = rotacaoDireita(head->dir);
        return rotacaoEsquerda(head);
    }
  }
  return head;
}

NO * ArvoreBinaria::removeUtil(NO * head, Email x){
  if(head==NULL) return NULL;
  if(x < head->item){
      head->esq = removeUtil(head->esq, x);
  }else if(x > head->item){
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
          head->item = r->item;
          head->dir = removeUtil(head->dir, r->item);
      }
  }
  if(head==NULL) return head;
  head->altura = altura(head);
  int fb = altura(head->esq) - altura(head->dir);
  if(fb > 1){
      if(altura(head->esq) >= altura(head->dir)){
          return rotacaoDireita(head);
      }else{
          head->esq = rotacaoEsquerda(head->esq);
          return rotacaoDireita(head);
      }
  }else if(fb < -1){
      if(altura(head->dir) >= altura(head->esq)){
          return rotacaoEsquerda(head);
      }else{
          head->dir = rotacaoDireita(head->dir);
          return rotacaoEsquerda(head);
      }
  }
  return head;
}