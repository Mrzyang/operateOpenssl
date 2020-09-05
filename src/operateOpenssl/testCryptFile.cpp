#pragma once
#include<iostream>
#include<openssl/des.h>
#include<fstream>
using namespace std;

void testCryptFile(int argc, char* argv[]) {
	string cmd = "加密文件(crypt file, 3 args) {输入文件名} {输出文件名} {密码(6 byte)} \n";
	cmd += "加密文件(decrypt file, 4 args) {输入文件名} {输出文件名} {密码(6)} -d \n";
	cout << cmd << endl;
	if (argc < 4) {
		cerr << "param error" << endl;
		return;
	}
	//输入文件
	string in_file = argv[1]; //输入文件
	string out_file = argv[2]; //输出文件
	string password = argv[3]; //密钥
	int is_encrypt = DES_ENCRYPT;
	if (argc > 4) 
		is_encrypt = DES_DECRYPT;//解密
	//二进制打开文件
	ifstream ifs(in_file, ios::binary);
	if (!ifs) {
		cerr << "in_file:  " << in_file << "  open failed!" << endl;
		return;
	}

	//二进制打开输出文件
	ofstream ofs(out_file, ios::binary);
	if (!ofs) {
		cerr << "out_file:  " << out_file << "  open failed!" << endl;
		return;
	}
	
	//处理密钥,多处丢掉，少的补0
	int key_size = password.size();
	const_DES_cblock key = { 0 };
	if (key_size > sizeof(key))
		key_size = sizeof(key);//多出丢掉
	memcpy(key, password.c_str(), key_size);
	DES_key_schedule key_sch;
	DES_set_key(&key, &key_sch);//设置密钥

	const_DES_cblock in;//输入数据
	DES_cblock out;//输出数据

	// `1.读文件 => 2.加解密文件 => 3.写入文件
	while (!ifs.eof()) {
		//1.读文件
		ifs.read((char*)in, sizeof(in));
		int count = ifs.gcount();
		if (count <= 0) break;

		//2.加解密文件
		DES_ecb_encrypt(&in, &out, &key_sch, is_encrypt);

		//3.写入文件
		ofs.write((char*)out, sizeof(out));
	}
	if (is_encrypt == 1)
		cout << in_file << "加密成功，输出文件为" << out_file << endl;
	else
		cout << in_file << "解密成功，输出文件为" << out_file << endl;

	//释放资源，关闭io
	ifs.close();
	ofs.close();
}