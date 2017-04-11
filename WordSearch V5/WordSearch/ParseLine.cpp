#include <StdAfx.h>
#include <ParseLine.h>

int ParseLine::AllocateMemoryForNewWord(char** new_word,int size)
{
	*new_word = new char[size];
	if (NULL != *new_word)
	{
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

int ParseLine::Parse(char* line,int* number_of_words,unsigned __int64* bytes_processed)
{
	int start_offset = 0;
	int end_offset = 0;
	char* word = NULL;
	char character = NULL;
	int counter_word = 0;
	int word_length = 0;
	*number_of_words = 0;
	character = line[0];
	int line_length = strlen(line);
	while ('\0' != character)
	{
		character = line[counter_word]; 
		counter_word++;
		while (IsValidSaperator(character,bytes_processed))
		{
			character = line[counter_word]; 
			counter_word++;
		}
		start_offset = counter_word-1;
		while (!IsValidSaperator(character,bytes_processed))
		{	
			character = line[counter_word]; 
			counter_word++;			
		}	
		end_offset = counter_word-1;
		if (SUCCESS == GetNewWord(line,start_offset,end_offset,&word,bytes_processed))
		{
			Insert(word,bytes_processed);
			(*number_of_words)++;
		}
		else
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}

int ParseLine::GetNewWord(char* line,int start_offset, int end_offset, char** word,unsigned __int64* bytes_processed)
{
	int index = 0;
	char* new_word;
	int length = end_offset-start_offset+1;
	if (SUCCESS == AllocateMemoryForNewWord(&new_word,length))
	{
		for (int counter = start_offset; counter < end_offset; counter++)
		{
			new_word[index] = line[counter];
			index++;
		}
		new_word[index] = '\0';
		*word = new_word;
	}
	else
	{
		return FAILURE;
	}
	return SUCCESS;	
}

int ParseLine::GetNextWord(char** word,unsigned __int64* bytes_processed)
{
	if (NULL != mStart)
	{
		path_name_structure* next_node = mStart->next;
		*word = mStart->path_name;
		mStart->next = NULL;
		delete mStart;
		mStart = next_node;
		return SUCCESS;
	}
	else
	{
		*word = NULL;
		return FAILURE;
	}
}

bool ParseLine::IsValidSaperator(char character,unsigned __int64* bytes_processed)
{
	bool valid_flag = true;
	switch (character)
	{
				
		case ' ':	
					valid_flag = true;
					break;
		case ',':	
					valid_flag = true;
					break;
		case ';':	
					valid_flag = true;
					break;
		case ':':	
					valid_flag = true;
					break;		
		case '\0':	
					valid_flag = true;
					break;					
		default : 
					valid_flag = false;
					break;
	}
	return valid_flag;
}