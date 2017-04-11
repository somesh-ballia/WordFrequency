#include "StdAfx.h"
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <conio.h>
#include <direct.h>
#include <windows.h>
#include "ListDirectoryFiles.h"
#include "DirectoryNameList.h"
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

char* ListDirectoryFiles::allocateMemoryForNewWord(int size)
{
	char* new_word_memory = new char[size];
	if(NULL != new_word_memory)
	{
		return new_word_memory;
	}
	else
	{
		printf("\n Error Allocating memory");
		exit(1);
	}
}

int ListDirectoryFiles::populateFileNameList(char* directory_name, FileNameList *obj_file_name_list)
{
	int error_code;
	HANDLE h_find;
	WIN32_FIND_DATA find_data;	
	
	if(_chdir(directory_name))
	{
		printf("\nDirectory not found");
		return FAILURE;
	}

	h_find = FindFirstFile("*.txt",&find_data);

	if(INVALID_HANDLE_VALUE == h_find)
	{
		error_code = GetLastError();
		if(ERROR_FILE_NOT_FOUND == error_code)
		{
			printf("\nNo files with extention .txt");			
			return FAILURE;
		}	
	}	
	else
	{
		do
		{		
			char* complete_file_path;
			int directory_path_length = strlen(directory_name)+1;
			int complete_file_path_length = directory_path_length+strlen(find_data.cFileName)+1;
			char* ptr_last_slash_location = strrchr(directory_name,'/');
			int last_slash_location = ptr_last_slash_location - directory_name +1;

			// generating complete path name of file
			if((directory_path_length-1) != last_slash_location)
			{	
				// if the directory path dont have / at the end
				complete_file_path_length++;
				complete_file_path = allocateMemoryForNewWord(complete_file_path_length);
				strcpy(complete_file_path,directory_name);
				strncat(complete_file_path,"/",1);
				strncat(complete_file_path,find_data.cFileName,strlen(find_data.cFileName));
			}
			else
			{
				// if the directory path already has / at the end
				complete_file_path = allocateMemoryForNewWord(complete_file_path_length);
				strcpy(complete_file_path,directory_name);
				strncat(complete_file_path,find_data.cFileName,strlen(find_data.cFileName));
			}				
			//printf("\n%s",complete_file_path);
			obj_file_name_list->insert(complete_file_path);
		}
		while(0 != FindNextFile(h_find,&find_data));

		error_code = GetLastError();
		if(error_code != ERROR_NO_MORE_FILES)
		{
			printf("\nTraversal of path %s is complete");
		}

	}
	return 1;
}