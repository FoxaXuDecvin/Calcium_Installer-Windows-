// Var Space  - Based on CalciumProject/VarSpace.h

#pragma once
#include"../shload.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
//PUBLIC API

//HEAD
string _Old_VSAPI_TransVar(string Info);

//
string VarSpace = "varspace;";
int VarSpaceMax;

string readvar;
string varhead;
string varset;

string getfullLine;
string ResChar;
string ReplaceCharX;
string backinfo;

int checkCharA(string text, string chechchar) {
	const char* c = chechchar.c_str();

	if (text.find(c) != string::npos) {
		return 1;
	}
	else {
		return 0;
	}
}

string ReplaceCharA(string info, string replaceword, string nword) {
	//cout << "New Replace :  _" << info << "_  _" << replaceword << "_  _" << nword << "_" << endl;
	int checkanti = checkCharA(info, replaceword);
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

string cutlineblockB(string lines, string cutmark, int line) {
	string backapi;

	if (checkCharA(lines, cutmark) == 0) {
		return "NUL";
	}

	char* readcut = NULL;

	char Texts[65535] = "a";
	char CUMark[65535] = "a";

	strcpy(Texts, lines.c_str());
	strcpy(CUMark, cutmark.c_str());

	int cutrecord = 1;
	char* token = strtok(Texts, CUMark);
	if (token == NULL) {
		backapi = "";
		return backapi;
	}

	if (cutrecord == line) {

		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}

NextRollCR:
	if (cutrecord == line) {
		//cout << "CUTLINEBLOCK CHECK OK, RETURN :  _" << token << "_" << endl;
		backapi = token;
		return backapi;
	}
	if (token == NULL) {
		backapi = "";
		return backapi;
	}
	cutrecord++;
	token = strtok(NULL, CUMark);
	goto NextRollCR;
}


// 0 - OK
// 1 - Error
int _varspaceadd(string VarHead, string varinfo) {
	//cout << "GET " << endl;
	VarHead = ReplaceCharA(VarHead, " ", "");
	//cout << "START VAR" << endl;

	readbufferA = _Old_VSAPI_TransVar(VarHead);
	if (readbufferA == varinfo) {
		//cout << "NO EDIT" << endl;
		return 0;
	}

	if (varinfo == "") {
		//cout << "VAR EMPTY" << endl;
		_varspaceadd(VarHead, "{varspace.null}");
		return 0;
	}

	varinfo = ReplaceCharA(varinfo, " ", "%sbar%");
	varinfo = ReplaceCharA(varinfo, ";", "%selbar%");
	varinfo = ReplaceCharA(varinfo, "=","%eqbar%");
	varinfo = ReplaceCharA(varinfo, "$", "%mnbar%");
	varinfo = ReplaceCharA(varinfo, "\\", "%B_SLASH%");
	varinfo = ReplaceCharA(varinfo, "\n", "%$LineFeed%");
	if (checkCharA(VarHead, ";") == 1) {
		cout << "There is illegal text in the var" << endl;
		return 1;
	}

	if (VarSpaceMax == 0) {

		VarSpace = VarSpace + VarHead + "=" + varinfo + ";";

		VarSpaceMax++;

		return 0;
	}

	int startReadVar = 2;


BackFoundOldLine:
	//%var Mark Reader
	//cout << "readvar Head :  " << VarSpace << ".  " << VarHead << "_  " << to_string(startReadVar) << "_." << endl;
	readvar = cutlineblockB(VarSpace, ";", startReadVar);
	//cout << "readvar : " << readvar << endl;
	readvar = ReplaceCharA(readvar, ";", "");
	//cout << "readvar After Clean : " << readvar << endl;

	//Get XX = NN

	varhead = cutlineblockB(readvar, "=", 1);

	if (varhead == VarHead) {
		//cout << "Varhead : _" << varhead << "_. Select :  _" << VarHead << "_" << endl;
		varset = cutlineblockB(readvar, "=", 2);
		//cout << "Var Set :  _" << varset << "_" << endl;
		string delvars = varhead + "=" + varset + ";";
		string newvars = varhead + "=" + varinfo + ";";
		//cout << "Sort Delete Info :  _" << delvars << "_ .  ResData :  _" << VarSpace << "_" << endl;
		VarSpace = ReplaceCharA(VarSpace, delvars, newvars);
		//cout << "After CUT :  _" << VarSpace << "_" << endl;
		//cout << "After VarMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
		//cout << "Var Space is Update.  Max : " << to_string(VarSpaceMax) << " . Message:   " << VarSpace << endl;
		return 0;
	}

	startReadVar--;
	//cout << "IF Command :  _" << to_string(startReadVar) << "_  . VMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
	if (startReadVar == VarSpaceMax) {

		VarSpace = VarSpace + VarHead + "=" + varinfo + ";";

		VarSpaceMax++;

		return 0;
	}

	startReadVar++;
	startReadVar++;
	goto BackFoundOldLine;
}

void _varspacedelete(string VarHead) {
	//cout << "Delete Var Space :  _" << VarHead << "_" << endl;

	if (VarSpaceMax == 0) {
		return;
	}
	int startReadVar = 2;


BackFoundLine:
	//%var Mark Reader
	//cout << "readvar Head :  _" << VarSpace << "_.  _" << VarHead << "_  _" << to_string(startReadVar) << "_." << endl;
	readvar = cutlineblockB(VarSpace, ";", startReadVar);
	//cout << "readvar : " << readvar << endl;
	readvar = ReplaceCharA(readvar, ";", "");
	//cout << "readvar After Clean : " << readvar << endl;

	//Get XX = NN

	varhead = cutlineblockB(readvar, "=", 1);

	if (varhead == VarHead) {
		//cout << "Varhead : _" << varhead << "_. Select :  _" << VarHead << "_" << endl;
		varset = cutlineblockB(readvar, "=", 2);
		//cout << "Var Set :  _" << varset << "_" << endl;
		string delvars = varhead + "=" + varset + ";";
		//cout << "Sort Delete Info :  _" << delvars << "_ .  ResData :  _" << VarSpace << "_" << endl;
		VarSpace = ReplaceCharA(VarSpace, delvars, "");
		//cout << "After CUT :  _" << VarSpace << "_" << endl;
		VarSpaceMax--;
		//cout << "After VarMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
		//cout << "Var Space is Update.  Max : " << to_string(VarSpaceMax) << " . Message:   " << VarSpace << endl;
		return;
	}

	startReadVar--;
	//cout << "IF Command :  _" << to_string(startReadVar) << "_  . VMAX :  _" << to_string(VarSpaceMax) << "_" << endl;
	if (startReadVar == VarSpaceMax) {
		return;
	}

	startReadVar++;
	startReadVar++;
	goto BackFoundLine;
}

string _Old_VSAPI_TransVar(string Info) {
	backinfo = Info;

	if (VarSpaceMax == 0) {
		return backinfo;
	}

	for (int startrollmax = 0, readmark = 2; startrollmax < VarSpaceMax; startrollmax++, readmark++) {
		getfullLine = cutlineblockB(VarSpace, ";", readmark);
		ResChar = cutlineblockB(getfullLine, "=", 1);
		ReplaceCharX = cutlineblockB(getfullLine, "=", 2);
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%sbar%", " ");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%selbar%", ";");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%eqbar%", "=");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%mnbar%", "$");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%B_SLASH%", "\\");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%$LineFeed%", "\n");
		//cout << "Process Env :  " << startrollmax << "      RM :  " << readmark << endl;
		int checkChar(string text, string chechchar);
		backinfo = ReplaceCharA(backinfo, ResChar, ReplaceCharX);
	}

	return backinfo;
}

string _getvarspace(string VarHead) {
	backinfo = VarHead;

	if (VarSpaceMax == 0) {
		return backinfo;
	}

	for (int startrollmax = 0, readmark = 2; startrollmax < VarSpaceMax; startrollmax++, readmark++) {
		getfullLine = cutlineblockB(VarSpace, ";", readmark);
		ResChar = cutlineblockB(getfullLine, "=", 1);
		ReplaceCharX = cutlineblockB(getfullLine, "=", 2);
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%sbar%", " ");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%selbar%", ";");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%eqbar%", "=");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%mnbar%", "$");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%B_SLASH%", "\\");
		ReplaceCharX = ReplaceCharA(ReplaceCharX, "%$LineFeed%", "\n");

		int checkChar(string text, string chechchar);
		backinfo = ReplaceCharA(backinfo, ResChar, ReplaceCharX);
	}

	return backinfo;
}

void _clear_varspace(void) {
	VarSpace = "varspace;";
	VarSpaceMax = 0;
}