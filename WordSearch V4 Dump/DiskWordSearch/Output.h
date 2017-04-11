#pragma once
#include <WordList.h>
#include <PathNameFrequency.h>

class Output
{
public:
	void printOnScreen(WordList* obj_word_list);
	void printToFile(char* output_file_name, WordList* obj_word_list);
	void printFileList(PathNameFrequency* obj_path_name_frequency, int word_count);
};
