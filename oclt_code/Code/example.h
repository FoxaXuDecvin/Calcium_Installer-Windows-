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
	InstallSource = "DirectSetup";
	CreateVerFolder = true;
	//End
	return true;
}

//Args API
bool lengetargs, tgversionget,insourcget;
string CDAVersion;
void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	if (args$api == "--path") {

		lengetargs = true;
		return;
	}
	if (args$api == "--target-version") {

		tgversionget = true;
		return;
	}

	if (args$api == "--nsf") {
		CreateVerFolder = false;
		return;
	}

	if (args$api == "--install-source") {
		insourcget = true;
		return;
	}

	if (lengetargs == true) {
		WorkDirectory = args$api;
		lengetargs = false;
		return;
	}

	if (insourcget == true) {
		InstallSource = args$api;
		insourcget = false;
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
string TempURL,OriginURL,CodeVersion,DirectFile;
string TempUserType,PreDefaultWD;
string ServerA, ServerB, ServerC;
int _HeadMainLoad() {
	//main
	_fileapi_del(SystemTemp + "/fxserver_versionlist.txt");
	_fileapi_del(SystemTemp + "/fxserver_connecttest.txt");
	CDAVersion = "1.0.6";
	PreDefaultWD = _SystemAPI_getenv("userprofile") + "/OpenCalcium";

	_p("Deploy Program Version :  " + CDAVersion + "       Installer Source :  " + InstallSource);
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
		return -2;
	}

	_p("Connecting Server...");
	if (!_urldown_api_vc_nocache("http://githubimage.foxaxu.com/connecttest.txt", SystemTemp + "/fxserver_connecttest.txt")) {
		_p("Failed to connect server . URL :   http://githubimage.foxaxu.com/connecttest.txt");
		_pause();
		return -2;
	}

	//Download PROFILE
	_p("Downloading Cache file...");
	if (!_urldown_api_vc_nocache("http://githubimage.foxaxu.com/cda-api/download_api_windows.txt", SystemTemp + "/fxserver_versionlist.txt")) {
		_p("Failed to download files . URL :   http://githubimage.foxaxu.com/cda-api/download_api_windows.txt");
		_pause();
		return -2;
	}

	_p("Searching request version");
	if (!check_file_existence(SystemTemp + "/fxserver_versionlist.txt")) {
		_p("Error : Local Security Software may blocked CDA Access version list files");
		_p("version list files is lost");
		_pause();
		return 3;
	}
	ServerA = _load_sipcfg(SystemTemp + "/fxserver_versionlist.txt", "MainServer");
	ServerB = _load_sipcfg(SystemTemp + "/fxserver_versionlist.txt", "SecondServer");
	ServerC = _load_sipcfg(SystemTemp + "/fxserver_versionlist.txt", "fallbackServer");
	//Latest
	if (TargetVersion == "latest") {
		//Get Latest
		CodeVersion = _load_sipcfg(SystemTemp + "/fxserver_versionlist.txt", "latest");
		OriginURL = _load_sipcfg(SystemTemp + "/fxserver_versionlist.txt", CodeVersion);

	}
	else {
		CodeVersion = TargetVersion;
		OriginURL = _load_sipcfg(SystemTemp + "/fxserver_versionlist.txt", CodeVersion);
		if (OriginURL == "") {
			_p("Error : Your request version is not found");
			_pause();
			return 3;
		}

	}
	//Download Start
	_p("target version  " + CodeVersion + "    URL :  " + OriginURL);

	//Startdownload
	if (CreateVerFolder) {
		DirectFile = WorkDirectory + "/" + CodeVersion + "/Calcium.exe";
	}
	else {
		DirectFile = WorkDirectory + "/Calcium.exe";
	}
	_dapi_create_full_path(DirectFile);
	if (check_file_existence(DirectFile)) {
		_p("Error :  This file is existing on select directory");
		_pause();
		return -3;
	}

	//URL Maker

	TempURL = ReplaceChar(OriginURL, "{DomainServer}", ServerA);
	_p("Downloading ...  " + TempURL);
	if (!_urldown_api_vc_nocache(TempURL, DirectFile)) {
		_p("Failed to download files . URL :   " + TempURL);
		TempURL = ReplaceChar(OriginURL, "{DomainServer}", ServerB);
		_p("Use Second Server   Downloading ...  " + TempURL);

	    if (!_urldown_api_vc_nocache(TempURL, DirectFile)) {
			_p("Failed to download files . URL :   " + TempURL);
			TempURL = ReplaceChar(OriginURL, "{DomainServer}", ServerC);
			_p("Use Fallback Server   Downloading ...  " + TempURL);

			if (!_urldown_api_vc_nocache(TempURL, DirectFile)) {
				_p("Failed to download files . URL :   " + TempURL);
				_p("All Server target failed");
				_pause();
				return -2;
			}
		}
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