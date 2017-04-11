#include <StdAfx.h>
#include <cstring>
#include <PathNameFrequency.h>

PathNameFrequency::PathNameFrequency()
{
	mStart = NULL;
}

PathNameFrequency::~PathNameFrequency()
{
	path_frequency_structure* temp_node;
	while (NULL != mStart)
	{
		temp_node = mStart;
		mStart = mStart->next;
		temp_node->next = NULL;
		delete temp_node->path;
		delete temp_node;
	}
}

int PathNameFrequency::AllocateMemoryForNewNode(path_frequency_structure** new_node)
{
	*new_node = new path_frequency_structure;
	if (*new_node != NULL)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

void PathNameFrequency::IncrementCountValue(path_frequency_structure* temp_node,unsigned __int64* bytes_processed)
{
	temp_node->count++;
}

bool PathNameFrequency::Search(char *path,unsigned __int64* bytes_processed)
{
	bool matchSuccess = false;
	path_frequency_structure* temp_node = mStart;	
	int search_word_length = strlen(path);

	while (NULL != temp_node)
	{		
		if (search_word_length == strlen(temp_node->path))
		{
			if (!strcmp(path,temp_node->path))
			{
				IncrementCountValue(temp_node,bytes_processed);				
				matchSuccess = true;
				break;
			}
		}
		temp_node = temp_node->next;
	}	
	return matchSuccess;
}

int PathNameFrequency::Insert(char* path,unsigned __int64* bytes_processed)
{
	path_frequency_structure* new_node = NULL;

	if (SUCCESS == AllocateMemoryForNewNode(&new_node))
	{
		if (!Search(path,bytes_processed))
		{	
			new_node->count = 1;
			new_node->path = path;
			new_node->next = mStart;				
			mStart = new_node;			
		}	
	}
	else
	{
		return FAILURE;
	}
}

path_frequency_structure* PathNameFrequency::GetPathNameFrequencyStart()
{
	return mStart;
}