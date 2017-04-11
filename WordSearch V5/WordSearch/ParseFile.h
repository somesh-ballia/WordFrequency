#pragma once
#include <WordList.h>

class ParseFile
{
public:
	int			Parse(char* file_address,WordList* obj_word_list,unsigned __int64* bytes_processed);

private:
	int			GetWord(FILE *read_file,int word_length ,char** new_word,unsigned __int64* bytes_processed);
	bool		ValidateFileAddress(char* file_address,unsigned __int64* bytes_processed);
	bool		ValidSaperator(char character,unsigned __int64* bytes_processed);	
	int			AllocateMemoryForNewWord(char** new_word,int size);

};
