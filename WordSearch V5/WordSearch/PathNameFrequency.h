#pragma once

typedef struct path_frequency_structure
{
	char* path;
	int count;
	path_frequency_structure* next;

} path_frequency_structure;

class PathNameFrequency
{
public: 
								PathNameFrequency();
								~PathNameFrequency();
	int							Insert(char* path,unsigned __int64* bytes_processed);
	path_frequency_structure*	GetPathNameFrequencyStart();

private:
	path_frequency_structure*	mStart;
	bool						Search(char* path,unsigned __int64* bytes_processed);
	void						IncrementCountValue(path_frequency_structure* temp_node,unsigned __int64* bytes_processed);
	int							AllocateMemoryForNewNode(path_frequency_structure** new_node);
};	
