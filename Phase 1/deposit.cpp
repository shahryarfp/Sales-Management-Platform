#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deposit.h"
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
			printf("your money increased\n\n");
		}
	}
}