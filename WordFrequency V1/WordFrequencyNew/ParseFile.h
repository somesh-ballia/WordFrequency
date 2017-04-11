#pragma once
#include "WordList.h"

class ParseFile
{
public:
	bool parse(char* file_address,WordList* obj_word_list);
private:
	char* getWord(FILE *read_file,int word_length);
	bool validateFileAddress(char* file_address);
	bool validSaperator(char character);	
	char* allocateMemory(int size);

};
