#pragma once

typedef struct directory_name_structure
{
	char* directory_name;
	directory_name_structure* next;

} directory_name_structure;

class DirectoryNameList
{
public :
		DirectoryNameList();
		~DirectoryNameList();
		void insert(char* directory_name);
		char* getNextDirectoryName();
private:
		directory_name_structure* start;
		//directory_name_structure* next_directory_node;
		directory_name_structure* allocateMemoryForNewNode();
};
