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

	//cout << "�ַ�a��ֵ: "<< a <<"\n" << "�ڴ��ַ��"<<(unsigned int)&a<< endl;
	while (getchar()) {
		str += "zy|";
		cout << "�ַ���str��ֵ: " << str << "\n" << "�ڴ��ַ��" << (unsigned int)&str << endl;
	}
	return 0;
}