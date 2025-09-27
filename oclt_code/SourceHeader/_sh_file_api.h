//Source Header
// File API
// Copyright FoxaXu 2024

#include "../SourceHeader/include.h"
#define _CRT_SECURE_NO_WARNINGS
//DEF
string _fileapi_textread(string File, int line_number);

//API
const string sw_os_NULL = "null";

string sw_openfile_str = sw_os_NULL;

int CountLines(string filename)
{
	ifstream ReadFile;
	int n = 0;
	string tmp;
	ReadFile.open(filename.c_str());
	if (ReadFile.fail())
	{
		return 0;
	}
	else
	{
		while (getline(ReadFile, tmp, '\n'))
		{
			n++;
		}
		ReadFile.close();
		return n;
	}
}
int getdocmax(string file) {
	int maxread = 1;
BackCheckRUN:
	string ReadNULLCheck = _fileapi_textread(file, maxread);
	if (ReadNULLCheck == "overline") {
		maxread--;
		return maxread;
	}
	maxread++;
	goto BackCheckRUN;
}


//Main
bool _existfile(const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		return true;
	}
	else {
		return false;
	}
}

bool _fileapi_createmark(string File, string info) {
	ofstream CMark;
	CMark.open(File);
	CMark << info << endl;
	CMark.close();

	if (_existfile(File)) {
		return true;
	}
	else {
		return false;
	}
}

string _fileapi_textread(string File, int line_number) {
	if (_existfile(File)) {}
	else {
		_sh_throw_error("FileAPI.TextRead :  File Not Exist");
		return "FileNotExist";
	}
	int lines, i = 0;
	string temp;
	fstream file;
	file.open(File.c_str());
	lines = CountLines(File);

	if (line_number <= 0)
	{
		_sh_throw_error("FileAPI.TextRead :  Line Error On : " + File +" .  Line :  " + to_string(line_number));
		return "LineError";
	}
	if (file.fail())
	{
		_sh_throw_error("FileAPI.TextRead :  File Read Failed :  " + File);
		return "ReadFailed";
	}
	if (line_number > lines)
	{
		return "overline";
	}
	while (getline(file, temp) && i < line_number - 1)
	{
		i++;
	}
	file.close();
	return temp;
}

void _fileapi_typetext(string file) {
	if (_existfile(file)) {
		int maxdocsize = getdocmax(file);

		maxdocsize++;

		for (int startRoll = 1; maxdocsize != startRoll; startRoll++) {
			_api_prtmsg(_fileapi_textread(file, startRoll)+"\n");
		}
		return;
	}
	else {
		_sh_throw_error("FileAPI.TypeText :  File Not Exist");
		return;
	}
}

//File Write Not Clear
void _fileapi_write(string _fa_file, string _fa_info) {
	fstream f; 
	f.open(_fa_file, ios::out | ios::app); 
	f << _fa_info << endl;
	f.close();
	return;
}

//Copy/Delete
bool _fileapi_CpFile(string CopyFL, string CopyPath) {
	CopyFile(CopyFL.c_str(), CopyPath.c_str(), 0);
	if (check_file_existenceA(CopyPath)) {
		return true;
	}
	else {
		return false;
	}

	//Anti Cpp Code Check
	return false;
}

bool _fileapi_del(string DelFL) {
	remove(DelFL.c_str());

	if (check_file_existenceA(DelFL)) {
		return false;
	}
	else {
		return true;
	}

	//Anti Cpp Code Check
	return false;
}

//SoildWrite

bool _soildwrite_open(string sw_fileopen) {

	sw_openfile_str = sw_fileopen;

	return true;
}

bool _soildwrite_write(string info) {
	
	if (sw_openfile_str == sw_os_NULL) {
		return false;
	}

	_fileapi_write(sw_openfile_str,info);

	if (!check_file_existenceA(sw_openfile_str)) {
		_sh_throw_error("Failed open soildwrite :   " + sw_openfile_str);
		return false;
	}

	return true;
}

void _soildwrite_close() {
	sw_openfile_str = sw_os_NULL;

	return;
}