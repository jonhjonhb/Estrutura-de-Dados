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
FER = -pg -O3
OBJS = $(OBJ)/poker.o $(OBJ)/jogo.o $(OBJ)/memlog.o
HDRS = $(INC)/poker.hpp $(INC)/memlog.hpp $(INC)/msgassert.h
OBJSM = $(OBJ)/pilhaindexada.o $(OBJ)/analisamem.o
HDRSM = $(INC)/pilhaindexada.h $(INC)/msgassert.h
CFLAGS = $(FER) -Wall -c -I$(INC)
ANALISAMEM = ../../aulapratica2/analisamem/bin/analisamem

EXE = $(BIN)/jogo

all: jogo bin

clean:
	rm -f $(OBJ)/* $(BIN)/* *.out ../temp/*

jogar: $(EXE)
	$(EXE)

gdb: $(EXE) 
	gdb $(EXE)

gerador: $(EXE) 
	gcc src/geracarga.c -I$(INC) -o bin/gerador -lm
	bin/gerador -o "entrada.txt" -r 3 -j 8 -v 1

jogo: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(FER) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/jogo.o: $(HDRS) $(SRC)/jogo.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/jogo.o $(SRC)/jogo.cpp 

$(OBJ)/poker.o: $(HDRS) $(SRC)/poker.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/poker.o $(SRC)/poker.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp 

gprof:
	gprof $(EXE) gmon.out > ../temp/gprof.txt

perf:
	$(ANALISAMEM) -i ../temp/partidagprof.out -p ../temp/perf
	gnuplot ../temp/*.gp