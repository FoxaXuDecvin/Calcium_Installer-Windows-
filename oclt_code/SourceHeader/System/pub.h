//DeF

#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<random>

using namespace std;
//MAIN

int checkChar(string text, string chechchar) {
	const char* c = chechchar.c_str();

	if (text.find(c) != string::npos) {
		return 1;
	}
	else {
		return 0;
	}
}

//Replace Char
string ReplaceChar(string info, string replaceword, string nword) {
	//cout << "New Replace :  _" << info << "_  _" << replaceword << "_  _" << nword << "_" << endl;
	int checkanti = checkChar(info, replaceword);
	if (checkanti == 1) {
		std::string dst_str = info;
		std::string::size_type pos = 0;
		while ((pos = dst_str.find(replaceword)) != std::string::npos)
		{
			dst_str.replace(pos, replaceword.length(), nword);
		}
		//cout << "Return Data :  _" << dst_str <<"_" << endl;
		return dst_str;
	}
	else {
		//cout << "Return Data :  _" << info << "_" << endl;
		return info;
	}
}

void _api_prtmsg(string msg) {
	printf(msg.c_str());
	return;
}

//Calcium Copy
//Read Env NEW
string _api_PartRead(string Info, string StartMark, string EndMark) {
	int MaxInfoSize = Info.size();
	int startmarkadd, endmarkadd, readptr;
	string readbufferPR;
	readptr = 0;

	if (StartMark == "$FROMSTART$") {
		startmarkadd = 0;
		goto SKIPGETMARKSTART;
	}

	//GetStart
	for (; readbufferPR != StartMark; readptr++) {
		if (readptr > MaxInfoSize) {
			//cout << "Message :  " << Info << endl;
			return "notfoundstart :  " + Info;
		}
		readbufferPR = Info[readptr];
	}

	startmarkadd = readptr;

SKIPGETMARKSTART:
	readbufferPR = "";
	//GetEnd
	if (EndMark == "$FROMEND$") {
		endmarkadd = MaxInfoSize;
		goto skipENDGET;
	}
	for (; readbufferPR != EndMark; readptr++) {
		if (readptr > MaxInfoSize) {
			return "notfoundEnd :  " + Info;
		}
		readbufferPR = Info[readptr];
	}

	endmarkadd = readptr;
	endmarkadd--;

skipENDGET:
	//cout << "Start :  " << startmarkadd << "  End :  " << endmarkadd << endl;

	//Start Process CMD

	//ReadPTR
	readbufferPR = "";
	for (readptr = startmarkadd; readptr != endmarkadd; readptr++) {
		readbufferPR = readbufferPR + Info[readptr];
	}

	return readbufferPR;
}

int _str_system(string msg) {
	return system(msg.c_str());
}