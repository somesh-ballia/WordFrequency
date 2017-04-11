#include "StdAfx.h"
#include "DirectoryNameList.h"
#include <stdlib.h>

DirectoryNameList::DirectoryNameList()
{
	start = NULL;
	next_directory_node = start;
}

DirectoryNameList::~DirectoryNameList()
{
	directory_name_structure* temp_node = start;
	while (NULL != start)
	{	
		temp_node = start;
		start = start->next;
		delete temp_node->directory_name;
		delete temp_node;
	}
}

directory_name_structure* DirectoryNameList::allocateMemoryForNewNode()
{
	directory_name_structure* new_node_memory = new directory_name_structure[1];
	if(NULL != new_node_memory)
	{
		return new_node_memory;
	}
	else
	{
		printf("\n Error Allocating memory");
		exit(1);
	}
}

void DirectoryNameList::insert(char *directory_name)
{
	directory_name_structure* new_node = allocateMemoryForNewNode();
	if (NULL == start)
	{
		new_node->directory_name = directory_name;
		new_node->next = NULL;
		start = new_node;
		next_directory_node = start;
	}
	else
	{
		new_node->directory_name = directory_name;
		new_node->next = start;
		start = new_node;
		next_directory_node = start;
	}	
}

char* DirectoryNameList::getNextDirectoryName()
{
	if (NULL != next_directory_node)
	{
		char* directory_name = next_directory_node->directory_name;
		next_directory_node = next_directory_node->next;
		return directory_name;
	}
	else
	{
		return NULL;
	}
}