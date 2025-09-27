//Everything is Possible
//On OpenCppLangTab
//Code on _HeadMainLoad() 

#pragma once

#include"../shload.h"
#define _CRT_SECURE_NO_WARNINGS

bool PreLaunchLoad(void) {
	//Put Preload code here
	//
	WorkDirectory = "No Parameter";
	TargetVersion = "Default";
	CreateVerFolder = true;
	//End
	return true;
}

//Args API
bool lengetargs, tgversionget;
string CDAVersion;
void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	if (args$api == "--path") {
		_prtoutmsg("Argument = " + args$api);
		lengetargs = true;
		return;
	}
	if (args$api == "--target-version") {
		_prtoutmsg("Argument = " + args$api);
		tgversionget = true;
		return;
	}

	if (args$api == "--nsf") {
		CreateVerFolder = false;
		return;
	}

	if (lengetargs == true) {
		WorkDirectory = args$api;
		lengetargs = false;
		return;
	}

	if (tgversionget == true) {
		TargetVersion = args$api;
		tgversionget = false;
		return;
	}

	_prtoutmsg("Unknown Args :  " + args$api);
	return;
}

//Put Code Here
string SystemTemp;
string TempURL,CodeVersion,DirectFile;
string TempUserType,PreDefaultWD;
int _HeadMainLoad() {
	//main
	CDAVersion = "1.0.3";
	PreDefaultWD = _SystemAPI_getenv("userprofile") + "/OpenCalcium";

	_p("Deploy Program Version :   " + CDAVersion);
	if (WorkDirectory == "No Parameter") {
		if (TargetVersion == "Default") {
			_p("Calcium Deployment Application");
			_p("No Parameters. Please set your own settings");
			_p("");
			_p("Default Directory :   " + PreDefaultWD);
			_prtoutmsg("Select Deploy Directory>");
			TempUserType = _getline_type();
			if (TempUserType != "") {
				WorkDirectory = TempUserType;
			}
			_p("");
			_p("Default Select :   Latest");
			_prtoutmsg("Type you own version>");
			TempUserType = _getline_type();
			if (TempUserType != "") {
				TargetVersion = TempUserType;
			}
			_p("");
			_p("Default Select :   y");
			_prtoutmsg("Create Version Folder ?  (y/n)>");
			TempUserType = _getline_type();
			if (TempUserType == "n") {
				CreateVerFolder = false;
				_p ("false");
			}
			if (TempUserType == "N") {
				CreateVerFolder = false;
				_p("false");
			}
		}
	}
	if (WorkDirectory == "No Parameter")WorkDirectory = PreDefaultWD;
	if (TargetVersion == "Default")TargetVersion = "latest";
	SystemTemp = _SystemAPI_getenv("temp");

	_dapi_create_full_path(WorkDirectory + "/CheckExist");
	if (!_dapi_ExistFolder_check(WorkDirectory)) {
		_p("Error. failed to create directory");
		_p("Dir :   " + WorkDirectory);
		_pause();
		return 0;
	}

	_p("Connecting Server...");
	if (!_urldown_api_vc_nocache("http://githubimage.foxaxu.com/connecttest.txt", SystemTemp + "/fxserver_connecttest.txt")) {
		_p("Failed to connect server . URL :   http://githubimage.foxaxu.com/connecttest.txt");
		_pause();
		return 0;
	}

	//Download PROFILE
	_p("Downloading Cache file...");
	if (!_urldown_api_vc_nocache("http://githubimage.foxaxu.com/cda-api/version.txt", SystemTemp + "/fxserver_versionlist.txt")) {
		_p("Failed to download files . URL :   http://githubimage.foxaxu.com/cda-api/version.txt");
		_pause();
		return 0;
	}

	_p("Searching request version");
	//Latest
	if (TargetVersion == "latest") {
		//Get Latest
		CodeVersion = _load_sipcfg(SystemTemp + "/fxserver_versionlist.txt", "latest");
		TempURL = _load_sipcfg(SystemTemp + "/fxserver_versionlist.txt", CodeVersion);
	}
	else {
		CodeVersion = TargetVersion;
		TempURL = _load_sipcfg(SystemTemp + "/fxserver_versionlist.txt", CodeVersion);
		if (TempURL == "") {
			_p("Error : Your request version is not found");
			_pause();
			return 0;
		}
	}
	//Download Start
	_p("target version  " + CodeVersion + "    URL :  " + TempURL);

	//Startdownload
	if (CreateVerFolder) {
		DirectFile = WorkDirectory + "/" + CodeVersion + "/Calcium.exe";
	}
	else {
		DirectFile = WorkDirectory + "/Calcium.exe";
	}
	_dapi_create_full_path(DirectFile);

	_p("Downloading ...  " + TempURL);
	if (!_urldown_api_vc_nocache(TempURL, DirectFile)) {
		_p("Failed to download files . URL :   " + TempURL);
		_pause();
		return 0;
	}

	_p("");
	_p("Complete Deploy Calcium");
	_p("File Deploy on :  " + DirectFile);
	_fileapi_del(SystemTemp + "/fxserver_versionlist.txt");
	_fileapi_del(SystemTemp + "/fxserver_connecttest.txt");
	_p("Press Enter to Close This applicaton");
	_pause();
	return 0;
}