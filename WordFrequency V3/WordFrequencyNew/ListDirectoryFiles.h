#pragma once
#include <FileNameList.h>
#include <DirectoryNameList.h>

class ListDirectoryFiles
{
public:	
	int populateFileNameList(char* directory_name, FileNameList* obj_file_name_list);
	int populateDirectoryNameList(char* directory_name, DirectoryNameList* obj_directory_name_list);
private:
	 char* allocateMemoryForNewWord(int size);	
};
