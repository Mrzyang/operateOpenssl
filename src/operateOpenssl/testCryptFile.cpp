#pragma once
#include<iostream>
#include<openssl/des.h>
#include<fstream>
using namespace std;

void testCryptFile(int argc, char* argv[]) {
	string cmd = "�����ļ�(crypt file, 3 args) {�����ļ���} {����ļ���} {����(6 byte)} \n";
	cmd += "�����ļ�(decrypt file, 4 args) {�����ļ���} {����ļ���} {����(6)} {-d} \n";
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

	//��ȡ�ļ���С
	long long filesize = 0;
	ifs.seekg(0, ios::end);//�ļ�ָ���ƶ�����β
	filesize = ifs.tellg();
	ifs.seekg(0, ios::beg);//�ļ�ָ���ƶ���ͷ��
	cout << "filezie = " << filesize <<" bytes" << endl; 

	long long read_size = 0; //�Ѿ����˶����ֽ�
	long long write_size = 0;//�Ѿ����������д�˶����ֽ�

	// `1.���ļ� => 2.�ӽ����ļ� => 3.д���ļ�
	while (!ifs.eof()) {
		//ÿ��д���ֽڴ�С
		int out_len = sizeof(out);
		//1.���ļ�
		ifs.read((char*)in, sizeof(in));
		int count = ifs.gcount();
		if (count <= 0) break;
		read_size += count;

		//PKCS7 Padding ���
		//���ܵ���β�����
		if (read_size == filesize && is_encrypt == DES_ENCRYPT) {
			if (filesize % 8 == 0) {//���8�ֽڵ�ֵΪ8
				//��д�뵱ǰ����
				DES_ecb_encrypt(&in, &out, &key_sch, is_encrypt);
				ofs.write((char*)out, out_len);

				//�������8
				memset(in, 8, sizeof(int));
			}
			else {
				int padding = 8 - filesize % 8;//Ҫ�����ֽ�
				//�Ƶ�λ���������
				memset(in + (filesize % 8), padding, padding);
			}
		}

		//2.�ӽ����ļ�
		DES_ecb_encrypt(&in, &out, &key_sch, is_encrypt);

		//���ܽ�β��padding
		if (read_size == filesize && is_encrypt == DES_DECRYPT) {
			//��ȥ����С
			out_len = 8 - out[7];
		}
		if (out_len <= 0) break;

		//3.д���ļ�
		ofs.write((char*)out, out_len);
		write_size += out_len;
	}
	if (is_encrypt == 1)
		cout << in_file << "���ܳɹ�������ļ�Ϊ" << out_file << endl;
	else
		cout << in_file << "���ܳɹ�������ļ�Ϊ" << out_file << endl;

	//�ͷ���Դ���ر�io
	ifs.close();
	ofs.close();

	cout << "write:" << write_size << " bytes" << endl;
}