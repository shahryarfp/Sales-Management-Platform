#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deposit.h"
#include "get_fline.h"
void deposit(int* flagg, char* first, char* second, char* third, int loged_in_user, int loged_in_user_number, BUYER** buyersaddress)
{
	if (!strcmp(first, "deposit") & second != NULL & third == NULL)//if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		int flag = 1;//for checking if format is ok
		if (loged_in_user == 1) {//so user is seller
			printf("warning: this action is just for buyers\n\n");
			flag = 0;
		}
		else//so user is buyer
		{
			//check integers in input format
			for (int i = 0;i < strlen(second);i++)
			{
				if (i == 0)
				{
					if ((second[i] > 57 || second[i] < 48) & second[i] != '-')//we let our integer number to be less than zero
					{
						printf("warning: please enter integer money!\n\n");
						flag = 0;
						break;
					}
				}
				else
				{
					if (second[i] > 57 || second[i] < 48)
					{
						printf("warning: please enter integer money!\n\n");
						flag = 0;
						break;
					}
				}
			}
		}
		if (flag == 1) {//so format was OK
			(*buyersaddress)[loged_in_user_number].money += atoi(second);
			FILE *myfile = fopen("buyers.txt", "r");
			if (myfile == NULL)//error opening file
				printf("Error while opening file");
			FILE *mytempfile = fopen("buyers_temp.txt", "w");
			if (mytempfile == NULL)//error opening file
				printf("Error while opening file");
			while (true)
			{
				char *fline_str = get_fline(myfile);
				if (*fline_str == NULL)//end of file
					break;

				char *token = strtok(fline_str, ",");
				if (!strcmp((*buyersaddress)[loged_in_user_number].username, token))
				{
					fprintf(mytempfile, "%s,", token);
					token = strtok(NULL, ",");
					fprintf(mytempfile, "%s,", token);
					token = strtok(NULL, ",");
					fprintf(mytempfile, "%d\n", atoi(token)+ atoi(second));
					free(fline_str);
				}
				else
				{
					fprintf(mytempfile, "%s,", token);
					token = strtok(NULL, ",");
					fprintf(mytempfile, "%s,", token);
					token = strtok(NULL, ",");
					fprintf(mytempfile, "%s\n", token);
					free(fline_str);
				}
			}
			fclose(myfile);
			fclose(mytempfile);
			remove("buyers.txt");
			rename("buyers_temp.txt", "buyers.txt");
			printf("your money increased\n\n");
		}
	}
}