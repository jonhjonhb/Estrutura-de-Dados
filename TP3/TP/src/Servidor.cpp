#include <getopt.h>
#include "Hash.hpp"
#include <cstring>
#include <fstream>
#include "msgassert.h"

// variaveis globais para opcoes
char logName[100];
std::string fileNameInput;
std::string fileNameOutput;
int regmem;
bool regOpt;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
	fprintf(stderr,"TP3\n");
	fprintf(stderr,"\t-i <arq>\t(endereço do arquivo de entrada)\n");
	fprintf(stderr,"\t-o <arq>\t(endereço do arquivo de saida)\n");
	fprintf(stderr,"\t-p <arq>\t(arquivo de registro de acesso/desempenho)\n");
	fprintf(stderr,"\t-l \t\t(registrar acessos a memoria)\n");
	// fprintf(stderr,"\t-x <int>\t(primeira dimensao)\n");
	// fprintf(stderr,"\t-y <int>\t(segunda dimensao)\n");
	// fprintf(stderr,"\t-s \t(somar matrizes) \n");
	// fprintf(stderr,"\t-m \t(multiplicar matrizes) \n");
	// fprintf(stderr,"\t-t \t(transpor matriz)\n");
}

void parse_args(int argc,char ** argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida: optescolhida, optx, opty, regmem, logName
{
		 // variaveis externas do getopt
		 extern char * optarg;

		 // variavel auxiliar
		 int c;

		 // inicializacao variaveis globais para opcoes
		 regmem = 0;
		 logName[0] = 0;
		 fileNameInput = "";
		 fileNameOutput = "";

		 // getopt - letra indica a opcao, : junto a letra indica parametro
		 // no caso de escolher mais de uma operacao, vale a ultima
		 while ((c = getopt(argc, argv, "o:p:i:l")) != EOF)
			 switch(c) {
				 case 'p':
            strcpy(logName,optarg);
						erroAssert(strlen(logName)>0,
						 "analisador - nome de arquivo de registro de acesso tem que ser definido");
	            regOpt = true;
						break;
				 case 'i':
            fileNameInput = optarg;
            break;
				 case 'o':
            fileNameOutput = optarg;
            break;
				 case 'l': 
						regmem = 1;
            break;
				 default:
            uso();
            exit(1);
            break;
			 }
			 if(regmem)
				regmem = regOpt;
			 // verificacao da consistencia das opcoes
			 erroAssert(fileNameInput != "",
				 "analisador - nome do arquivo de entrada tem que ser definido");
			 erroAssert(fileNameOutput != "",
				 "analisador - nome do arquivo de saida tem que ser definido");
}

int main(int argc, char ** argv)
// Descricao: programa principal para execucao 
// Entrada: argc e argv
// Saida: escrita no arquivo escolhido
{
	regOpt = false;
	// avaliar linha de comando
	parse_args(argc,argv);
	// iniciar registro de acesso
	if(regOpt)
		iniciaMemLog(logName);
	// ativar ou nao o registro de acesso
	if (regmem){ 
		ativaMemLog();
	} else{
		desativaMemLog();
	}
  int tamanho = 0;
  std::string aux = "", metod = "", msg = "";
  int U = 0, E = 0;
  int nPalavras = 0;

  std::ifstream fileInput(fileNameInput);
	std::ofstream output(fileNameOutput);
	erroAssert(!output.fail(), "Arquivo de saida - Nao foi possivel abrir o arquivo");

  fileInput >> tamanho;
  HashLista Servidor(tamanho);

  while (fileInput >> metod){
    msg = "";
    fileInput >> U;
    fileInput >> E;
    if (metod == "ENTREGA") {
      fileInput >> nPalavras;
      for (int i = 0; i < nPalavras; i++) {
        fileInput >> aux;
        msg += aux + " ";
      }
      msg = msg.substr(0,msg.size()-1);
    }
    output << Servidor.request(metod, U, E, msg);
  }
	
  fileInput.close();
	output.close();
	// conclui registro de acesso
	return (regOpt) ? finalizaMemLog() : 0;
}