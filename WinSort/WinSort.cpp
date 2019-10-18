// WinSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include<cctype>
//#include <cstring>
#include <algorithm>
#include "FileName.h"
#include <vector>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include <iostream>
#include "utils.h"


#include <string>
#include <io.h>

wchar_t* CharToWchar_New(const char *str) {
	int nLen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	if (nLen == 0) {
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen + 1];
	ZeroMemory(pResult, nLen + 1);
	MultiByteToWideChar(CP_ACP, 0, str, -1, pResult, nLen);
	return pResult;
}

bool compareFileName(FileName *left, FileName *right) {
	return *left < *right;
}


void dir(std::string path,std::vector<std::string>& filename)
{
	long long hFile = 0;
	struct _finddata_t fileInfo;
	std::string pathName, exdName;
	// \\* 代表要遍历所有的类型,如改成\\*.jpg表示遍历jpg类型文件
	if ((hFile = _findfirst(pathName.assign(path).append("\\*").c_str(), &fileInfo)) == -1) {
		return;
	}
	do
	{
		//判断文件的属性是文件夹还是文件
		if (fileInfo.attrib&_A_SUBDIR)
		{

		}
		else
		{
			filename.push_back(fileInfo.name);
		}

		//std::cout << fileInfo.name << (fileInfo.attrib&_A_SUBDIR ? "[folder]" : "[file]") << std::endl;
	} while (_findnext(hFile, &fileInfo) == 0);
	_findclose(hFile);
	return;
}

void sortName(std::vector<std::string>&src, std::vector<std::string>&target)
{
	std::vector<FileName*> fileList = {};

	for (uint32_t i = 0; i < src.size(); i++)
	{
		wchar_t* filename = CharToWchar_New(src[i].c_str());
		FileName* file = new FileName(filename, false);
		fileList.push_back(file);
	}

	printf("%d\n", fileList.size());

	std::sort(fileList.begin(), fileList.end(), compareFileName);
	printf("after sort================= %d\n", fileList.size());

	for (FileName *file : fileList) {
		//(*file).printFileName();
		target.push_back((*file).getFileName());
	}

}

int main() 
{
	while (1)
	{
		std::string srcpath = "";
		std::string despach = "";
		std::cout << "需要改名目录名字: " << std::endl;
		std::cin >> srcpath;
		std::cout << "输入参考目录名字: " << std::endl;
		std::cin >> despach;

		std::vector<std::string> filename1;
		dir(srcpath, filename1);
		std::vector<std::string> filename2;
		dir(despach, filename2);

		if (filename1.size() != filename2.size())
		{
			std::cout << "文件数量不匹配" << std::endl;
			system("pause");
			return 0;
		}

		std::vector<std::string> filename3;
		sortName(filename1, filename3);

		std::vector<std::string> filename4;
		sortName(filename2, filename4);

		uint32_t alllen = filename3.size();
		for (uint32_t i = 0; i < alllen; i++)
		{
			std::cout << filename3[i] << " 替换为 " << filename4[i] << std::endl;


			std::string srcname = srcpath + "\\" + filename3[i];
			std::string srcname2 = srcpath + "\\" + filename4[i];

			if (rename(srcname.c_str(), srcname2.c_str()) != 0)
			{
				std::cout << "替换失败" << srcname << " : " << srcname2 << std::endl;
				system("pause");
				return 0;
			}
		}

		std::cout << "替换完成 数量 : " << alllen << std::endl;

	}

	return 0;
}

