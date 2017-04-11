#include <StdAfx.h>
#include <FileNameList.h>
#include <stdlib.h>

FileNameList::FileNameList()
{
	start = NULL;
	next_file_node = start;
}

FileNameList::~FileNameList()
{
	file_name_structure* temp_node = start;
	while (NULL != start)
	{
		temp_node = start;
		start = start->next;
		delete temp_node->file_name;		
		delete temp_node;
	}
}

file_name_structure* FileNameList::allocateMemoryForNewNode()
{
	file_name_structure* new_node_memory = new file_name_structure[1];
	if (NULL != new_node_memory)
	{
		return new_node_memory;
	}
	else
	{
		printf("\n Error Allocating memory");
		exit(1);
	}
}

void FileNameList::insert(char *file_name)
{	
	file_name_structure* new_node = allocateMemoryForNewNode();
	if (NULL == start)
	{
		new_node->file_name = file_name;
		new_node->next = NULL;
		start = new_node;
		next_file_node = start;
	}
	else
	{
		new_node->file_name = file_name;
		new_node->next = start;
		start = new_node;
		next_file_node = start;
	}
}

char* FileNameList::getNextFileName()
{
	if (NULL != next_file_node)
	{
		char* file_name = next_file_node->file_name;
		next_file_node = next_file_node->next;
		return file_name;
	}
	else
	{
		return NULL;
	}
}

