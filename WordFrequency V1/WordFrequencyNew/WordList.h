#pragma once
typedef struct word_structure
{
	char* word;
	int count;	
	word_structure* next;

} word_structure;

class WordList
{
public:
	WordList();
	~WordList();
	void insert(char* word);	
	word_structure* getWordListStart();

private:
	word_structure* start;
	bool search(char* word);
	int getWordLength(char* word);
	void incrementCountValue(word_structure* temp_node);
	bool textMatch(char* first_word, char* second_word);	
	word_structure* allocateMemoryForNewNode();
};