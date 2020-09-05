#include"testDES.h"
#include<openssl/des.h>
#include<time.h>
#include<iostream>
using namespace std;

void testDES() {
	unsigned char data[] = "12345678";
	unsigned char out[1024] = { 0 };
	unsigned char out2[1024] = { 0 };
	unsigned char key[] = "1234567";
	DES_key_schedule key_sch;
	//������Կ
	DES_set_key(&key,&key_sch);
	//���ݼ���
	DES_ecb_encrypt((const_DES_cblock*)data, (DES_cblock*)out, &key_sch, DES_ENCRYPT);
	cout << "���ܽ��:" << out << endl;
	//���ݽ���
	DES_ecb_encrypt((const_DES_cblock*)out, (DES_cblock*)out2, &key_sch, DES_DECRYPT);
	cout << "���ܽ��:" << out2 << endl;
}