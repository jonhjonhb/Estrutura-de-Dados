#include <iostream>
#include <cstring>
#include <getopt.h>
#include <fstream>
using namespace std;

void parseArgs(int argc, char *argv[], char file1[], char file2[]){
	extern char *optarg;
	file1[0] = 0;
	file2[0] = 0;

	for(int opt; (opt=getopt(argc, argv, "i1:i2:")) != EOF;){
		switch(opt){
			case '1':
				strcpy(file1, optarg);
				break;

			case '2':
				strcpy(file2, optarg);
				break;
		}
	}
}

int main(int argc, char *argv[]){
	register int i;

	unsigned char buf1[1024], buf2[1024];
	
	char filename1[100], filename2[100];
	parseArgs(argc, argv, filename1, filename2);
	std::string strFileName1(filename1), strFileName2(filename2);

	ifstream f1(strFileName1, ios::in | ios::binary);
	if (!f1){
		cout << "Cannot open first file.\n";
		return 1;
	}
	ifstream f2(strFileName2, ios::in | ios::binary);
	if (!f2){
		cout << "Cannot open second file.\n";
		return 1;
	}

	//cout << "Comparing files...\n";

	do{
		f1.read((char *)buf1, sizeof buf1);
		f2.read((char *)buf2, sizeof buf2);
		if (f1.gcount() != f2.gcount()){
			cout << "\"\033[37mFiles \033[0;33m\""
					 << strFileName1 << "\"\033[37m and \033[0;33m\""
					 << strFileName2 << "\"\033[1;31m are of different sizes.\033[0m\"\n";
			f1.close();
			f2.close();
			return 0;
		}

		// compare contents of buffers
		for (i = 0; i < f1.gcount(); i++)
			if (buf1[i] != buf2[i]){
				cout << "\"\033[37mFiles \033[0;33m\""
					 << strFileName1 << "\"\033[37m and \033[0;33m\""
					 << strFileName2 << "\"\033[1;31m differ.\033[0m\"\n";
				f1.close();
				f2.close();
				return 0;
			}

	} while (!f1.eof() && !f2.eof());

	cout << "\"\033[37mFiles \033[0;33m\""
		 << strFileName1 << "\"\033[37m and \033[0;33m\""
		 << strFileName2 << "\"\033[1;36m are the same.\033[0m\"\n";

	f1.close();
	f2.close();

	return 0;
}