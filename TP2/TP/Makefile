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
FER = -g -O3
OBJS = $(OBJ)/analisador.o $(OBJ)/memlog.o #$(OBJ)/poker.o
HDRS = $(INC)/memlog.hpp $(INC)/msgassert.h $(INC)/Word.hpp $(INC)/Text.hpp $(INC)/listaEncadeada.hpp 
OBJSM = $(OBJ)/analisamem.o
HDRSM = $(INC)/msgassert.h
CFLAGS = $(FER) -Wall -c -I$(INC)
ANALISAMEM = ../../aulapratica2/analisamem/bin/analisamem

EXE = $(BIN)/analisador

all: analisador bin

clean:
	rm -f $(OBJ)/* $(BIN)/* *.out ../temp/*

jogar: $(EXE)
	$(EXE) -p ../temp/gprofTeste.out -i entrada.txt -o saida.txt -l

gdb: $(EXE) 
	gdb $(EXE)

analisador: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(FER) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/analisador.o: $(HDRS) $(SRC)/analisador.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/analisador.o $(SRC)/analisador.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.cpp 

performance: gerador
	bin/gerador -o "entrada.txt" -r 1000 -j 9
	$(EXE)
	gprof $(EXE) gmon.out > ../temp/gprof-1000x10.txt
	bin/gerador -o "entrada.txt" -r 2000 -j 9
	$(EXE)
	gprof $(EXE) gmon.out > ../temp/gprof-2000x10.txt
	bin/gerador -o "entrada.txt" -r 3000 -j 9
	$(EXE)
	gprof $(EXE) gmon.out > ../temp/gprof-3000x10.txt
	
gprof:
	gprof $(EXE) gmon.out > ../temp/gprof.txt

perf:
	$(ANALISAMEM) -i ../temp/partidagprof.out -p ../temp/perf
	gnuplot ../temp/*.gp

teste: clean jogar gprof perf