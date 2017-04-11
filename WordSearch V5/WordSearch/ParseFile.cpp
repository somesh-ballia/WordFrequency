#include <StdAfx.h>
#include <ParseFile.h>

int ParseFile::AllocateMemoryForNewWord(char** new_word,int size)
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

int ParseFile::Parse(char* file_address, WordList* obj_word_list ,unsigned __int64* bytes_processed)
{
	*bytes_processed = 0;
	int line_number = 0;
	if (ValidateFileAddress(file_address,bytes_processed))
	{
		int word_length = 0;		
		char character;
		char* word;
		FILE *read_fp = fopen(file_address,"r");
		FILE *previous_read_fp = fopen(file_address,"r");		
		while (!feof(read_fp))
		{
			(*bytes_processed)++;
			character = getc(read_fp);		
			word_length++;
			if (ValidSaperator(character,bytes_processed))
			{
				if (word_length > 1)
				{
					if (SUCCESS == GetWord(previous_read_fp,word_length,&word,bytes_processed))
					{
						if (FAILURE == obj_word_list->Insert(word,file_address,bytes_processed))
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

int ParseFile::GetWord(FILE *prev_read_fp, int word_length, char** new_word,unsigned __int64* bytes_processed)
{
	int counter = 0;	
	char* word;
	if (SUCCESS == AllocateMemoryForNewWord(&word,word_length))
	{
		char character = getc(prev_read_fp);	
		while (ValidSaperator(character,bytes_processed))
		{
			character = getc(prev_read_fp);	
		}
		while (!ValidSaperator(character,bytes_processed))
		{
			while (ValidSaperator(character,bytes_processed))
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

bool ParseFile::ValidateFileAddress(char* file_address,unsigned __int64* bytes_processed)
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

bool ParseFile::ValidSaperator(char character,unsigned __int64* bytes_processed)
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
		case '.':	
					valid_flag = true;
					break;
		case '\n':	
					valid_flag = true;
					break;
		case '\t':	
					valid_flag = true;
					break;
		case '?':	
					valid_flag = true;
					break;
		case '!':	
					valid_flag = true;
					break;
		case '\"':	
					valid_flag = true;
					break;
		case '\'':	
					valid_flag = true;
					break;
		case '\/':	
					valid_flag = true;
					break;
		case '\\':	
					valid_flag = true;
					break;
		case '(':	
					valid_flag = true;
					break;
		case ')':	
					valid_flag = true;
					break;
		case '{':	
					valid_flag = true;
					break;
		case '}':	
					valid_flag = true;
					break;
		case '[':	
					valid_flag = true;
					break;
		case ']':	
					valid_flag = true;
					break;
		case '<':	
					valid_flag = true;
					break;		
		case '~':	
					valid_flag = true;
					break;
		case '@':	
					valid_flag = true;
					break;
		case '#':	
					valid_flag = true;
					break;
		case '$':	
					valid_flag = true;
					break;
		case '%':	
					valid_flag = true;
					break;
		case '^':	
					valid_flag = true;
					break;
		case '&':	
					valid_flag = true;
					break;
		case EOF:	
					valid_flag = true;
					break;					
		default : 
					valid_flag = false;
					break;
	}
	return valid_flag;
}
