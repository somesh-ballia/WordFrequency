#include <StdAfx.h>
#include <WordList.h>
#include <WordToFilePathMapping.h>

WordList::WordList()
{
	mStart = NULL;	
}

word_structure* WordList::GetWordListStart()
{	
		return mStart;	
}

WordList::~WordList()
{
	word_structure* temp_node;	
	while (NULL != mStart)
	{
		temp_node = mStart;
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
		mStart = mStart->next;		
		delete temp_node->word;
		delete temp_node;
	}
}

int WordList::AllocateMemoryForNewNode(word_structure** new_node)
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

int WordList::GetWordLength(char* word,unsigned __int64* bytes_processed)
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

bool WordList::TextMatch(char* first_word,char* second_word,unsigned __int64* bytes_processed)
{
	bool match_flag = false;	
	if (GetWordLength(first_word,bytes_processed) == GetWordLength(second_word,bytes_processed))
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

void WordList::IncrementCountValue(word_structure* list_node,unsigned __int64* bytes_processed)
{
	list_node->count++;
}

bool WordList::Search(char *word, word_structure* &found_node,unsigned __int64* bytes_processed)
{
	bool matchSuccess = false;
	word_structure* temp_list_node = mStart;	
	int search_word_length = GetWordLength(word,bytes_processed);

	while (NULL != temp_list_node)
	{		
		if (search_word_length == GetWordLength(temp_list_node->word,bytes_processed))
		{
			if (TextMatch(word,temp_list_node->word,bytes_processed))
			{
				IncrementCountValue(temp_list_node,bytes_processed);
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

int WordList::Insert(char* word,char* file_path,unsigned __int64* bytes_processed)
{
	WordToFilePathMapping* obj_word_to_file_path_mapping = new WordToFilePathMapping();
	word_structure* new_node = NULL;
	word_structure* found_node = NULL;
	
	if (SUCCESS == AllocateMemoryForNewNode(&new_node))
	{		
		if (!Search(word,found_node,bytes_processed))
		{	
			new_node->count = 1;
			new_node->word = word;
			new_node->next = mStart;		
			new_node->file_path_start = NULL;	
			mStart = new_node;		
			// inserting path of file contaning that word in the node
			if (FAILURE == obj_word_to_file_path_mapping->Insert(&mStart->file_path_start,file_path,bytes_processed))
			{
				return FAILURE;
			}
		}
		else
		{			
			if (FAILURE ==  obj_word_to_file_path_mapping->Insert(&found_node->file_path_start,file_path,bytes_processed))
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

