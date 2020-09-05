#include"testRand.h"
#include<openssl/rand.h>
#include<time.h>
#include<iostream>
using namespace std;

void testRand(){
	time_t t = time(0);
	unsigned char buf[16] = { 0 };
	int re = RAND_bytes(buf, sizeof(buf));
	for (int i = 0; i < sizeof(buf); i++) {
		cout << "[" << (int)buf[i] << "]";
	}
}