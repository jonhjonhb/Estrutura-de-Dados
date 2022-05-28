#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#               : 2021-11-15 - Versao 1.1 memlog
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o $(OBJ)/memlog.o
HDRS = $(INC)/mat.h $(INC)/memlog.h $(INC)/msgassert.h
OBJSM = $(OBJ)/pilhaindexada.o $(OBJ)/analisamem.o
HDRSM = $(INC)/pilhaindexada.h $(INC)/msgassert.h
CFLAGS = -pg -Wall -c -I$(INC)

EXE = $(BIN)/matop

all:  bin mem perf gprof

mem: $(EXE)
	rm -rf /tmp/TP0
	mkdir /tmp/TP0
	mkdir /tmp/TP0/gprof
	mkdir /tmp/TP0/soma
	$(EXE) -s -p /tmp/TP0/soma/somalog.out -o resultSoma.out -1 ../teste/matriz10x10.txt -2 ../teste/matriz10x10.txt -l
	$(BIN)/analisamem -i /tmp/TP0/soma/somalog.out -p /tmp/TP0/soma/soma
	gnuplot /tmp/TP0/soma/*.gp
	mkdir /tmp/TP0/mult
	$(EXE) -m -p /tmp/TP0/mult/multlog.out -o resultMult.out -1 ../teste/matriz7x8.txt -2 ../teste/matriz8x7.txt -l
	$(BIN)/analisamem -i /tmp/TP0/mult/multlog.out -p /tmp/TP0/mult/mult
	gnuplot /tmp/TP0/mult/*.gp
	mkdir /tmp/TP0/transp
	$(EXE) -t -p /tmp/TP0/transp/transplog.out -o resultTransp.out -1 ../teste/matriz2x8.txt -l
	$(BIN)/analisamem -i /tmp/TP0/transp/transplog.out -p /tmp/TP0/transp/transp
	gnuplot /tmp/TP0/transp/*.gp

perf: $(EXE)
	$(EXE) -s -p /tmp/TP0/soma1x1.out -1 ../teste/matriz1x1.txt -2 ../teste/matriz1x1.txt
	$(EXE) -m -p /tmp/TP0/mult1x1.out -1 ../teste/matriz1x1.txt -2 ../teste/matriz1x1.txt
	$(EXE) -t -p /tmp/TP0/transp1x1.out -1 ../teste/matriz1x1.txt
	
	$(EXE) -s -p /tmp/TP0/soma2x2.out -1 ../teste/matriz2x2.txt -2 ../teste/matriz2x2.txt
	$(EXE) -m -p /tmp/TP0/mult2x2.out -1 ../teste/matriz2x2.txt -2 ../teste/matriz2x2.txt
	$(EXE) -t -p /tmp/TP0/transp2x2.out -1 ../teste/matriz2x2.txt
	
	$(EXE) -s -p /tmp/TP0/soma3x3.out -1 ../teste/matriz3x3.txt -2 ../teste/matriz3x3.txt
	$(EXE) -m -p /tmp/TP0/mult3x3.out -1 ../teste/matriz3x3.txt -2 ../teste/matriz3x3.txt
	$(EXE) -t -p /tmp/TP0/transp3x3.out -1 ../teste/matriz3x3.txt
	
	$(EXE) -s -p /tmp/TP0/soma4x4.out -1 ../teste/matriz4x4.txt -2 ../teste/matriz4x4.txt
	$(EXE) -m -p /tmp/TP0/mult4x4.out -1 ../teste/matriz4x4.txt -2 ../teste/matriz4x4.txt
	$(EXE) -t -p /tmp/TP0/transp4x4.out -1 ../teste/matriz4x4.txt

	$(EXE) -s -p /tmp/TP0/soma5x5.out -1 ../teste/matriz5x5.txt -2 ../teste/matriz5x5.txt
	$(EXE) -m -p /tmp/TP0/mult5x5.out -1 ../teste/matriz5x5.txt -2 ../teste/matriz5x5.txt
	$(EXE) -t -p /tmp/TP0/transp5x5.out -1 ../teste/matriz5x5.txt
	
	$(EXE) -s -p /tmp/TP0/soma6x6.out -1 ../teste/matriz6x6.txt -2 ../teste/matriz6x6.txt
	$(EXE) -m -p /tmp/TP0/mult6x6.out -1 ../teste/matriz6x6.txt -2 ../teste/matriz6x6.txt
	$(EXE) -t -p /tmp/TP0/transp6x6.out -1 ../teste/matriz6x6.txt
	
	$(EXE) -s -p /tmp/TP0/soma7x7.out -1 ../teste/matriz7x7.txt -2 ../teste/matriz7x7.txt
	$(EXE) -m -p /tmp/TP0/mult7x7.out -1 ../teste/matriz7x7.txt -2 ../teste/matriz7x7.txt
	$(EXE) -t -p /tmp/TP0/transp7x7.out -1 ../teste/matriz7x7.txt
	
	$(EXE) -s -p /tmp/TP0/soma8x8.out -1 ../teste/matriz8x8.txt -2 ../teste/matriz8x8.txt
	$(EXE) -m -p /tmp/TP0/mult8x8.out -1 ../teste/matriz8x8.txt -2 ../teste/matriz8x8.txt
	$(EXE) -t -p /tmp/TP0/transp8x8.out -1 ../teste/matriz8x8.txt

	$(EXE) -s -p /tmp/TP0/soma9x9.out -1 ../teste/matriz9x9.txt -2 ../teste/matriz9x9.txt
	$(EXE) -m -p /tmp/TP0/mult9x9.out -1 ../teste/matriz9x9.txt -2 ../teste/matriz9x9.txt
	$(EXE) -t -p /tmp/TP0/transp9x9.out -1 ../teste/matriz9x9.txt
	
	$(EXE) -s -p /tmp/TP0/soma10x10.out -1 ../teste/matriz10x10.txt -2 ../teste/matriz10x10.txt
	$(EXE) -m -p /tmp/TP0/mult10x10.out -1 ../teste/matriz10x10.txt -2 ../teste/matriz10x10.txt
	$(EXE) -t -p /tmp/TP0/transp10x10.out -1 ../teste/matriz10x10.txt


gprof: $(BIN)/matop
	$(EXE) -s -p /tmp/TP0/gprof/soma500x500gprof.out -1 ../teste/matriz500x500.txt -2 ../teste/matriz500x500.txt
	gprof $(EXE) gmon.out > /tmp/TP0/gprof/soma500x500gprof.txt
	$(EXE) -m -p /tmp/TP0/gprof/mult500x500gprof.out -1 ../teste/matriz500x500.txt -2 ../teste/matriz500x500.txt
	gprof $(EXE) gmon.out > /tmp/TP0/gprof/mult500x500gprof.txt
	$(EXE) -t -p /tmp/TP0/gprof/transp500x500gprof.out -1 ../teste/matriz500x500.txt
	gprof $(EXE) gmon.out > /tmp/TP0/gprof/transp500x500gprof.txt
	
	$(EXE) -s -p /tmp/TP0/gprof/soma1000x1000gprof.out -1 ../teste/matriz1000x1000.txt -2 ../teste/matriz1000x1000.txt
	gprof $(EXE) gmon.out > /tmp/TP0/gprof/soma1000x1000gprof.txt
	$(EXE) -m -p /tmp/TP0/gprof/mult1000x1000gprof.out -1 ../teste/matriz1000x1000.txt -2 ../teste/matriz1000x1000.txt
	gprof $(EXE) gmon.out > /tmp/TP0/gprof/mult1000x1000gprof.txt
	$(EXE) -t -p /tmp/TP0/gprof/transp1000x1000gprof.out -1 ../teste/matriz1000x1000.txt
	gprof $(EXE) gmon.out > /tmp/TP0/gprof/transp1000x1000gprof.txt

	$(EXE) -s -p /tmp/TP0/gprof/soma1500x1500gprof.out -1 ../teste/matriz1500x1500.txt -2 ../teste/matriz1500x1500.txt
	gprof $(EXE) gmon.out > /tmp/TP0/gprof/soma1500x1500gprof.txt
	$(EXE) -m -p /tmp/TP0/gprof/mult1500x1500gprof.out -1 ../teste/matriz1500x1500.txt -2 ../teste/matriz1500x1500.txt
	gprof $(EXE) gmon.out > /tmp/TP0/gprof/mult1500x1500gprof.txt
	$(EXE) -t -p /tmp/TP0/gprof/transp1500x1500gprof.out -1 ../teste/matriz1500x1500.txt
	gprof $(EXE) gmon.out > /tmp/TP0/gprof/transp1500x1500gprof.txt
	

$(BIN)/matop: $(OBJS)
	$(CC) -pg -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 

$(OBJ)/memlog.o: $(HDRSM) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -o $(OBJ)/memlog.o $(SRC)/memlog.c 

bin: $(BIN)/analisamem

$(BIN)/analisamem: $(OBJSM)
	$(CC) -pg -o $(BIN)/analisamem $(OBJSM) $(LIBS)

$(OBJ)/analisamem.o: $(HDRSM) $(SRC)/analisamem.c
	$(CC) $(CFLAGS) -o $(OBJ)/analisamem.o $(SRC)/analisamem.c 

$(OBJ)/pilhaindexada.o: $(HDRSM) $(SRC)/pilhaindexada.c
	$(CC) $(CFLAGS) -o $(OBJ)/pilhaindexada.o $(SRC)/pilhaindexada.c 
	
clean:
	rm -f $(EXE) $(OBJS) $(OBJSM) $(BIN)/analisamem *.out
	rm -rf /tmp/TP0