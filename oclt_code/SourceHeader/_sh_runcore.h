//Run Core

#pragma once
#include "../SourceHeader/include.h"
#define _CRT_SECURE_NO_WARNINGS
//Define
string PartReadA(string Info, string StartMark, string EndMark, int RPartSizeA);

string araBuffer;
string $quomark = "\"";
string $sqmark = "\'";

//Run any program in any system
//    _system_autoRun("C:\Windows\Notepad.exe","Example.txt");
//    _system_autoRun("./home/desktop/app.run","example");
int resultCode;
int _system_autoRun(string file, string arguments) {
	if (!check_file_existenceA(file)) return -1001;

	if (_Run_SysKernel == Win32_kernel) {
		file = ReplaceChar(file, "/", "\\");
		araBuffer = $quomark + $quomark + file + $quomark + " " + arguments + $quomark;
		resultCode = system(araBuffer.c_str());
	}

	if (_Run_SysKernel == Linux_kernel) {
		file = ReplaceChar(file, "\\", "/");
		araBuffer = $sqmark + file + $sqmark + " " + arguments;
		resultCode = system(araBuffer.c_str());
	}

	return resultCode;
}
string _sa_makeCache;
int _system_autoRun_A(string file, string arguments,bool SetFileLinuxChmod777) {
	if (!check_file_existenceA(file)) return -1001;

	if (_Run_SysKernel == Win32_kernel) {
		file = ReplaceChar(file, "/", "\\");
		araBuffer = $quomark + $quomark + file + $quomark + " " + arguments + $quomark;
		resultCode = system(araBuffer.c_str());
	}

	if (_Run_SysKernel == Linux_kernel) {
		file = ReplaceChar(file, "\\", "/");
		_sa_makeCache = "chmod 777 " + $sqmark + file + $sqmark;
		if (SetFileLinuxChmod777 == true)system(_sa_makeCache.c_str());
		araBuffer = $sqmark + file + $sqmark + " " + arguments;
		resultCode = system(araBuffer.c_str());
	}

	return resultCode;
}


int _system_autoRun_admin(string file, string arguments) {
	if (!check_file_existenceA(file)) return -1001;

	_Execute_Admin(file, arguments);

	return resultCode;
}


string _get_argslonger(void) {
	return to_string(_argslonger);
}