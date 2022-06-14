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
OBJSM = $(OBJ)/analisamem.o
HDRSM = $(INC)/msgassert.h
CFLAGS = $(FER) -Wall -c -I$(INC)

EXE = $(BIN)/jogo

all: bin
$(BIN)/jogo: $(OBJS)
	$(CC) $(FER) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/jogo.o: $(HDRS) $(SRC)/jogo.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/jogo.o $(SRC)/jogo.cpp 

$(OBJ)/poker.o: $(HDRS) $(SRC)/poker.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/poker.o $(SRC)/poker.cpp 
	
clean:
	rm -f $(EXE) $(BIN)/gerador $(OBJS) $(OBJSM) *.out

jogar: $(EXE) 
	$(EXE)

gdb: $(EXE) 
	gdb $(EXE)

gerador: $(EXE) 
	gcc src/geracarga.c -I$(INC) -o bin/gerador -lm
	bin/gerador -o "entrada.txt" -r 50000 -j 8 -v 1

bin: $(BIN)/analisamem

$(BIN)/analisamem: $(OBJSM)
	$(CC) -pg -o $(BIN)/analisamem $(OBJSM) $(LIBS)

$(OBJ)/analisamem.o: $(HDRSM) $(SRC)/analisamem.c
	$(CC) $(CFLAGS) -o $(OBJ)/analisamem.o $(SRC)/analisamem.c 