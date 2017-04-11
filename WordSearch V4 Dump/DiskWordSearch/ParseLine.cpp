#include <StdAfx.h>
#include <stdlib.h>
#include <ParseLine.h>

ParseLine::ParseLine()
{
	start = NULL;
	next_word_node = start;
}

ParseLine::~ParseLine()
{
	line_structure* temp_node = start;
	while (NULL != start)
	{
		temp_node = start;
		start = start->next;
		temp_node->next = NULL;
		delete temp_node->word;
		delete temp_node;
	}
}

line_structure* ParseLine::allocateMemoryForNewNode()
{
	line_structure* new_node = new line_structure[1];
	if (NULL != new_node)
	{
		return new_node;
	}
	else
	{
		printf("\nUnable to allocate memory");
		exit(-1);
	}
}

char* ParseLine::allocateMemoryForNewWord(int size)
{
	char* new_node = new char[size];
	if (NULL != new_node)
	{
		return new_node;
	}
	else
	{
		printf("\nUnable to allocate memory");
		exit(-1);
	}
}

void ParseLine::insert(char* word)
{
	line_structure* new_node = allocateMemoryForNewNode();
	if (NULL == start)
	{
		new_node->word = word;
		new_node->next = NULL;
		start = new_node;
		next_word_node = start;
	}
	else
	{
		new_node->word= word;
		new_node->next = start;
		start = new_node;
		next_word_node = start;
	}
}

char* ParseLine::getNextWord()
{
	if (NULL != next_word_node)
	{
		char* word = next_word_node->word;
		next_word_node = next_word_node->next;
		return word;
	}
	else
	{
		return NULL;
	}
}

int ParseLine::parse(char *line)
{
	int start_offset = 0;
	int end_offset = 0;
	char* word = NULL;
	char character = *line;
	int counter_word = 0;
	int word_length = 0;
	int number_of_words = 0;
	while ('\0' != character)
	{
		character = line[counter_word]; counter_word++;
		while (isValidSaperator(character))
		{
			character = line[counter_word]; counter_word++;
		}
		start_offset = counter_word-1;
		while (!isValidSaperator(character))
		{
			character = line[counter_word]; counter_word++;
		}	
		end_offset = counter_word-1;
		word = getWord(line,start_offset,end_offset);
		insert(word);
		number_of_words++;			
	}
	return number_of_words;
}

char* ParseLine::getWord(char* line,int start_offset,int end_offset)
{	
	int index = 0;
	int length = end_offset-start_offset+1;
	char* new_word = allocateMemoryForNewWord(length);
	for (int counter = start_offset; counter < end_offset; counter++)
	{
		new_word[index] = line[counter];
		index++;
	}
	new_word[index] = '\0';
	return new_word;
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