#include <StdAfx.h>
#include <cstring>
#include <PathNameFrequency.h>

PathNameFrequency::PathNameFrequency()
{
	m_start = NULL;
}

PathNameFrequency::~PathNameFrequency()
{
	path_frequency_structure* temp_node;
	while (NULL != m_start)
	{
		temp_node = m_start;
		m_start = m_start->next;
		temp_node->next = NULL;
		delete temp_node->path;
		delete temp_node;
	}
}

int PathNameFrequency::allocateMemoryForNewNode(path_frequency_structure** new_node)
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

void PathNameFrequency::incrementCountValue(path_frequency_structure* temp_node)
{
	temp_node->count++;
}

bool PathNameFrequency::search(char *path)
{
	bool matchSuccess = false;
	path_frequency_structure* temp_node = m_start;	
	int search_word_length = strlen(path);

	while (NULL != temp_node)
	{		
		if (search_word_length == strlen(temp_node->path))
		{
			if (!strcmp(path,temp_node->path))
			{
				incrementCountValue(temp_node);				
				matchSuccess = true;
				break;
			}
		}
		temp_node = temp_node->next;
	}	
	return matchSuccess;
}

int PathNameFrequency::insert(char* path)
{
	path_frequency_structure* new_node = NULL;

	if (SUCCESS == allocateMemoryForNewNode(&new_node))
	{
		if (!search(path))
		{	
			new_node->count = 1;
			new_node->path = path;
			new_node->next = m_start;				
			m_start = new_node;			
		}	
	}
	else
	{
		return FAILURE;
	}
}

path_frequency_structure* PathNameFrequency::getPathNameFrequencyStart()
{
	return m_start;
}