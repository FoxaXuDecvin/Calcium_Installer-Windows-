//Base Engine
//Simple File config Engine
//Copyright FoxaXu 2024

#include"../shload.h"
#define _CRT_SECURE_NO_WARNINGS
string tempreadbuffEr_;

//Design On Calcium Project
string tempptr, readcacheA;
int readptr_glo = 0;

string _load_sipcfg(string _sc_File, string _sc_ID) {
	int readptr = 0;
	if (check_file_existenceA(_sc_File)) {
		while (true) {
			readptr++;
			tempptr = _fileapi_textread(_sc_File, readptr);
			if (tempptr == "") {
				continue;
			}
			if (tempptr == "ReadFailed") {
				cout << "Failed to Load Simple Config" << endl;
				cout << "Open File Failed :  " << _sc_File << endl;
				break;
			}
			if (tempptr == "overline") {
				_sh_throw_error("Load Simple Config Error :  Unknown Config :  Not Found  --(" + _sc_ID + ")--  On File :    _" + _sc_File + "_");
				return "";
			}
			readcacheA = _api_PartRead(tempptr, "$", "=");

			//cout << "Read Up :  Line " << readptr << "   INFO :  _" << tempptr << "_" << endl;

			if (readcacheA == _sc_ID) {
				return _api_PartRead(tempptr, "=", ";");
			}

			if (tempptr == "")break;

			continue;
		}
		return "";
	}
	else {
		_sh_throw_error("Load Simple Config Error :  File Not Found   _" + _sc_File + "_");
		return "";
	}
}

string _load_sipcfg_noreturn(string _sc_File, string _sc_ID) {
	if (check_file_existenceA(_sc_File)) {
		while (true) {
			readptr_glo++;
			tempptr = _fileapi_textread(_sc_File, readptr_glo);
			if (tempptr == "") {
				continue;
			}
			if (tempptr == "ReadFailed") {
				cout << "Failed to Load Simple Config" << endl;
				cout << "Open File Failed :  " << _sc_File << endl;
				break;
			}
			if (tempptr == "overline") {
				_sh_throw_error("Load Simple Config Error :  Unknown Config :  Not Found  --(" + _sc_ID + ")--  On File :    _" + _sc_File + "_");
				return "";
			}
			readcacheA = _api_PartRead(tempptr, "$", "=");

			//cout << "Read Up :  Line " << readptr << "   INFO :  _" << tempptr << "_" << endl;

			if (readcacheA == _sc_ID) {
				return _api_PartRead(tempptr, "=", ";");
			}

			if (tempptr == "")break;

			continue;
		}
		return "";
	}
	else {
		_sh_throw_error("Load Simple Config Error :  File Not Found   _" + _sc_File + "_");
		return "";
	}
}

void _sipcfg_reset(void) {
	readptr_glo = 0;
	return;
}

bool _sw_target_remove;
bool _spcfg_wiriteapi(string _sc_File, int _sc_Line, string _sc_header, string _sc_winfo) {
	//Simple Config Write
	_sw_target_remove = false;
	//Create New File

	string _scnew_file = "sipcfg_newtemp-" + _get_random_s(1, 99999);


	int n_readptr_ = 1;
	while (true) {
		//File Write
		if (n_readptr_ == _sc_Line) {
			//ReCreate Config
			if (_sc_winfo != "@target_sipcfg_remove") {
				_fileapi_write(_scnew_file, "$" + _sc_header + "=" + _sc_winfo + ";");
				_sw_target_remove = false;
			}
			else {
				_sw_target_remove = true;
			}
			n_readptr_++;
			continue;
		}

		tempreadbuffEr_ = _fileapi_textread(_sc_File, n_readptr_);

		if (tempreadbuffEr_ == "overline") {
			break;
		}

		_fileapi_write(_scnew_file, tempreadbuffEr_);

		n_readptr_++;
		continue;
	}

	remove(_sc_File.c_str());
	CopyFile(_scnew_file.c_str(), _sc_File.c_str(), 0);
	remove(_scnew_file.c_str());

	if (_sw_target_remove == false) {
		if (_load_sipcfg(_sc_File, _sc_header) == _sc_winfo) {
			return true;
		}
		else {
			_sh_throw_error("Process Config Failed...");
			return false;
		}
	}
	else {
		_sw_target_remove = false;
	}

	return false;
}

bool _write_sipcfg(string _sc_File, string _sc_ID, string _sc_writeINFO) {
	string readbufferA;
	int readptr = 0;
	if (check_file_existenceA(_sc_File)) {
		while (true) {
			readptr++;
			string tempptr = _fileapi_textread(_sc_File, readptr);
			if (tempptr == "") {
				continue;
			}
			if (tempptr == "ReadFailed") {
				cout << "Failed to Write Simple Config" << endl;
				cout << "Open File Failed :  " << _sc_File << endl;
				break;
			}
			if (tempptr == "overline") {
				//WriteNewConfig
				return _spcfg_wiriteapi(_sc_File, readptr, _sc_ID, _sc_writeINFO);
			}
			readbufferA = _api_PartRead(tempptr, "$", "=");

			//cout << "Read Up :  Line " << readptr << "   INFO :  _" << tempptr << "_" << endl;

			if (readbufferA == _sc_ID) {
				return _spcfg_wiriteapi(_sc_File, readptr, _sc_ID, _sc_writeINFO);
			}

			if (tempptr == "")break;

			continue;
		}
		return "";
	}
	else {
		_sh_throw_error("Write Simple Config Error :  File Not Found   _" + _sc_File + "_");
		return "";
	}
}

//New Remove API
string rs_buf;
bool _remove_sipcfg(string _sc_File, string _sc_ID) {
	string readbufferA;
	int readptr = 0;
	if (check_file_existenceA(_sc_File)) {
		while (true) {
			readptr++;
			string tempptr = _fileapi_textread(_sc_File, readptr);
			if (tempptr == "") {
				continue;
			}
			if (tempptr == "ReadFailed") {
				cout << "Failed to Write Simple Config" << endl;
				cout << "Open File Failed :  " << _sc_File << endl;
				break;
			}
			if (tempptr == "overline") {
				//WriteNewConfig
				return _spcfg_wiriteapi(_sc_File, readptr, _sc_ID, "@target_sipcfg_remove");
			}
			readbufferA = _api_PartRead(tempptr, "$", "=");

			//cout << "Read Up :  Line " << readptr << "   INFO :  _" << tempptr << "_" << endl;

			if (readbufferA == _sc_ID) {
				return _spcfg_wiriteapi(_sc_File, readptr, _sc_ID, "@target_sipcfg_remove");
			}

			if (tempptr == "")break;

			continue;
		}
		return "";
	}
	else {
		_sh_throw_error("Write Simple Config Error :  File Not Found   _" + _sc_File + "_");
		return "";
	}
}
