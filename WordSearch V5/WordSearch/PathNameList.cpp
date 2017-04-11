#include <StdAfx.h>
#include <PathNameList.h>

PathNameList::PathNameList()
{
	mStart = NULL;
}

PathNameList::~PathNameList()
{
	path_name_structure* temp_node;
	while (NULL != mStart)
	{
		temp_node = mStart;
		mStart = mStart->next;
		temp_node->next = NULL;
		delete temp_node->path_name;
		delete temp_node;
	}
}

int PathNameList::AllocateMemoryForNewNode(path_name_structure **new_node)
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

int PathNameList::Insert(char* path_name,unsigned __int64* bytes_processed)
{
	path_name_structure* new_node;
	if (SUCCESS == AllocateMemoryForNewNode(&new_node))
	{
		new_node->path_name = path_name;
		new_node->next = mStart;
		mStart = new_node;			
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}		 
}

int PathNameList::GetNextPath(char** path_name,unsigned __int64* bytes_processed)
{
	if (NULL != mStart)
	{
		path_name_structure* next_node = mStart->next;
		*path_name = mStart->path_name;
		mStart->next = NULL;
		delete mStart;
		mStart = next_node;
		return SUCCESS;
	}
	else
	{
		*path_name = NULL;
		return FAILURE;
	}
}