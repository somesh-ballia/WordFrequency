#pragma once
#include <WordList.h>

class ParseFile
{
public:

	int			parse(char* file_address,WordList* obj_word_list);

private:

	int			getWord(FILE *read_file,int word_length ,char** new_word);
	bool		validateFileAddress(char* file_address);
	bool		validSaperator(char character);	
	int			allocateMemoryForNewWord(char** new_word,int size);

};
