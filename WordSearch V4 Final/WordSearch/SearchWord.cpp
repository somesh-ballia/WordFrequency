#include <StdAfx.h>
#include <SearchWord.h>

SearchWord::SearchWord(WordList *object_word_list)
{
	m_obj_word_list = object_word_list;
}

void SearchWord::search(char *word,PathNameFrequency* obj_path_name_frequency)
{
	bool word_found = false;
	word_structure* temp_search = m_obj_word_list->getWordListStart();
	while (NULL != temp_search)
	{
		if (!strcmp(word,temp_search->word))
		{
			word_found = true;			
			insert(word,temp_search,obj_path_name_frequency);
			break;
		}
		temp_search = temp_search->next;
	}
	if (!word_found)
	{
		printf("\nOOPS! %s not present in any file",word);
	}
}

void SearchWord::insert(char *word, word_structure* temp_search,PathNameFrequency* obj_path_name_frequency)
{
	file_path_structure* temp_print = temp_search->file_path_start;
	while(NULL != temp_print)
	{
		obj_path_name_frequency->insert(temp_print->file_path);		
		temp_print= temp_print->next;
	}
}