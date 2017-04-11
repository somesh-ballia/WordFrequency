#pragma once
#include <WordList.h>

class WordToFilePathMapping
{
public :	
	int insert(file_path_structure** start,char* file_path);
private:	
	int allocateMemoryForNewNode(file_path_structure** new_node);
	bool search(file_path_structure* start,char* file_path);
};
