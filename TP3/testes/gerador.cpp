#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <iostream>


std::string gen_random(const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    
    return tmp_s;
}

void execute(int number, int hashsize, int nofwords, int nofusers, char* name, int consultPercent=100, int removalPercent=100){
	std::cout << "Creating file " << name << std::endl;
    unsigned long j;
    srand( (unsigned)time(NULL) );

	const int hashRange = hashsize;
	const int wordsRange = nofwords;
	const int maxWordSize = 10;
	const int nElements = number;

	std::fstream out;
	out.open(name, std::fstream::out);
	std::fstream outRemovals;
	outRemovals.open((char*)"outRemovals.txt", std::fstream::out);
	std::fstream outConsults;
	outConsults.open((char*)"outConsults.txt", std::fstream::out);

	out << hashRange << std::endl;
	
    for( j = 0; j < nElements; ++j ){
        int n;

        while( ( n = rand() ) > RAND_MAX - (RAND_MAX-hashRange-1)%hashRange ){}

		int temp = n%(nofusers);
		int nWords = n%wordsRange + 1;
		out << "ENTREGA " << temp << " " << j+1 << " " << nWords << " ";
		if(consultPercent != 100 && consultPercent != 0) { if(rand()%100 < consultPercent) outConsults << "CONSULTA " << temp << " " << j+1 << std::endl; }
		else if(consultPercent != 0) outConsults << "CONSULTA " << temp << " " << j+1 << std::endl;
		if(removalPercent != 100 && removalPercent != 0) { if(rand()%100 < removalPercent) outRemovals << "APAGA " << temp << " " << j+1 << std::endl; }
		else if(removalPercent != 0) outRemovals << "APAGA " << temp << " " << j+1 << std::endl;

		for(int i = 0; i < nWords; ++i){
			int size;
			while( ( size = rand() ) > RAND_MAX - (RAND_MAX-maxWordSize-1)%maxWordSize ){}
			out << gen_random(size%maxWordSize+1);
			if(i<nWords-1) out << " ";
		}
		out << std::endl;
    }

	std::ifstream if_a("outConsults.txt", std::ios_base::binary);
	std::ifstream if_b("outRemovals.txt", std::ios_base::binary);

	
	out << if_a.rdbuf() << if_b.rdbuf();
}

int main(void){

	// // GrÃ¡fico de acessos
	// execute(1000,50,10,200,(char*)"entradas/regmem_load.txt");

	// execute(10000,500,10,200,(char*)"entradas/out_numusers_1.txt");
	// execute(10000,500,10,400,(char*)"entradas/out_numusers_2.txt");
	// execute(10000,500,10,600,(char*)"entradas/out_numusers_3.txt");
	// execute(10000,500,10,800,(char*)"entradas/out_numusers_4.txt");
	// execute(10000,500,10,1000,(char*)"entradas/out_numusers_5.txt");

	// execute(100000,50,10,200,(char*)"entradas/out_1.txt");
	// execute(200000,50,10,200,(char*)"entradas/out_2.txt");
	// execute(300000,50,10,200,(char*)"entradas/out_3.txt");
	// execute(400000,50,10,200,(char*)"entradas/out_4.txt");
	// execute(500000,50,10,200,(char*)"entradas/out_5.txt");

	// execute(10000,50,10,200,(char*)"entradas/out_msgsize_1.txt",0,0);
	// execute(10000,50,100,200,(char*)"entradas/out_msgsize_2.txt",0,0);
	// execute(10000,50,1000,200,(char*)"entradas/out_msgsize_3.txt",0,0);
	// execute(10000,50,10000,200,(char*)"entradas/out_msgsize_4.txt",0,0);
	// execute(10000,50,100000,200,(char*)"entradas/out_msgsize_5.txt",0,0);

	execute(10000,50,10,200,(char*)"input/dist_20-20_1.txt",20,20);
	execute(20000,50,10,200,(char*)"input/dist_20-20_2.txt",20,20);
	execute(30000,50,10,200,(char*)"input/dist_20-20_3.txt",20,20);
	execute(40000,50,10,200,(char*)"input/dist_20-20_4.txt",20,20);
	execute(50000,50,10,200,(char*)"input/dist_20-20_5.txt",20,20);

	execute(10000,50,10,200,(char*)"input/dist_100-0_1.txt",100,0);
	execute(20000,50,10,200,(char*)"input/dist_100-0_2.txt",100,0);
	execute(30000,50,10,200,(char*)"input/dist_100-0_3.txt",100,0);
	execute(40000,50,10,200,(char*)"input/dist_100-0_4.txt",100,0);
	execute(50000,50,10,200,(char*)"input/dist_100-0_5.txt",100,0);

	execute(10000,50,10,200,(char*)"input/dist_0-100_1.txt",0,100);
	execute(20000,50,10,200,(char*)"input/dist_0-100_2.txt",0,100);
	execute(30000,50,10,200,(char*)"input/dist_0-100_3.txt",0,100);
	execute(40000,50,10,200,(char*)"input/dist_0-100_4.txt",0,100);
	execute(50000,50,10,200,(char*)"input/dist_0-100_5.txt",0,100);
}