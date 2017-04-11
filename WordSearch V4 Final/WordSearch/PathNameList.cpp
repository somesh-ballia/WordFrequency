#include <StdAfx.h>
#include <PathNameList.h>

PathNameList::PathNameList()
{
	m_start = NULL;
}

PathNameList::~PathNameList()
{
	path_name_structure* temp_node;
	while (NULL != m_start)
	{
		temp_node = m_start;
		m_start = m_start->next;
		temp_node->next = NULL;
		delete temp_node->path_name;
		delete temp_node;
	}
}

int PathNameList::allocateMemoryForNewNode(path_name_structure **new_node)
{
	*new_node = new path_name_structure;
	if (NULL != new_node)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

int PathNameList::insert(char* path_name)
{
	path_name_structure* new_node;
	if (SUCCESS == allocateMemoryForNewNode(&new_node))
	{
		new_node->path_name = path_name;
		new_node->next = m_start;
		m_start = new_node;	
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}		 
}

int PathNameList::getNextPath(char** path_name)
{
	if (NULL != m_start)
	{
		path_name_structure* next_node = m_start->next;
		*path_name = m_start->path_name;
		m_start->next = NULL;
		delete m_start;
		m_start = next_node;
		return SUCCESS;
	}
	else
	{
		*path_name = NULL;
		return FAILURE;
	}
}