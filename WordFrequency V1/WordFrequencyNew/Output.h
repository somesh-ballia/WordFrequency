#pragma once
#include "WordList.h"

class Output
{
public:
	void printOnScreen(WordList* obj_word_list);
	void printToFile(char* output_file_name, WordList* obj_word_list);
};
