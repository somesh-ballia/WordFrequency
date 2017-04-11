#include "StdAfx.h"
#include "ParseFile.h"
#include "WordList.h"
#include <stdlib.h>

#define SUCCESS true
#define FAILURE false


char* ParseFile::allocateMemory(int size)
{
	char* new_word = new char[size];
	if (NULL != new_word)
	{
		return new_word;
	}
	else
	{
		printf("\n Error Allocating memory");
		exit(1);
	}
}

bool ParseFile::parse(char* file_address, WordList* obj_word_list)
{
	if (validateFileAddress(file_address))
	{
		int word_length = 0;		
		char character;
		char* word;
		FILE *read_fp = fopen(file_address,"r");
		FILE *previous_read_fp = fopen(file_address,"r");
		
		while (!feof(read_fp))
		{
			character = getc(read_fp);			
			word_length++;
			if (validSaperator(character))
			{
				if (word_length > 1)
				{
					word = getWord(previous_read_fp,word_length);
					obj_word_list->insert(word);					
				}
				word_length = 0;
			}			
		}		
		fclose(read_fp);
		fclose(previous_read_fp);
		return SUCCESS;
	}
	else
	{
		printf("\n %s not fosund",file_address);
		return FAILURE;
	}
	
}

char* ParseFile::getWord(FILE *prev_read_fp, int word_length)
{
	int counter = 0;
	char* new_word = allocateMemory(word_length);
	char character = getc(prev_read_fp);	
	while (validSaperator(character))
	{
		character = getc(prev_read_fp);	
	}
	while (!validSaperator(character))
	{
		while (validSaperator(character))
		{
			character = getc(prev_read_fp);	
		}
		new_word[counter] = character;
		character = getc(prev_read_fp);
		counter++;
	}
	new_word[counter] = '\0';
	//printf(":%s",new_word);
	return new_word;
}


bool ParseFile::validateFileAddress(char* file_address)
{
	FILE *file = fopen(file_address,"r");
	if (NULL != file)
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}

bool ParseFile::validSaperator(char character)
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
		case '.':	
					validFlag = true;
					break;
		case '\n':	
					validFlag = true;
					break;
		case '\t':	
					validFlag = true;
					break;
		case '?':	
					validFlag = true;
					break;
		case '!':	
					validFlag = true;
					break;
		case '\"':	
					validFlag = true;
					break;
		case '\'':	
					validFlag = true;
					break;
		case '\/':	
					validFlag = true;
					break;
		case '\\':	
					validFlag = true;
					break;
		case '(':	
					validFlag = true;
					break;
		case ')':	
					validFlag = true;
					break;
		case '{':	
					validFlag = true;
					break;
		case '}':	
					validFlag = true;
					break;
		case '[':	
					validFlag = true;
					break;
		case ']':	
					validFlag = true;
					break;
		case '<':	
					validFlag = true;
					break;
		case '>':	
					validFlag = true;
					break;
		case EOF:	
					validFlag = true;
					break;
					
		default : 
					validFlag = false;
					break;
	}
	return validFlag;
}
