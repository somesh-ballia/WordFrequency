#pragma once

typedef struct file_path_structure
{	
	char* file_path;	
	int count;
	file_path_structure* next;

} file_path_structure;

typedef struct word_structure
{	
	char* word;
	int count;
	file_path_structure* file_path_start;
	word_structure* next;

} word_structure;

class WordList
{
public:
						WordList();
						~WordList();
	int					Insert(char* word, char* file_path,unsigned __int64* bytes_processed);	
	word_structure*		GetWordListStart();

private:
	word_structure*		mStart;
	bool				Search(char* word,word_structure* &found_node,unsigned __int64* bytes_processed);
	int					GetWordLength(char* word,unsigned __int64* bytes_processed);
	void				IncrementCountValue(word_structure* temp_node,unsigned __int64* bytes_processed);
	bool				TextMatch(char* first_word, char* second_word,unsigned __int64* bytes_processed);	
	int					AllocateMemoryForNewNode(word_structure** new_node);
};