#pragma once
#include <WordList.h>

class WordToFilePathMapping
{
public :	
	file_path_structure* insert(file_path_structure* start,char* file_path);
private:
	//file_path_structure* start;
	file_path_structure* allocateMemoryForNewNode();
	bool search(file_path_structure* start,char* file_path);
};
