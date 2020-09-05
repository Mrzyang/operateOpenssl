#include<iostream>
#include"testRand.h"
#include "testDES.h"
#include "testCryptFile.h"
using namespace std;

int main(int argc, char* argv[]) {
	cout << "operate openssl_v1.1.1g_x64" << endl; 
	//testRand();
	//testDES();
	testCryptFile(argc, argv);
	//getchar();
	return 0;
}