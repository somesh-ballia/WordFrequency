#include <StdAfx.h>
#include <WordToFilePathMapping.h>

int WordToFilePathMapping::AllocateMemoryForNewNode(file_path_structure** new_node)
{
	*new_node = new file_path_structure;
	if (NULL != new_node)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

bool WordToFilePathMapping::Search(file_path_structure* start, char *file_path,unsigned __int64* bytes_processed)
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
				temp_list_node->count += 1;
				matchSuccess = true;
				break;
			}
		}
		temp_list_node = temp_list_node->next;
	}	
	return matchSuccess;
}

int WordToFilePathMapping::Insert(file_path_structure** start, char *file_path,unsigned __int64* bytes_processed)
{
	file_path_structure* new_node;
	if (SUCCESS == AllocateMemoryForNewNode(&new_node))
	{
		if (!Search(*start,file_path,bytes_processed))
		{	
			new_node->file_path = file_path;
			new_node->count = 1;
			new_node->next = *start;
			*start = new_node;	
		}		
		return SUCCESS;
	}
	else
	{		
		return FAILURE;
	}	
}