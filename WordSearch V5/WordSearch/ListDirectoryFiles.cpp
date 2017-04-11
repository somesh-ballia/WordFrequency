#include <StdAfx.h>
#include <cstring>
#include <iostream>
#include <direct.h>
#include <ListDirectoryFiles.h>

int ListDirectoryFiles::AllocateMemoryForNewWord(char **new_word, int size)
{
	*new_word = new char[size];
	if (NULL != *new_word)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

int ListDirectoryFiles::ValidatePath(char *path,unsigned __int64* bytes_processed)
{
	*bytes_processed += strlen(path);

	if(_chdir(path))
	{
		switch(errno)
		{		
		case EACCES:
			printf("\nAccess to %s is denied",path);
			break;

		case ENOENT:
			printf("\n%s : No such directory found",path);
			break;

		case EINVAL:
			printf("\n%s : Invalid path found",path);
			break;

		default:
			printf("\nDirectory not found");
			break;
		}
		return FAILURE;
	}
	else
	{
		return SUCCESS;
	}
}

int ListDirectoryFiles::GenerateCompletePath(char *path, WIN32_FIND_DATA find_data, char** complete_path,unsigned __int64* bytes_processed)
{	
	int path_length = strlen(path)+1;

	//find_data.ftCreationTime;
	int complete_path_length = path_length+strlen(find_data.cFileName)+1;
	char* ptr_last_slash_location = strrchr(path,'/');
	int last_slash_location = ptr_last_slash_location - path +1;
	
	// Computing data processed
	*bytes_processed += complete_path_length;

	// generating complete path name of file
	if ((path_length-1) != last_slash_location)
	{	
		// if the directory path dont have / at the end
		complete_path_length++;
		if (SUCCESS == AllocateMemoryForNewWord(complete_path,complete_path_length))
		{
			strcpy(*complete_path,path);
			strncat(*complete_path,"/",1);
			strncat(*complete_path,find_data.cFileName,strlen(find_data.cFileName));	
			// Computing data processed
			*bytes_processed += complete_path_length;
		}
		else
		{
			return FAILURE;
		}		
	}
	else
	{
		// if the directory path already has / at the end
		if (SUCCESS == AllocateMemoryForNewWord(complete_path,complete_path_length))
		{
			strcpy(*complete_path,path);
			strncat(*complete_path,find_data.cFileName,strlen(find_data.cFileName));
		}
		else
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}

int ListDirectoryFiles::PopulateDirectoryPathNameList(char* directory_path, PathNameList *obj_directory_path_name_list,unsigned __int64* bytes_processed)
{
	int error_code;
	HANDLE h_find;
	WIN32_FIND_DATA find_data;
	
	// used to avoid . and .. of windows file system
	int reference_counter = 0;
	
	if (FAILURE == ValidatePath(directory_path,bytes_processed))
	{
		return FAILURE;
	}
	
	h_find = FindFirstFile("*",&find_data);
	
	if (INVALID_HANDLE_VALUE == h_find)
	{
		error_code = GetLastError();
		if (ERROR_FILE_NOT_FOUND == error_code)
		{ 					
			return FAILURE;
		}	
	}
	else
	{
		do
		{
			if (find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (reference_counter > 1)
				{
					char* complete_path = NULL;

					if (SUCCESS == GenerateCompletePath(directory_path,find_data,&complete_path,bytes_processed))
					{
						if (FAILURE == obj_directory_path_name_list->Insert(complete_path,bytes_processed))
						{
							return FAILURE;
						}						
					}
				}
				reference_counter++;
			}
		}
		while (0 != FindNextFile(h_find,&find_data));
		
		error_code = GetLastError();
		if (ERROR_NO_MORE_FILES != error_code)
		{
			printf("\nTraversal of path %s is complete",*directory_path);
		}
	}	
	return SUCCESS;
}

int ListDirectoryFiles::PopulateFilePathNameList(char* file_path, PathNameList *obj_file_path_name_list,unsigned __int64* bytes_processed)
{
	int error_code;
	HANDLE h_find;
	WIN32_FIND_DATA find_data;
	
	if (FAILURE == ValidatePath(file_path,bytes_processed))
	{
		return FAILURE;
	}
	
	h_find = FindFirstFile("*.txt",&find_data);
	
	if (INVALID_HANDLE_VALUE == h_find)
	{
		error_code = GetLastError();
		if (ERROR_FILE_NOT_FOUND == error_code)
		{ 					
			return FAILURE;
		}	
	}
	else
	{
		do
		{
			char* complete_path = NULL;
			if (SUCCESS == GenerateCompletePath(file_path,find_data,&complete_path,bytes_processed))
			{
				if (FAILURE == obj_file_path_name_list->Insert(complete_path,bytes_processed))
				{
					return FAILURE;					 
				}				
			}
		}
		while (0 != FindNextFile(h_find,&find_data));		
	}	
	return SUCCESS;
}
