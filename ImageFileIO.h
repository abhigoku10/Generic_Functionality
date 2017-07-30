
#pragma once

#include "Headers.h"
#include <tchar.h>
#include <strsafe.h>
#include <Shlwapi.h>
#include <string>
#include <io.h>
#include <cstring>

class FileIO
{

public:

	static int GetAllFilesInFolder(std::string folderName,
		std::string fileNames);

	static int GetAllFilesInFolder(std::string folderName,
		std::vector<std::string>& fileNames,
		bool isFullPathRequired = true
		);

	static int GetImageFilesInFolder(std::string folderName,
		std::vector<std::string>& fileNames,
		bool isFullPathRequired = true
		);
	static bool ValidDirectory(const string& dirName_in);

	static bool FindSubDirectories(char* pcDirectory,
		vector<string>& v_strDirectory,
		vector<string>& v_strFolderNames
		);

	static void FilterImagesFiles(std::vector<std::string>& input, std::vector<std::string>& output);

private:

	static void GetFullPath(std::string folderName, std::vector<std::string>& fileNames);
};