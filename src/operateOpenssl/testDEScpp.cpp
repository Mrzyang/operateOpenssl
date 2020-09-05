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
	//设置密钥
	DES_set_key(&key,&key_sch);
	//数据加密
	DES_ecb_encrypt((const_DES_cblock*)data, (DES_cblock*)out, &key_sch, DES_ENCRYPT);
	cout << "加密结果:" << out << endl;
	//数据解密
	DES_ecb_encrypt((const_DES_cblock*)out, (DES_cblock*)out2, &key_sch, DES_DECRYPT);
	cout << "解密结果:" << out2 << endl;
}