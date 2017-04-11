#include <stdafx.h>
#include <conio.h>
#include <stdlib.h>
#include <ParseFile.h>
#include <WordList.h>
#include <Output.h>
#include <cstring>
#include <FileNameList.h>
#include <ListDirectoryFiles.h>
#include <DirectoryNameList.h>

#define SUCCESS 1
#define FAILURE 0

char* allocateMemoryForCommand(int size)
{
	char* new_word = new char[size];
	if (NULL != new_word)
	{
		return new_word;
	}
	else
	{
		printf("\nError allocating memory");
		exit(1);
	}
}

void printHelpMessage()
{
	printf("\n\nwordfrequency -i <directory path> [-os] [-of] <file path> [-r] ");
	printf("\n-i  : for input directory\n-os : for output on screen \n-of : for output on a file \n-r  : for recursive directory access\n");
}

int main(int argc, char* argv[])
{		
	char* input_path = NULL;
	char* output_path = NULL;
	bool recursive_directory_access = false;	
	bool help_accessed = false;
	int is_data_processed = FAILURE;
	int counter = 1;
	int print_mode = 1;		// 1 for screen output 2 for file output	

	// processing command line arguments
	if (argc > 1)
	{
		while (NULL != argv[counter])
		{
			if (!strcmp(argv[counter],"-i") || !strcmp(argv[counter],"-I"))
			{
				if (NULL != argv[counter+1])
				{
					input_path = allocateMemoryForCommand(strlen(argv[counter+1])+1);
					input_path = argv[counter+1];
					counter++;
				}
				else
				{
					printf("\n Input Path Name Not Found"); 
					printHelpMessage();
					help_accessed = true;
				}
			}
			else if (!strcmp(argv[counter],"-OS")|| !strcmp(argv[counter],"-Os") || !strcmp(argv[counter],"-oS") || !strcmp(argv[counter],"-os"))
			{
				// for screen print;
				output_path = NULL;
				print_mode = 1;
			}
			else if (!strcmp(argv[counter],"-OF") ||!strcmp(argv[counter],"-Of") || !strcmp(argv[counter],"-oF") || !strcmp(argv[counter],"-of"))
			{
				if (NULL != argv[counter+1])
				{
					// to export to file
					print_mode = 2;
					output_path = allocateMemoryForCommand(strlen(argv[counter+1])+1);
					output_path = argv[counter+1];
					counter++;
				}
				else
				{
					printf("\nOutput Path Name Not Found");
					printHelpMessage();
					help_accessed = true;
				}
			}
			else if (!strcmp(argv[counter],"-r") || !strcmp(argv[counter],"-R"))
			{
				recursive_directory_access = true;
			}
			else if(!strcmp(argv[counter],"-help") || !strcmp(argv[counter],"-HELP"))
			{
				printHelpMessage();
				help_accessed = true;
			}
			else
			{
				printf("\nUnknown Input");
				printHelpMessage();
				help_accessed = true;
			}
			counter++;
		}		
	}
	else
	{
		printHelpMessage();
		help_accessed = true;
	}

	if (!help_accessed)
	{
		FileNameList* obj_file_name_list = new FileNameList();
		ListDirectoryFiles* obj_list_directory_files = new ListDirectoryFiles();
		DirectoryNameList* obj_directory_name_list = new DirectoryNameList();	

		// populating the file list with all the file names and directory list with all directory names

		obj_directory_name_list->insert(input_path);
		char* current_path = obj_directory_name_list->getNextDirectoryName();	
		while (NULL != current_path)
		{		
			if(recursive_directory_access)
			{
				is_data_processed = obj_list_directory_files->populateDirectoryNameList(current_path ,obj_directory_name_list);	
			}
			is_data_processed = obj_list_directory_files->populateFileNameList(current_path,obj_file_name_list);
			current_path = obj_directory_name_list->getNextDirectoryName();		
		}

		// parsing each file in the list for words
		ParseFile obj_parse_file;
		WordList* obj_word_list = new WordList();
		char* file_path = obj_file_name_list->getNextFileName();
		while (NULL != file_path)
		{
			if (obj_parse_file.parse(file_path,obj_word_list))
			{		
				printf("\nFile Parsed : %s",file_path);
			}		
			file_path = obj_file_name_list->getNextFileName();
		}

		// default output mode is on screen
		// Generating output
		if(SUCCESS == is_data_processed)
		{
			Output obj_output;
			switch(print_mode)
			{
			case 1:
				obj_output.printOnScreen(obj_word_list);
				break;
			case 2: 
				obj_output.printToFile(output_path,obj_word_list);
				break;
			default:
				printf("\nUnknown print option");
			}	
		}
		else
		{
			printf("\nError Traversing Directories");
		}
	}
	getch();
}		