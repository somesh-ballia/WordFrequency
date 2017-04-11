#pragma once

typedef struct file_name_structure
{
	char* file_name;
	file_name_structure* next;

}file_name_structure;

class FileNameList
{
public:
	FileNameList();
	~FileNameList();
	void insert(char* file_name);
	char* getNextFileName();

private:
	file_name_structure* start;	
	file_name_structure* next_file_node;
	file_name_structure* allocateMemoryForNewNode();	
};
