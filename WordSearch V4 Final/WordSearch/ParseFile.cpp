#include <StdAfx.h>
#include <ParseFile.h>

int ParseFile::allocateMemoryForNewWord(char** new_word,int size)
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

int ParseFile::parse(char* file_address, WordList* obj_word_list)
{
	int line_number = 0;
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
					if (SUCCESS == getWord(previous_read_fp,word_length,&word))
					{
						if (FAILURE == obj_word_list->insert(word,file_address))
						{
							printf("\nError in inserting %s from %s",word,file_address);
						}
					}					
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
		printf("\n %s not found",file_address);
		return FAILURE;
	}
}

int ParseFile::getWord(FILE *prev_read_fp, int word_length, char** new_word)
{
	int counter = 0;	
	char* word;
	if (SUCCESS == allocateMemoryForNewWord(&word,word_length))
	{
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
		word[counter] = character;
		character = getc(prev_read_fp);
		counter++;
	}
	word[counter] = '\0';	
	*new_word = word;
	return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
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
		case '~':	
					validFlag = true;
					break;
		case '@':	
					validFlag = true;
					break;
		case '#':	
					validFlag = true;
					break;
		case '$':	
					validFlag = true;
					break;
		case '%':	
					validFlag = true;
					break;
		case '^':	
					validFlag = true;
					break;
		case '&':	
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
