#include <StdAfx.h>
#include <PathNameFrequency.h>
#include <cstring>
#include <stdlib.h>

PathNameFrequency::PathNameFrequency()
{
	start = NULL;
}

PathNameFrequency::~PathNameFrequency()
{
	path_frequency_structure* temp_node;
	while (NULL != start)
	{
		temp_node = start;
		start = start->next;
		delete temp_node;
	}
}

path_frequency_structure* PathNameFrequency::allocateMemoryForNewNode()
{
	path_frequency_structure* new_node = new path_frequency_structure[1];
	if (NULL != new_node)
	{
		return new_node;
	}
	else
	{
		printf("\nUnable to allocate memory");
		exit(-1);
	}
}

void PathNameFrequency::incrementCountValue(path_frequency_structure* temp_node)
{
	temp_node->count++;
}

bool PathNameFrequency::search(char *path)
{
	bool matchSuccess = false;
	path_frequency_structure* temp_list_node = start;	
	int search_word_length = strlen(path);

	while (NULL != temp_list_node)
	{		
		if (search_word_length == strlen(temp_list_node->path))
		{
			if (!strcmp(path,temp_list_node->path))
			{
				incrementCountValue(temp_list_node);				
				matchSuccess = true;
				break;
			}
		}
		temp_list_node = temp_list_node->next;
	}	
	return matchSuccess;
}

void PathNameFrequency::insert(char* path)
{	
	path_frequency_structure* new_node = allocateMemoryForNewNode();	
	if (NULL == start)
	{			
		new_node->count = 1;
		new_node->path = path;
		new_node->next = NULL;	
		start = new_node;			
	}
	else
	{	
		if (!search(path))
		{	
			new_node->count = 1;
			new_node->path = path;
			new_node->next = start;				
			start = new_node;			
		}		
	}
}

path_frequency_structure* PathNameFrequency::getPathNameFrequencyStart()
{
	return start;
}