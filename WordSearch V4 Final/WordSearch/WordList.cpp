#include <StdAfx.h>
#include <WordList.h>
#include <WordToFilePathMapping.h>

WordList::WordList()
{
	m_start = NULL;	
}

word_structure* WordList::getWordListStart()
{	
		return m_start;	
}

WordList::~WordList()
{
	word_structure* temp_node;	
	while (NULL != m_start)
	{
		temp_node = m_start;
		file_path_structure* file_temp;
		while (NULL != temp_node->file_path_start)
		{
			file_temp = temp_node->file_path_start;
			temp_node->file_path_start = temp_node->file_path_start->next;
			file_temp->next = NULL;
			if (NULL != *(file_temp->file_path))
			{
				delete file_temp->file_path;
				*file_temp->file_path = NULL;
			}
			delete file_temp;
		}
		m_start = m_start->next;		
		delete temp_node->word;
		delete temp_node;
	}
}

int WordList::allocateMemoryForNewNode(word_structure** new_node)
{
	*new_node = new word_structure;
	if (NULL != *new_node)
	{
		return SUCCESS;
	}
	else
	{
		*new_node = NULL;
		return FAILURE;
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
	word_structure* temp_list_node = m_start;	
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

int WordList::insert(char* word,char* file_path)
{
	WordToFilePathMapping* obj_word_to_file_path_mapping = new WordToFilePathMapping();
	word_structure* new_node = NULL;
	word_structure* found_node = NULL;
	
	if (SUCCESS == allocateMemoryForNewNode(&new_node))
	{
		// found node returns the node which has the word we have searched
		if (!search(word,found_node))
		{	
			new_node->count = 1;
			new_node->word = word;
			new_node->next = m_start;		
			new_node->file_path_start = NULL;	
			m_start = new_node;				
			if (FAILURE == obj_word_to_file_path_mapping->insert(&m_start->file_path_start,file_path))
			{
				return FAILURE;
			}
		}
		else
		{			
			if (FAILURE ==  obj_word_to_file_path_mapping->insert(&found_node->file_path_start,file_path))
			{
				return FAILURE;
			}
		}
		return SUCCESS;
	}
	else
	{
		return SUCCESS;
	}		
}

