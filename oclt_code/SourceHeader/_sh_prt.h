//Print Advanced
#pragma once
#include "../SourceHeader/include.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

void _prtoutmsg(string message) {
	printf(message.c_str());
	printf("\n");
	return;
}

//Simple _prtoutmsg()
void _p(string message) {
	printf(message.c_str());
	printf("\n");
	return;
}

void _prts(string message) {
	printf(message.c_str());
	return;
}

void _prtendl(void) {
	printf("\n");
	return;
}

//Simple _prtend()
void _pn(void) {
	printf("\n");
	return;
}

void _coutmsg(string message) {
	cout << message << endl;
	return;
}