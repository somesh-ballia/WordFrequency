#include <StdAfx.h>
#include <WordList.h>
#include <WordToFilePathMapping.h>
#include <stdlib.h>

WordList::WordList()
{
	start = NULL;	
}

WordList::~WordList()
{
	word_structure* temp_node = start;
	while (NULL != start)
	{
		temp_node = start;
		file_path_structure* file_temp;
		while (NULL != temp_node->file_path_start)
		{
			file_temp = temp_node->file_path_start;
			temp_node->file_path_start = temp_node->file_path_start->next;
			delete file_temp->file_path;
			delete file_temp;
		}
		start = start->next;		
		delete temp_node->word;
		delete temp_node;
	}
}

word_structure* WordList::allocateMemoryForNewNode()
{
	word_structure* new_node_memory = new word_structure[1];
	if (NULL != new_node_memory)
	{
		return new_node_memory;
	}
	else
	{
		printf("\n Error Allocating memory");
		exit(-1);
	}
}

int WordList::getWordLength(char* word)
{
	int flag = 0;
	int word_length = 0;
	while ('\0' != *word)
	{		
		word++;
		word_length++;		
	}
	return word_length;
}

bool WordList::textMatch(char* first_word,char* second_word)
{
	bool match_flag = false;	
	if (getWordLength(first_word) == getWordLength(second_word))
	{
		int counter = 0;
		match_flag = true;
		while ('\0' != first_word[counter])
		{
			if (first_word[counter] != second_word[counter])
			{
				match_flag = false;
				break;
			}
			counter++;
		}
	}
	return match_flag;
}

void WordList::incrementCountValue(word_structure* list_node)
{
	list_node->count++;
}

bool WordList::search(char *word, word_structure* &found_node)
{
	bool matchSuccess = false;
	word_structure* temp_list_node = start;	
	int search_word_length = getWordLength(word);

	while (NULL != temp_list_node)
	{		
		if (search_word_length == getWordLength(temp_list_node->word))
		{
			if (textMatch(word,temp_list_node->word))
			{
				incrementCountValue(temp_list_node);
				found_node = temp_list_node;
				matchSuccess = true;
				break;
			}
		}
		temp_list_node = temp_list_node->next;
	}
	if (matchSuccess)
	{
		delete word;
	}
	return matchSuccess;
}

void WordList::insert(char *word,char* file_path)
{
	WordToFilePathMapping* obj_word_to_file_path_mapping = new WordToFilePathMapping();
	word_structure* new_node = allocateMemoryForNewNode();
	word_structure* found_node = NULL;
	if (NULL == start)
	{			
		new_node->count = 1;
		new_node->word = word;
		new_node->next = NULL;
		new_node->file_path_start = NULL;		
		start = new_node;		
		start->file_path_start = obj_word_to_file_path_mapping->insert(start->file_path_start,file_path);		
	}
	else
	{
		// found node returns the node which has the word we have searched
		if (!search(word,found_node))
		{	
			new_node->count = 1;
			new_node->word = word;
			new_node->next = start;		
			new_node->file_path_start = NULL;	
			start = new_node;	
			start->file_path_start = obj_word_to_file_path_mapping->insert(start->file_path_start,file_path);
		}
		else
		{
			found_node->file_path_start = obj_word_to_file_path_mapping->insert(found_node->file_path_start,file_path);
		}
	}	
}

word_structure* WordList::getWordListStart()
{	
		return start;	
}
