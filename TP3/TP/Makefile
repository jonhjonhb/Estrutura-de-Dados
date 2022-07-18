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
OBJS = $(OBJ)/Servidor.o $(OBJ)/memlog.o $(OBJ)/Hash.o $(OBJ)/ArvoreB.o
HDRS = $(INC)/memlog.hpp $(INC)/msgassert.h $(INC)/Hash.hpp $(INC)/ArvoreB.hpp $(INC)/Email.hpp
OBJSM = $(OBJ)/analisamem.o
HDRSM = $(INC)/msgassert.h
CFLAGS = $(FER) -Wall -c -I$(INC)
ANALISAMEM = ../../aulapratica2/analisamem/bin/analisamem

EXE = $(BIN)/tp3
AUTOTESTE = ../testes/comparator

all: tp3 bin

comp: tp3
	$(EXE) -i ../testes/input/entrada_1.txt -o ../testes/outputs/teste_1.txt -p ../temp/test.txt
	$(AUTOTESTE) -1 ../testes/outputs/teste_1.txt -2 ../testes/resposta/saida_1.txt
	$(EXE) -i ../testes/input/entrada_2.txt -o ../testes/outputs/teste_2.txt -p ../temp/test.txt
	$(AUTOTESTE) -1 ../testes/outputs/teste_2.txt -2 ../testes/resposta/saida_2.txt 
	$(EXE) -i ../testes/input/entrada_3.txt -o ../testes/outputs/teste_3.txt -p ../temp/test.txt
	$(AUTOTESTE) -1 ../testes/outputs/teste_3.txt -2 ../testes/resposta/saida_3.txt
	$(EXE) -i ../testes/input/entrada_4.txt -o ../testes/outputs/teste_4.txt -p ../temp/test.txt
	$(AUTOTESTE) -1 ../testes/outputs/teste_4.txt -2 ../testes/resposta/saida_4.txt

clean:
	rm -f $(OBJ)/* $(BIN)/* *.out ../temp/*

jogar: $(EXE)
	$(EXE) -p ../temp/gprofTeste.out -i entrada.txt -o saida.txt -l

gdb: $(EXE) 
	gdb $(EXE)

tp3: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(FER) -o $(EXE) $(OBJS) $(LIBS)

$(OBJ)/Servidor.o: $(HDRS) $(SRC)/Servidor.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Servidor.o $(SRC)/Servidor.cpp 

$(OBJ)/ArvoreB.o: $(HDRS) $(SRC)/ArvoreB.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/ArvoreB.o $(SRC)/ArvoreB.cpp 

$(OBJ)/Hash.o: $(HDRS) $(SRC)/Hash.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Hash.o $(SRC)/Hash.cpp 

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