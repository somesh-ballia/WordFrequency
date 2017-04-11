#pragma once

typedef struct file_path_structure
{	
	char* file_path;	
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
	int					insert(char* word, char* file_path);	
	word_structure*		getWordListStart();

private:

	word_structure*		m_start;
	bool				search(char* word,word_structure* &found_node);
	int					getWordLength(char* word);
	void				incrementCountValue(word_structure* temp_node);
	bool				textMatch(char* first_word, char* second_word);	
	int					allocateMemoryForNewNode(word_structure** new_node);
};