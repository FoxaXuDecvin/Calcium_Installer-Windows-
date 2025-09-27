//Switch Tools
#pragma once
#include "../SourceHeader/include.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

//Message
string $_pause = "Press Enter...   ";

string _swt_buffer;

//Main
void _pause() {
	printf($_pause.c_str());
	getchar();
	return;
}

string _getline_type(void) {
	getline(cin, _swt_buffer);
	return _swt_buffer;
}