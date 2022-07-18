#include "ArvoreB.hpp"

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

NO * ArvoreBinaria::insereRecursivo(NO * head, Email x){
  if(head==NULL){
      NO * temp = new NO();
      temp->item = x;
      return temp;
  }
  if(x < head->item) head->esq = insereRecursivo(head->esq, x);
  else if(x > head->item) head->dir = insereRecursivo(head->dir, x);
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

NO * ArvoreBinaria::removeRecursivo(NO * head, Email x){
  if(head==NULL) return NULL;
  if(x < head->item){
      head->esq = removeRecursivo(head->esq, x);
  }else if(x > head->item){
      head->dir = removeRecursivo(head->dir, x);
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
          head->dir = removeRecursivo(head->dir, r->item);
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