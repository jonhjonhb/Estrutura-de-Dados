#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Johnatan Augusto (johnatanaugusto@ufmg.br)
# Histórico	: 2022-05-21 - arquivo criado
#		: 2022-05-21 - estrutura de diretórios
#               : 2022-05-21 - Versao 1.1 memlog
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
FER = -g
OBJS = $(OBJ)/poker.o $(OBJ)/jogo.o 
HDRS = $(INC)/poker.hpp
CFLAGS = $(FER) -Wall -c -I$(INC) # -O3

EXE = $(BIN)/jogo

# all: bin
$(BIN)/jogo: $(OBJS)
	$(CC) $(FER) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/jogo.o: $(HDRS) $(SRC)/jogo.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/jogo.o $(SRC)/jogo.cpp 

$(OBJ)/poker.o: $(HDRS) $(SRC)/poker.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/poker.o $(SRC)/poker.cpp 
	
clean:
	rm -f $(EXE) $(OBJS) *.out

jogar: $(EXE) 
	$(EXE)