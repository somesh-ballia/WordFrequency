#include <StdAfx.h>
#include <SearchWord.h>

SearchWord::SearchWord(WordList *object_word_list)
{
	mObjWordList = object_word_list;
}

void SearchWord::Search(char *word,PathNameFrequency* obj_path_name_frequency,unsigned __int64* bytes_processed)
{
	bool word_found = false;
	word_structure* temp_search = mObjWordList->GetWordListStart();
	while (NULL != temp_search)
	{
		if (!strcmp(word,temp_search->word))
		{
			word_found = true;			
			Insert(word,temp_search,obj_path_name_frequency,bytes_processed);
			break;
		}
		temp_search = temp_search->next;
	}
	if (!word_found)
	{
		printf("\nOOPS! %s not present in any file",word);
	}
}

void SearchWord::Insert(char *word, word_structure* temp_search,PathNameFrequency* obj_path_name_frequency,unsigned __int64* bytes_processed)
{
	file_path_structure* temp_print = temp_search->file_path_start;
	while(NULL != temp_print)
	{
		obj_path_name_frequency->Insert(temp_print->file_path,bytes_processed);		
		temp_print= temp_print->next;
	}
}