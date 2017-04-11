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
	int						Insert(char* path_name,unsigned __int64* bytes_processed);
	int						GetNextPath(char** path_name,unsigned __int64* bytes_processed);

protected:
	path_name_structure*	mStart;

private:
	int						AllocateMemoryForNewNode(path_name_structure** new_node);	
};
