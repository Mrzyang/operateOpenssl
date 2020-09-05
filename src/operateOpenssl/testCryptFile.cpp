#pragma once
#include<iostream>
#include<openssl/des.h>
#include<fstream>
using namespace std;

void testCryptFile(int argc, char* argv[]) {
	string cmd = "�����ļ�(crypt file, 3 args) {�����ļ���} {����ļ���} {����(6 byte)} \n";
	cmd += "�����ļ�(decrypt file, 4 args) {�����ļ���} {����ļ���} {����(6)} -d \n";
	cout << cmd << endl;
	if (argc < 4) {
		cerr << "param error" << endl;
		return;
	}
	//�����ļ�
	string in_file = argv[1]; //�����ļ�
	string out_file = argv[2]; //����ļ�
	string password = argv[3]; //��Կ
	int is_encrypt = DES_ENCRYPT;
	if (argc > 4) 
		is_encrypt = DES_DECRYPT;//����
	//�����ƴ��ļ�
	ifstream ifs(in_file, ios::binary);
	if (!ifs) {
		cerr << "in_file:  " << in_file << "  open failed!" << endl;
		return;
	}

	//�����ƴ�����ļ�
	ofstream ofs(out_file, ios::binary);
	if (!ofs) {
		cerr << "out_file:  " << out_file << "  open failed!" << endl;
		return;
	}
	
	//������Կ,�ദ�������ٵĲ�0
	int key_size = password.size();
	const_DES_cblock key = { 0 };
	if (key_size > sizeof(key))
		key_size = sizeof(key);//�������
	memcpy(key, password.c_str(), key_size);
	DES_key_schedule key_sch;
	DES_set_key(&key, &key_sch);//������Կ

	const_DES_cblock in;//��������
	DES_cblock out;//�������

	// `1.���ļ� => 2.�ӽ����ļ� => 3.д���ļ�
	while (!ifs.eof()) {
		//1.���ļ�
		ifs.read((char*)in, sizeof(in));
		int count = ifs.gcount();
		if (count <= 0) break;

		//2.�ӽ����ļ�
		DES_ecb_encrypt(&in, &out, &key_sch, is_encrypt);

		//3.д���ļ�
		ofs.write((char*)out, sizeof(out));
	}
	if (is_encrypt == 1)
		cout << in_file << "���ܳɹ�������ļ�Ϊ" << out_file << endl;
	else
		cout << in_file << "���ܳɹ�������ļ�Ϊ" << out_file << endl;

	//�ͷ���Դ���ر�io
	ifs.close();
	ofs.close();
}