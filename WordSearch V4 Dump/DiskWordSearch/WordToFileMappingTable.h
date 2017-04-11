#pragma once

typedef struct word_file_map_structure
{
	int word_id;
	int line_number;
	char* file_path;
	word_file_map_structure* next;

} word_file_map_structure;

class WordToFileMappingTable
{
public:
	WordToFileMappingTable();
	~WordToFileMappingTable();
	void insert(int word_id,int line_number,char* file_path);
private:

};
