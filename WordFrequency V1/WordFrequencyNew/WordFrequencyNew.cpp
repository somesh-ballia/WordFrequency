#include "stdafx.h"
#include "ParseFile.h"
#include "WordList.h"
#include "Output.h"
#include "FileNameList.h"
#include "ListDirectoryFiles.h"
#include "DirectoryNameList.h"
#include <conio.h>

int main()
{
	char* path = new char[100];
	printf("\n Path : ");
	scanf("%s",path);

	FileNameList* obj_file_name_list = new FileNameList();
	ListDirectoryFiles* obj_list_directory_files = new ListDirectoryFiles();
	obj_list_directory_files->populateFileNameList(path,obj_file_name_list);
	WordList* obj_word_list = new WordList();
	Output obj_output;
	ParseFile obj_parse_file;

	char* file_path = obj_file_name_list->getNextFileName();
	while(NULL != file_path)
	{
		printf("\n Parsing %s",file_path);
		obj_parse_file.parse(file_path,obj_word_list);	
		file_path = obj_file_name_list->getNextFileName();
	}
	//obj_output.printOnScreen(obj_word_list);
	obj_output.printToFile("c:/output.txt",obj_word_list);		
	
	getch();
}
	