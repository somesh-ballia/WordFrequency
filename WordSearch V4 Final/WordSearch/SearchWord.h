#pragma once
#include <WordList.h>
#include <PathNameFrequency.h>

class SearchWord
{
public:

							SearchWord(WordList *object_word_list);
	void					search(char* word, PathNameFrequency* obj_path_name_frequency);

private:

	WordList				*m_obj_word_list;
	void					insert(char *word, word_structure* temp_print,PathNameFrequency* obj_path_name_frequency);
};
