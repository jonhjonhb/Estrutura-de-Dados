#include <iostream>
#include "poker.hpp"
#include <ctime>

int main(){
  Poker mesa;
  mesa.iniciaJogo();
  return 0;
}

/*
void criaMatrizArquivo(mat_tipo * mat, char * nomeFile, int id){
  int i, j;
  FILE *partidaFile;
  partidaFile = fopen("entrada.txt","r");
  erroAssert(partidaFile != NULL,"Não foi possivel abrir o arquivo!");
  
  fscanf(matrizFile, "%d %d", &tx, &ty); // erro do double como dimensão
  criaMatriz(mat,tx,ty,id);
  inicializaMatrizNula(mat);
  for (i=0; i<mat->tamx; i++){
    for(j=0; j<mat->tamy; j++){
      fscanf(matrizFile, "%le", &mat->m[i][j]);
      ESCREVEMEMLOG((long int)(&(mat->m[i][j])),sizeof(double),mat->id);
    }
  }
  fclose(matrizFile);
}*/