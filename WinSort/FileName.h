#pragma once
#include <tchar.h>
#include <string>

class FileName
{
public:
	FileName(const wchar_t *file_name,bool isFolder);
	~FileName();
	
	bool operator<(const FileName &rhs);

	void printFileName();

	std::string getFileName();

private:
	const wchar_t *fileName;
	bool isFolder;
};

