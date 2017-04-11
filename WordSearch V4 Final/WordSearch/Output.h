#pragma once
#include <WordList.h>
#include <PathNameFrequency.h>

class Output
{
public:
	int			printOnScreen(WordList* obj_word_list);
	int			printToFile(char* output_file_name, WordList* obj_word_list);
	int			printFileList(PathNameFrequency* obj_path_name_frequency, int word_count);
};
