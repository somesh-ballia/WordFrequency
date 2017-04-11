#include <StdAfx.h>
#include <Output.h>
#include <WordList.h>

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
	if (NULL != write_fp)
	{
		word_structure* temp_write = obj_word_list->getWordListStart();
		while (NULL != temp_write)
		{
			fprintf(write_fp,"\n%s,%d",temp_write->word,temp_write->count);
			temp_write = temp_write->next;
		}
		printf("\n\n\n\nFile Exported to : %s",output_file_name);
		delete temp_write;
		fclose(write_fp);
	}
	else
	{
		printf("\nError in file export : %s",output_file_name);
	}	
}

void Output::printFileList(PathNameFrequency *obj_path_name_frequency,int word_count)
{
	path_frequency_structure* temp_print = obj_path_name_frequency->getPathNameFrequencyStart();
	while (NULL != temp_print)
	{
		if (temp_print->count == word_count)
		{
			printf("\n%s",temp_print->path);
		}
		temp_print = temp_print->next;
	}
}

