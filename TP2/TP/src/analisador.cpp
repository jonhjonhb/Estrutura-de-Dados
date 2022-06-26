#include <getopt.h>
#include <string>
#include <cstring>
#include "memlog.hpp"
#include "msgassert.h"

// variaveis globais para opcoes
char logName[100];
std::string fileInput;
std::string fileOutput;
int regmem;

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
	fprintf(stderr,"analisador\n");
	fprintf(stderr,"\t-i <arq>\t(arquivo de entrada com o texto e a nova ordem lexicografica)\n");
	fprintf(stderr,"\t-o <arq>\t(endereço do arquivo de saida)\n");
	fprintf(stderr,"\t-p <arq>\t(arquivo de registro de acesso/desempenho)\n");
	fprintf(stderr,"\t-l \t(registrar acessos a memoria)\n");
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
		 fileInput = "";
		 fileOutput = "";

		 // getopt - letra indica a opcao, : junto a letra indica parametro
		 // no caso de escolher mais de uma operacao, vale a ultima
		 while ((c = getopt(argc, argv, "smtp:o:i:l")) != EOF)
			 switch(c) {
				 case 'p':
            strcpy(logName,optarg);
            break;
				 case 'o':
            fileOutput = optarg;
            break;
				 case 'i': 
            fileInput = optarg;
            break;
				 case 'l': 
						regmem = 1;
            break;
				 default:
            uso();
            exit(1);
            break;
			 }
			 // verificacao da consistencia das opcoes
			 erroAssert(strlen(logName)>0,
				 "analisador - nome de arquivo de registro de acesso tem que ser definido");
			 erroAssert(fileInput != "",
				 "analisador - nome do arquivo de entrada tem que ser definido");
			 erroAssert(fileOutput != "",
				 "analisador - nome do arquivo de saida tem que ser definido");
}

int main(int argc, char ** argv)
// Descricao: programa principal para execucao 
// Entrada: argc e argv
// Saida: escrita no arquivo escolhido
{
	// ate 3 matrizes sao utilizadas, dependendo da operacao
	// mat_tipo a, b, c;

	// avaliar linha de comando
	parse_args(argc,argv);

	// iniciar registro de acesso
	iniciaMemLog(logName);

	// ativar ou nao o registro de acesso
	if (regmem){ 
		ativaMemLog();
	}
	else{
		desativaMemLog();
	}



	// conclui registro de acesso
	return finalizaMemLog();
}
