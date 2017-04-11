#pragma once
#include <WordList.h>

class WordToFilePathMapping
{
public :	
	int				Insert(file_path_structure** start,char* file_path,unsigned __int64* bytes_processed);

private:	
	int				AllocateMemoryForNewNode(file_path_structure** new_node);
	bool			Search(file_path_structure* start,char* file_path,unsigned __int64* bytes_processed);
};
