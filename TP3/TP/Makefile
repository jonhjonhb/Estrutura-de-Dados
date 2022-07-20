#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa TP3
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
TST = ../testes
AUTOTESTE = $(TST)/comparator

all: tp3 bin

desempenho: tp3 gpNumUser gpMsg gpTamMsg gpDist

gpNumUser:
	$(EXE) -i $(TST)/input/input_NumUsers1.txt -o $(TST)/outputs/input_NumUsers1.txt -p ../temp/NumUsers1.txt
	gprof $(EXE) gmon.out > ../temp/GprofNumUsers1.txt
	$(EXE) -i $(TST)/input/input_NumUsers2.txt -o $(TST)/outputs/input_NumUsers2.txt -p ../temp/NumUsers2.txt
	gprof $(EXE) gmon.out > ../temp/GprofNumUsers2.txt
	$(EXE) -i $(TST)/input/input_NumUsers3.txt -o $(TST)/outputs/input_NumUsers3.txt -p ../temp/NumUsers3.txt
	gprof $(EXE) gmon.out > ../temp/GprofNumUsers3.txt

gpMsg:
	$(EXE) -i $(TST)/input/input_Msg1.txt -o $(TST)/outputs/input_Msg1.txt -p ../temp/Msg1.txt
	gprof $(EXE) gmon.out > ../temp/GprofMsg1.txt
	$(EXE) -i $(TST)/input/input_Msg2.txt -o $(TST)/outputs/input_Msg2.txt -p ../temp/Msg2.txt
	gprof $(EXE) gmon.out > ../temp/GprofMsg2.txt
	$(EXE) -i $(TST)/input/input_Msg3.txt -o $(TST)/outputs/input_Msg3.txt -p ../temp/Msg3.txt
	gprof $(EXE) gmon.out > ../temp/GprofMsg3.txt

gpTamMsg:
	$(EXE) -i $(TST)/input/input_tamMsg1.txt -o $(TST)/outputs/input_tamMsg1.txt -p ../temp/tamMsg1.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_tamMsg1.txt
	$(EXE) -i $(TST)/input/input_tamMsg2.txt -o $(TST)/outputs/input_tamMsg2.txt -p ../temp/tamMsg2.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_tamMsg2.txt
	$(EXE) -i $(TST)/input/input_tamMsg3.txt -o $(TST)/outputs/input_tamMsg3.txt -p ../temp/tamMsg3.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_tamMsg3.txt

gpDist:
	$(EXE) -i $(TST)/input/dist_20-20_1.txt -o $(TST)/outputs/dist_20-20_1.txt -p ../temp/dist_20-20_1.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_20-20_1.txt
	$(EXE) -i $(TST)/input/dist_20-20_2.txt -o $(TST)/outputs/dist_20-20_2.txt -p ../temp/dist_20-20_2.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_20-20_2.txt
	$(EXE) -i $(TST)/input/dist_20-20_3.txt -o $(TST)/outputs/dist_20-20_3.txt -p ../temp/dist_20-20_3.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_20-20_3.txt
	$(EXE) -i $(TST)/input/dist_20-20_4.txt -o $(TST)/outputs/dist_20-20_4.txt -p ../temp/dist_20-20_4.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_20-20_4.txt
	$(EXE) -i $(TST)/input/dist_20-20_5.txt -o $(TST)/outputs/dist_20-20_5.txt -p ../temp/dist_20-20_5.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_20-20_5.txt
	$(EXE) -i $(TST)/input/dist_100-0_1.txt -o $(TST)/outputs/dist_100-0_1.txt -p ../temp/dist_100-0_1.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_100-0_1.txt
	$(EXE) -i $(TST)/input/dist_100-0_2.txt -o $(TST)/outputs/dist_100-0_2.txt -p ../temp/dist_100-0_2.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_100-0_2.txt
	$(EXE) -i $(TST)/input/dist_100-0_3.txt -o $(TST)/outputs/dist_100-0_3.txt -p ../temp/dist_100-0_3.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_100-0_3.txt
	$(EXE) -i $(TST)/input/dist_100-0_4.txt -o $(TST)/outputs/dist_100-0_4.txt -p ../temp/dist_100-0_4.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_100-0_4.txt
	$(EXE) -i $(TST)/input/dist_100-0_5.txt -o $(TST)/outputs/dist_100-0_5.txt -p ../temp/dist_100-0_5.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_100-0_5.txt
	$(EXE) -i $(TST)/input/dist_0-100_1.txt -o $(TST)/outputs/dist_0-100_1.txt -p ../temp/dist_0-100_1.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_0-100_1.txt
	$(EXE) -i $(TST)/input/dist_0-100_2.txt -o $(TST)/outputs/dist_0-100_2.txt -p ../temp/dist_0-100_2.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_0-100_2.txt
	$(EXE) -i $(TST)/input/dist_0-100_3.txt -o $(TST)/outputs/dist_0-100_3.txt -p ../temp/dist_0-100_3.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_0-100_3.txt
	$(EXE) -i $(TST)/input/dist_0-100_4.txt -o $(TST)/outputs/dist_0-100_4.txt -p ../temp/dist_0-100_4.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_0-100_4.txt
	$(EXE) -i $(TST)/input/dist_0-100_5.txt -o $(TST)/outputs/dist_0-100_5.txt -p ../temp/dist_0-100_5.txt
	gprof $(EXE) gmon.out > ../temp/Gprof_dist_0-100_5.txt

comp: tp3
	$(EXE) -i $(TST)/input/entrada_1.txt -o $(TST)/outputs/teste_1.txt -p ../temp/test.txt
	$(EXE) -i $(TST)/input/entrada_2.txt -o $(TST)/outputs/teste_2.txt -p ../temp/test.txt
	$(EXE) -i $(TST)/input/entrada_3.txt -o $(TST)/outputs/teste_3.txt -p ../temp/test.txt
	$(EXE) -i $(TST)/input/entrada_4.txt -o $(TST)/outputs/teste_4.txt -p ../temp/test.txt
	$(AUTOTESTE) -1 $(TST)/outputs/teste_1.txt -2 $(TST)/resposta/saida_1.txt
	$(AUTOTESTE) -1 $(TST)/outputs/teste_2.txt -2 $(TST)/resposta/saida_2.txt 
	$(AUTOTESTE) -1 $(TST)/outputs/teste_3.txt -2 $(TST)/resposta/saida_3.txt
	$(AUTOTESTE) -1 $(TST)/outputs/teste_4.txt -2 $(TST)/resposta/saida_4.txt

clean:
	rm -f $(OBJ)/* $(BIN)/* *.out ../temp/*

jogar: $(EXE)
	$(EXE) -p ../temp/partidagprof.out -i entrada.txt -o saida.txt -l

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

perf: jogar
	$(ANALISAMEM) -i ../temp/partidagprof.out -p ../temp/perf
	gnuplot ../temp/*.gp

teste: clean jogar gprof perf