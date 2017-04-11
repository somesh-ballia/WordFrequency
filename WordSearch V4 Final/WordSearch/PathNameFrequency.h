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
	int							insert(char* path);
	path_frequency_structure*	getPathNameFrequencyStart();

private:

	path_frequency_structure*	m_start;
	bool						search(char* path);
	void						incrementCountValue(path_frequency_structure* temp_node);
	int							allocateMemoryForNewNode(path_frequency_structure** new_node);
};	
