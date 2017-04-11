#pragma once
#include <PathNameList.h>
#include <windows.h>

class ListDirectoryFiles
{
public:
	int			PopulateFilePathNameList(char* file_path, PathNameList* obj_file_path_name_list,unsigned __int64* bytes_processed);
	int			PopulateDirectoryPathNameList(char* directory_path,PathNameList* obj_directory_path_name_list,unsigned __int64* bytes_processed);

private:
	int			AllocateMemoryForNewWord(char** new_word,int size);
	int			GenerateCompletePath(char* path,WIN32_FIND_DATA find_data, char** complete_path,unsigned __int64* bytes_processed);
	int			ValidatePath(char* path,unsigned __int64* bytes_processed);	
};
