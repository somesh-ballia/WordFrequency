#pragma once
typedef struct path_name_structure
{
	char* path_name;
	path_name_structure* next;

} path_name_structure;

class PathNameList
{
public:

							PathNameList();
							~PathNameList();
	int						insert(char* path_name);
	int						getNextPath(char** path_name);

protected:

	path_name_structure*	m_start;

private:

	int						allocateMemoryForNewNode(path_name_structure** new_node);	
};
