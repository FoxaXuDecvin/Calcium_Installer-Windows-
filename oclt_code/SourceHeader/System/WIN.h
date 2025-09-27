#pragma once
#include<Windows.h> 
#include<direct.h>
#include <fstream>
#include <io.h>
#include <string>
#include <vector>
#include<ShlObj.h>

const string Win32_kernel = "Win32";
const string Linux_kernel = "Linux";
string _windows_userprofile = getenv("userprofile");
const string _Build_Path = _windows_userprofile + "/.OpenCppLangTab";

char* stringtochar;
char* StringToCharX(string tomessage) {

	const int len = tomessage.length();

	stringtochar = new char[len + 1];

	strcpy(stringtochar, tomessage.c_str());

	return stringtochar;
}

//Design For Windows
const std::string pathsign = "\\";
string RunPlatfom = "Windows (MSVC 64Bit)";//Must Include Windows/Linux one
string _Run_SysKernel = Win32_kernel;
//Linux s   Windows  ms
//Default Use s
void sleepapi(int num) {
	int cutth = num * 1000;
	Sleep(cutth);
	return;
}

void cleanConsole() {
	system("cls");
}

void foldercreateapi(string dir) {
	_mkdir(dir.c_str());
}

bool check_file_existenceA(const std::string& filename) {
	std::ifstream file(filename);
	if (file.is_open()) {
		return true;
	}
	else {
		return false;
	}
}
//NET CORE

//Use Windows API  <URLMON.DLL>
#include<urlmon.h>
#pragma comment(lib,"URlmon.lib")
using namespace std;
LPCWSTR stringToLPCWSTR(string orig)
{
	size_t origsize = orig.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* wcstring = new wchar_t[sizeof(wchar_t) * (orig.length() - 1)];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	return wcstring;
}

//0-FAILED
//1-TRUE
bool URLDown(string URL, string Save) {
	remove(Save.c_str());

	LPCWSTR LcDsp = stringToLPCWSTR(Save);
	LPCWSTR LcURL = stringToLPCWSTR(URL);
	HRESULT applydownload = URLDownloadToFileW(
		nullptr,
		LcURL,
		LcDsp,
		0,
		nullptr
	);
	if (check_file_existenceA(Save)) {
		return true;
	}
	else {
		return false;
	}
	
}

//GetFilePath
// Resource File
string GetFilePath(void) {
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	/*
	strrchr:函数功能：查找一个字符c在另一个字符串str中末次出现的位置（也就是从str的右侧开始查找字符c首次出现的位置），
	并返回这个位置的地址。如果未能找到指定字符，那么函数将返回NULL。
	使用这个地址返回从最后一个字符c到str末尾的字符串。
	*/
	(strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串//
	string path = szFilePath;
	return path;
}

string GetFileName(void) {
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	/*
	strrchr:函数功能：查找一个字符c在另一个字符串str中末次出现的位置（也就是从str的右侧开始查找字符c首次出现的位置），
	并返回这个位置的地址。如果未能找到指定字符，那么函数将返回NULL。
	使用这个地址返回从最后一个字符c到str末尾的字符串。
	*/
	string path = szFilePath;
	return path;
}

void removeDirectoryAPIX(string dir) {
	//在目录后面加上"\\*.*"进行第一次搜索
	string newDir = dir + "\\*.*";
	//用于查找的句柄
	intptr_t handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1) {
		//cout << "无文件" << endl;
		return;
	}

	do
	{
		if (fileinfo.attrib & _A_SUBDIR) {//如果为文件夹，加上文件夹路径，再次遍历
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			newDir = dir + "\\" + fileinfo.name;
			removeDirectoryAPIX(newDir.c_str());//先遍历删除文件夹下的文件，再删除空的文件夹
			//cout << newDir.c_str() << endl;
			if (_rmdir(newDir.c_str()) == 0) {//删除空文件夹
				//cout << "delete empty dir success" << endl;
			}
			else {
				//cout << "delete empty dir error" << endl;
			}
		}
		else {
			string file_path = dir + "\\" + fileinfo.name;
			//cout << file_path.c_str() << endl;
			if (remove(file_path.c_str()) == 0) {//删除文件
				//cout << "delete file success" << endl;
			}
			else {
				//cout << "delete file error" << endl;
			}
		}
	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);

	_rmdir(dir.c_str());
	return;
}

string Process_cache;
void _fileapi_write(string _fa_file, string _fa_info);
string p1_filepath = GetFilePath();
void CreateFileMap_txt(string savefile,string dir) {
	//在目录后面加上"\\*.*"进行第一次搜索
	string newDir = dir + "\\*.*";
	//用于查找的句柄
	intptr_t handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1) {
		//cout << "无文件" << endl;
		return;
	}

	do
	{
		if (fileinfo.attrib & _A_SUBDIR) {//如果为文件夹，加上文件夹路径，再次遍历
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			newDir = dir + "\\" + fileinfo.name;
			CreateFileMap_txt(savefile,newDir);//先遍历删除文件夹下的文件，再删除空的文件夹
		}
		else {
			string file_path = dir + "\\" + fileinfo.name;
			Process_cache = file_path;
			Process_cache = ReplaceChar(Process_cache, p1_filepath, "");
			//cout << file_path.c_str() << endl;
			_fileapi_write(savefile, ReplaceChar(Process_cache, "\\", "/"));
		}
	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);

	return;
}
void CreateDirMap_txt(string savefile, string dir) {
	//在目录后面加上"\\*.*"进行第一次搜索
	string newDir = dir + "\\*.*";
	//用于查找的句柄
	intptr_t handle;
	struct _finddata_t fileinfo;
	//第一次查找
	handle = _findfirst(newDir.c_str(), &fileinfo);

	if (handle == -1) {
		//cout << "无文件" << endl;
		return;
	}

	do
	{
		if (fileinfo.attrib & _A_SUBDIR) {//如果为文件夹，加上文件夹路径，再次遍历
			if (strcmp(fileinfo.name, ".") == 0 || strcmp(fileinfo.name, "..") == 0)
				continue;

			// 在目录后面加上"\\"和搜索到的目录名进行下一次搜索
			newDir = dir + "\\" + fileinfo.name;
			//CreateFileMap_txt(savefile, newDir);//先遍历删除文件夹下的文件，再删除空的文件夹
			_fileapi_write(savefile, ReplaceChar(newDir, "\\", "/") + "/");
		}
		else {
			string file_path = dir + "\\" + fileinfo.name;
			Process_cache = file_path;
			Process_cache = ReplaceChar(Process_cache, p1_filepath, "");
			//cout << file_path.c_str() << endl;
			_fileapi_write(savefile, ReplaceChar(Process_cache, "\\", "/"));
		}
	} while (!_findnext(handle, &fileinfo));

	_findclose(handle);

	return;
}


char *envbuffer;
string _SystemAPI_getenv(string Environment) {
	envbuffer = getenv(Environment.c_str());
	if (envbuffer == NULL) {
		return "Null.SystemAPI.getenv --> NullEnv";
	}
	return envbuffer;
}

bool _Execute_Admin(string File, string Args) {
	return ShellExecute(0, "runas", File.c_str(), Args.c_str(), 0, SW_SHOW);
}

void sleepapi_ms(int secondsNum) {
	Sleep(secondsNum);
	return;
}