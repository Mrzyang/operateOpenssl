#include<iostream>
#include"testRand.h"
#include "testDES.h"
#include "testCryptFile.h"
using namespace std;

int main(int argc, char* argv[]) {
	cout << "operate openssl_v1.1.1g_x64" << endl; 
	//testRand();
	//testDES();
	//testCryptFile(argc, argv);
	//getchar();
	string str = "admin";

	//cout << "字符a的值: "<< a <<"\n" << "内存地址："<<(unsigned int)&a<< endl;
	while (getchar()) {
		str += "zy|";
		cout << "字符串str的值: " << str << "\n" << "内存地址：" << (unsigned int)&str << endl;
	}
	return 0;
}