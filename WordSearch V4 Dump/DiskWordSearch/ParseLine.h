#pragma once

typedef struct line_structure
{
	char* word;
	line_structure* next;
} line_structure;

class ParseLine
{
public:
	ParseLine();
	~ParseLine();	
	char* getNextWord();
	int parse(char* line);
private:
	line_structure* start;
	line_structure* next_word_node;
	line_structure* allocateMemoryForNewNode();
	char* allocateMemoryForNewWord(int size);
	bool isValidSaperator(char character);
	void insert(char* word);
	char* getWord(char* line,int start_offset,int end_offset);

};
