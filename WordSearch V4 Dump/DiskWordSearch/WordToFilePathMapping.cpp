#include <StdAfx.h>
#include <WordToFilePathMapping.h>
#include <stdlib.h>
#include <WordList.h>
#include <cstring>

file_path_structure* WordToFilePathMapping::allocateMemoryForNewNode()
{
	file_path_structure* new_node = new file_path_structure[1];
	if (NULL != new_node)
	{
		return new_node;
	}
	else
	{
		printf("\nError Allocating memory");
		exit(-1);
	}
}

bool WordToFilePathMapping::search(file_path_structure* start, char *file_path)
{
	bool matchSuccess = false;
	file_path_structure* temp_list_node = start;	
	int search_word_length = strlen(file_path);

	while (NULL != temp_list_node)
	{		
		if (search_word_length == strlen(temp_list_node->file_path))
		{
			if (!strcmp(file_path,temp_list_node->file_path))
			{								
				matchSuccess = true;
				break;
			}
		}
		temp_list_node = temp_list_node->next;
	}	
	return matchSuccess;
}

file_path_structure* WordToFilePathMapping::insert(file_path_structure* start, char *file_path)
{
	file_path_structure* new_node = allocateMemoryForNewNode();
	if (NULL == start)
	{
		new_node->file_path = file_path;		
		new_node->next = NULL;
		start = new_node;
	}
	else if (!search(start,file_path))
	{	
		new_node->file_path = file_path;		
		new_node->next = start;
		start = new_node;	
	}
	return start;
}