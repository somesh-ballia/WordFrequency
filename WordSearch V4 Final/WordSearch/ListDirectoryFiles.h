#pragma once
#include <PathNameList.h>
#include <windows.h>

class ListDirectoryFiles
{
public:

	int			populateFilePathNameList(char* file_path, PathNameList* obj_file_path_name_list);
	int			populateDirectoryPathNameList(char* directory_path,PathNameList* obj_directory_path_name_list);

private:

	int			allocateMemoryForNewWord(char** new_word,int size);
	int			generateCompletePath(char* path,WIN32_FIND_DATA find_data, char** complete_path);
	int			validatePath(char* path);	
};
