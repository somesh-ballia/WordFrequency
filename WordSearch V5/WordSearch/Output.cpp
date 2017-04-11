#include <StdAfx.h>
#include <Output.h>

int Output::PrintOnScreen(WordList *obj_word_list,unsigned __int64* bytes_processed)
{	
	word_structure* temp_print = obj_word_list->GetWordListStart();
	if (NULL != temp_print)
	{
		while (NULL != temp_print)
		{		
			printf("\n%s,%d",temp_print->word,temp_print->count);		
			temp_print = temp_print->next;
		}		
	}
	else
	{
		printf("\nPrining Failed");
		return FAILURE;
	}
	return SUCCESS;
}

int Output::PrintToFile(char *output_file_name, WordList *obj_word_list,unsigned __int64* bytes_processed)
{
	FILE* write_fp = fopen(output_file_name,"w");
	if (NULL != write_fp)
	{
		word_structure* temp_write = obj_word_list->GetWordListStart();
		if (NULL != temp_write)
		{
			while (NULL != temp_write)
			{
				fprintf(write_fp,"\n%s,%d",temp_write->word,temp_write->count);
				temp_write = temp_write->next;
			}
			printf("\nFile Exported to : %s",output_file_name);			
			fclose(write_fp);
		}
		else
		{
			printf("\nPrining Failed");
			return FAILURE;
		}
	}
	else
	{
		printf("\nError in file export : %s",output_file_name);
		return FAILURE;
	}
	return SUCCESS;
}

int Output::PrintFileList(PathNameFrequency *obj_path_name_frequency,int word_count,unsigned __int64* bytes_processed)
{
	path_frequency_structure* temp_print = obj_path_name_frequency->GetPathNameFrequencyStart();
	if (NULL != temp_print)
	{
		while (NULL != temp_print)
		{
			if (temp_print->count >= word_count)
			{
				printf("\n%s",temp_print->path);
			}
			temp_print = temp_print->next;
		}
	}
	else
	{		
		return FAILURE;
	}
	return SUCCESS;
}

