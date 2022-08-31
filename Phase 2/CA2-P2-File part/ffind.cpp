#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get_fline.h"
#include "ffind.h"
#include "mallcheck.h"
int ffind(char* name,FILE* myfile)
{
	int numofline = 1;
	while (true)
	{
		char *fline_str = get_fline(myfile);

		if (fline_str == NULL)//end of file
			return -1;//it means not found

		//char *fline_str = get_fline(myfile);//get line from file
		char *token = strtok(fline_str, ",");
		if (!strcmp(name, token))
		{
			free(fline_str);
			return numofline;
		}
		while(true)
		{
			char *token = strtok(NULL, ",");
			if (token == NULL)
				break;//end of line
			if (!strcmp(name, token))
			{
				free(fline_str);
				return numofline;
			}
		}
		numofline++;
	}
}