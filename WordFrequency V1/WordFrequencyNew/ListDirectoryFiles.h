#pragma once
#include "FileNameList.h"

class ListDirectoryFiles
{
public:
	int populateFileNameList(char* directory_name, FileNameList* obj_file_name_list);
private:
	 char* allocateMemoryForNewWord(int size);
	
};
