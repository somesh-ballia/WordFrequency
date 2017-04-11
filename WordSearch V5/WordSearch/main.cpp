#include <stdafx.h>
#include <conio.h>
#include <time.h>
#include <cstring>
#include <direct.h>
#include <PathNameList.h>
#include <ListDirectoryFiles.h>
#include <ParseFile.h>
#include <WordList.h>
#include <SearchWord.h>
#include <Output.h>
#include <ParseLine.h>

#define WORD_TO_SEARCH_SIZE 100
#define RECURSIVE_ACCESS_ENABLED 1
#define RECURSIVE_ACCESS_DISABLED 0
#define SEARCH_ACTIVE 1
#define SEARCH_UNACTIVE 0
#define PRINT_MODE_DISABLED 0
#define PRINT_MODE_SCREEN 1
#define PRINT_MODE_FILE 2
#define FILE_NAME_PRINT_MODE_AND 48 // ascii value of 0

int AllocateMemoryForNewWord(char** new_word,int size)
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

void PrintHelpMessage()
{
	printf("\n\nCOMMAND -i <directory path> [-os] [-of] <file path> [-r] [-s] [-help]");
	printf("\n-i\t: for input directory\n-os\t: for output on screen \n-of\t: for output on a file \n-r\t: for recursive directory access\n");
	printf("-s\t: for searching files by words");
}

int ValidateDirectoryPath(char* directory_path)
{
	if (_chdir(directory_path))
	{
		switch(errno)
		{		
		case EACCES:
			printf("\nAccess to %s is denied",directory_path);
			break;

		case ENOENT:
			printf("\n%s : No such directory found",directory_path);
			break;

		case EINVAL:
			printf("\n%s : Invalid path found",directory_path);
			break;

		default:
			printf("\nDirectory not found");
			break;
		}
		return FAILURE;
	}
	else
	{
		return SUCCESS;
	}
}

