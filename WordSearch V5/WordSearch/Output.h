#pragma once
#include <WordList.h>
#include <PathNameFrequency.h>

class Output
{
public:
	int			PrintOnScreen(WordList* obj_word_list,unsigned __int64* bytes_processed);
	int			PrintToFile(char* output_file_name, WordList* obj_word_list,unsigned __int64* bytes_processed);
	int			PrintFileList(PathNameFrequency* obj_path_name_frequency, int word_count,unsigned __int64* bytes_processed);
};
