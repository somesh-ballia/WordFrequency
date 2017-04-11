#pragma once
#include <WordList.h>
#include <PathNameFrequency.h>

class SearchWord
{
public:
							SearchWord(WordList *object_word_list);
	void					Search(char* word, PathNameFrequency* obj_path_name_frequency,unsigned __int64* bytes_processed);

private:
	WordList				*mObjWordList;
	void					Insert(char *word, word_structure* temp_print,PathNameFrequency* obj_path_name_frequency,unsigned __int64* bytes_processed);
};
