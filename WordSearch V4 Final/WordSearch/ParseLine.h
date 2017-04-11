#pragma once
#include <PathNameList.h>

class ParseLine : public PathNameList
{
public:

	int						parse(char* line,int* number_of_words);
	int						getNextWord(char** word);

private:

	int						allocateMemoryForNewWord(char** new_word,int size);
	int						getNewWord(char* line,int start_offset,int end_offset,char** word);
	bool					isValidSaperator(char character);	
};
