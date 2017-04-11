#pragma once
#include <PathNameList.h>

class ParseLine : public PathNameList
{
public:
	int				Parse(char* line,int* number_of_words,unsigned __int64* bytes_processed);
	int				GetNextWord(char** word,unsigned __int64* bytes_processed);

private:
	int				AllocateMemoryForNewWord(char** new_word,int size);
	int				GetNewWord(char* line,int start_offset,int end_offset,char** word,unsigned __int64* bytes_processed);
	bool			IsValidSaperator(char character,unsigned __int64* bytes_processed);	
};
