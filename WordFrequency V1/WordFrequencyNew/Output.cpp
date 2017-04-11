#include "StdAfx.h"
#include "Output.h"
#include "WordList.h"

void Output::printOnScreen(WordList *obj_word_list)
{
	word_structure* temp_print = obj_word_list->getWordListStart();
	while (NULL != temp_print)
	{
		printf("\n%s,%d",temp_print->word,temp_print->count);
		temp_print = temp_print->next;
	}
	delete temp_print;
}

void Output::printToFile(char *output_file_name, WordList *obj_word_list)
{
	FILE* write_fp = fopen(output_file_name,"w");
	if(NULL != write_fp)
	{
		word_structure* temp_write = obj_word_list->getWordListStart();
		while(NULL != temp_write)
		{
			fprintf(write_fp,"\n%s,%d",temp_write->word,temp_write->count);
			temp_write = temp_write->next;
		}
		printf("\nFile Exported to : %s",output_file_name);
		delete temp_write;
	}
	else
	{
		printf("\nUnable to export to file");
	}
	fclose(write_fp);
}