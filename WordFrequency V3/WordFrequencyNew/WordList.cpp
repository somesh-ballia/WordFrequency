#include <StdAfx.h>
#include <WordList.h>
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
		exit(1);
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

bool WordList::search(char *word)
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

void WordList::insert(char *word)
{
	word_structure* new_node = allocateMemoryForNewNode();
	if (NULL == start)
	{	
		new_node->count = 1;
		new_node->word = word;
		new_node->next = NULL;
		start = new_node;
	}
	else
	{
		if (!search(word))
		{
			new_node->count = 1;
			new_node->word = word;
			new_node->next = start;
			start = new_node;
		}
	}
}

word_structure* WordList::getWordListStart()
{	
		return start;	
}