int ValidateFilePath(char* file_path)
{
	FILE *write_fp = fopen(file_path,"w");
	if (NULL != write_fp)
	{
		fclose(write_fp);
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

int ValidateCommandLineConstruct(char* input_path, char* output_path, int recursive_directory_access, int print_mode, int search_status)
{		
	if (NULL == input_path)
	{
		printf("\nInput directory path not found");
		PrintHelpMessage();
		return FAILURE;
	}
	if (0 == strlen(input_path))
	{
		printf("\nInput directory path not found");
		PrintHelpMessage();
		return FAILURE;
	}

	// checking if any post processing action is requested
	if (PRINT_MODE_DISABLED == print_mode && SEARCH_UNACTIVE == search_status)
	{
		printf("\nNo post processing action requested");
		PrintHelpMessage();
		return FAILURE;
	}

	if (print_mode == PRINT_MODE_FILE)
	{
		if (NULL == output_path)
		{
			printf("\nOutput file path not found");
			PrintHelpMessage();
			return FAILURE;
		}
		if (0 == strlen(output_path))
		{
			printf("\nOutput file path not found");
			PrintHelpMessage();
			return FAILURE;
		}
	}
	return SUCCESS;
}

int ValidateCommandLineArgument(int argument_number , char* arguments[],char** input_path, char** output_path, int* recursive_directory_access, int* print_mode, int* search_status)
{	
	int argument_counter = 1;
	*input_path = NULL;
	*output_path = NULL;
	*search_status = SEARCH_UNACTIVE;
	*print_mode = PRINT_MODE_DISABLED;

	// By default recursive directory access is disabled
	*recursive_directory_access = RECURSIVE_ACCESS_DISABLED;

	if (argument_number > 1)
	{
		while (NULL != arguments[argument_counter])
		{
			if (!strcmp(arguments[argument_counter],"-i") || !strcmp(arguments[argument_counter],"-I"))
			{
				if (NULL != arguments[argument_counter+1])
				{
					*input_path = arguments[argument_counter+1];
					argument_counter++;
					if (FAILURE == ValidateDirectoryPath(*input_path))
					{
						printf("\nInvalid Path Name");
						PrintHelpMessage();
						return FAILURE;
					}
				}
				else
				{
					printf("\nInvalid Path Name");
					PrintHelpMessage();
					return FAILURE;
				}
			}
			else if (!strcmp(arguments[argument_counter],"-r") || !strcmp(arguments[argument_counter],"-R"))
			{
				*recursive_directory_access = 1;
			}
			else if (!strcmp(arguments[argument_counter],"-OS")|| !strcmp(arguments[argument_counter],"-Os") || !strcmp(arguments[argument_counter],"-oS") || !strcmp(arguments[argument_counter],"-os"))
			{	
				*output_path = NULL;
				*print_mode = PRINT_MODE_SCREEN;
			}
			else if (!strcmp(arguments[argument_counter],"-OF") ||!strcmp(arguments[argument_counter],"-Of") || !strcmp(arguments[argument_counter],"-oF") || !strcmp(arguments[argument_counter],"-of"))
			{
				if (NULL != arguments[argument_counter+1])
				{					
					*print_mode = PRINT_MODE_FILE;					
					*output_path = arguments[argument_counter+1];
					argument_counter++;
					if (FAILURE == ValidateFilePath(*output_path))
					{
						printf("\nInvalid output file name");
						PrintHelpMessage();
						return FAILURE;
					}					
				}
				else
				{
					printf("\nInvalid output file name");
					PrintHelpMessage();
					return FAILURE;
				}
			}
			else if (!strcmp(arguments[argument_counter],"-s") || !strcmp(arguments[argument_counter],"-S"))
			{
				*search_status = SEARCH_ACTIVE;
			}			
			else
			{
				printf("\nUnknown command %s",arguments[argument_counter]);
				return FAILURE;
			}
			argument_counter++;	
		}
	}
	else
	{
		PrintHelpMessage();
		return FAILURE;
	}

	if (FAILURE == ValidateCommandLineConstruct(*input_path,*output_path,*recursive_directory_access,*print_mode,*search_status))
	{
		return FAILURE;
	}
	return SUCCESS;
}

int SearchForFileNames(WordList* obj_word_list,unsigned __int64* bytes_processed)
{	
	char* words_to_search = NULL;
	if (SUCCESS == AllocateMemoryForNewWord(&words_to_search,WORD_TO_SEARCH_SIZE))
	{
		int number_of_words = 0;
		char file_name_print_mode = FILE_NAME_PRINT_MODE_AND;
		SearchWord* obj_search_word = new SearchWord(obj_word_list);
		Output obj_output;
		do
		{
			*words_to_search = NULL;
			PathNameFrequency* obj_path_name_frequency = new PathNameFrequency();	
			ParseLine* obj_parse_line = new ParseLine();	

			printf("\nEnter the Words \n:- ");
			gets(words_to_search);			
			if (SUCCESS == obj_parse_line->Parse(words_to_search,&number_of_words,bytes_processed))
			{
				if (1 < number_of_words)
				{
					printf("\nPress 0 for common files\nPress anything else for all files\n");
					file_name_print_mode = getch();
				}

				char* word = NULL;
				if (SUCCESS == obj_parse_line->GetNextWord(&word,bytes_processed))
				{
						while (NULL != word)
						{
							obj_search_word->Search(word,obj_path_name_frequency,bytes_processed);	
							delete word;
							obj_parse_line->GetNextWord(&word,bytes_processed);
						}
						if (FILE_NAME_PRINT_MODE_AND != file_name_print_mode)
						{
							number_of_words = 1;
						}
						obj_output.PrintFileList(obj_path_name_frequency,number_of_words,bytes_processed);
						printf("\nEnter 1 to exit\n");
				}	
				else
				{
					return FAILURE;
				}
			}
			else
			{
				return FAILURE;
			}
		}
		while('1' != getch());
	}
	else
	{
		return FAILURE;
	}
	return SUCCESS;
}

int main(int argc, char* argv[])
{
	int file_parsed = FAILURE;
	char* input_path;	
	char* output_path;
	int search_status;
	int print_mode;
	int recursive_directory_access;	
	int file_list_populated = FAILURE;

	// to compute number of bytes processed by code
	unsigned __int64 bytes_processed = 0;

	if (SUCCESS == ValidateCommandLineArgument(argc,argv,&input_path,&output_path,&recursive_directory_access,&print_mode,&search_status))
	{
		PathNameList* obj_file_path_name_list = new PathNameList();
		PathNameList* obj_directory_name_list = new PathNameList();
		ListDirectoryFiles* obj_list_directory_files = new ListDirectoryFiles();
		
		// populating the file list with all the file names and directory list with all directory names
		if (SUCCESS == obj_directory_name_list->Insert(input_path,&bytes_processed))
		{
			char* current_path = NULL;
			if (SUCCESS == obj_directory_name_list->GetNextPath(&current_path,&bytes_processed))
			{
				while (NULL != current_path)
				{
					if (RECURSIVE_ACCESS_ENABLED == recursive_directory_access)
					{
						obj_list_directory_files->PopulateDirectoryPathNameList(current_path,obj_directory_name_list,&bytes_processed);					
					}
					if (SUCCESS == obj_list_directory_files->PopulateFilePathNameList(current_path,obj_file_path_name_list,&bytes_processed))
					{						
						file_list_populated = SUCCESS;
					}
					obj_directory_name_list->GetNextPath(&current_path,&bytes_processed);					
				}
			}			
			if (SUCCESS == file_list_populated) 
			{
				// Parsing all the required files and populating the word list
				ParseFile obj_parse_file;
				WordList* obj_word_list = new WordList();
				current_path = NULL;
				
				// take start time stamp
				time_t time_start = time(NULL);
			
				if (SUCCESS == obj_file_path_name_list->GetNextPath(&current_path,&bytes_processed))
				{
					while (NULL != current_path)
					{
						if (SUCCESS == obj_parse_file.Parse(current_path,obj_word_list,&bytes_processed))
						{							
							printf("\nFile Parsed : %s",current_path);
							file_parsed = SUCCESS;
						}			
						obj_file_path_name_list->GetNextPath(&current_path,&bytes_processed);
					}
					// take end time stamp
					time_t time_end = time(NULL);

					// Processing time usage
					int time_difference = (int) (time_end - time_start);
					float byte_rate = bytes_processed/time_difference;
					printf ("\n\nTime taken to process : %d Seconds",time_difference);
					printf("\nByte rate of program is : %f Bytes/Second",byte_rate);

					// all files have been parsed by now and the word list is populated
					if (SUCCESS == file_parsed)
					{
						Output obj_output;
						
						// Processing search options
						if (SEARCH_ACTIVE == search_status)
						{
							if(FAILURE == SearchForFileNames(obj_word_list,&bytes_processed))
							{
								printf("\nError in starting search module");
							}
							else
							{
								printf("\nSearch complete");
							}
						}

						// Processing print options to file or on screen
						if (PRINT_MODE_DISABLED != print_mode)
						{
							switch(print_mode)
							{
							case PRINT_MODE_SCREEN:
								obj_output.PrintOnScreen(obj_word_list,&bytes_processed);
								break;
							case PRINT_MODE_FILE:
								printf("\nExporting files to %s",output_path);
								obj_output.PrintToFile(output_path,obj_word_list,&bytes_processed);
								break;
							default:
								printf("\nUnknown print option");
								break;
							}
						}
						printf("\nProgram will exit now\n");
					}
					else
					{
						printf("\nError in parsing files");
						getch();
						return(-1);
					}
				}
				else
				{
					printf("\nError in fetching file paths");
					getch();
					return(-1);
				}
			}
			else
			{
				printf("\nError in reading directory information");
				getch();
				return(-1);
			}
		}
		else
		{
			printf("\nError in processing directory list");
			getch();
			return(-1);
		}		
	}
	else
	{
		printf("\nInvalid Command Line Argument");		
	}
	getch();
	return 0;
}
