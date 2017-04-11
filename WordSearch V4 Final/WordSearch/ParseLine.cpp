#include <StdAfx.h>
#include <ParseLine.h>

int ParseLine::allocateMemoryForNewWord(char** new_word,int size)
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

int ParseLine::parse(char* line,int* number_of_words)
{
	int start_offset = 0;
	int end_offset = 0;
	char* word = NULL;
	char character = NULL;
	int counter_word = 0;
	int word_length = 0;
	*number_of_words = 0;
	character = line[0];
	while ('\0' != character)
	{
		character = line[counter_word]; 
		counter_word++;
		while (isValidSaperator(character))
		{
			character = line[counter_word]; 
			counter_word++;
		}
		start_offset = counter_word-1;
		while (!isValidSaperator(character))
		{
			character = line[counter_word]; 
			counter_word++;
		}	
		end_offset = counter_word-1;
		if (SUCCESS == getNewWord(line,start_offset,end_offset,&word))
		{
			insert(word);
			(*number_of_words)++;
		}
		else
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}

int ParseLine::getNewWord(char* line,int start_offset, int end_offset, char** word)
{
	int index = 0;
	char* new_word;
	int length = end_offset-start_offset+1;
	if (SUCCESS == allocateMemoryForNewWord(&new_word,length))
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

int ParseLine::getNextWord(char** word)
{
	if (NULL != m_start)
	{
		path_name_structure* next_node = m_start->next;
		*word = m_start->path_name;
		m_start->next = NULL;
		delete m_start;
		m_start = next_node;
		return SUCCESS;
	}
	else
	{
		*word = NULL;
		return FAILURE;
	}
}

bool ParseLine::isValidSaperator(char character)
{
	bool validFlag = true;
	switch (character)
	{
				
		case ' ':	
					validFlag = true;
					break;
		case ',':	
					validFlag = true;
					break;
		case ';':	
					validFlag = true;
					break;
		case ':':	
					validFlag = true;
					break;		
		case '\0':	
					validFlag = true;
					break;					
		default : 
					validFlag = false;
					break;
	}
	return validFlag;
}