#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "change_goods_price.h"
void change_goods_price(int* flagg, char* first, char* second, char* third, char* fourth, int loged_in_user, int loged_in_user_number, SELLER** sha)
{
	// sha is sellers_head_address
	if (!strcmp(first, "change_goods_price")& second != NULL & third != NULL & fourth==NULL)//if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		if (loged_in_user == 2)//so loged in user is buyer
			printf("warning: this action is just for sellers\n\n");
		else//so loged in user is seller
		{
			int flag = 1;//for checking if format is ok
			for (int i = 0;i < strlen(third);i++)
			{
				if (third[i] > 57 || third[i] < 48)
				{
					printf("warning: please enter integer price!\n\n");
					flag = 0;
					break;
				}
			}
			if (flag == 0)
				return;//end of function
			//else:
			SELLER* sha_temp = *sha;//make temporary head
			for (int i = 0;i < loged_in_user_number + 1;i++)
			{
				sha_temp = sha_temp->next;//goto next node
			}
			GOOD* good_temp = sha_temp->sellers_goods;//make temporary head
			for (int i = 0;i < sha_temp->numofgoods;i++)//search in goods
			{
				good_temp = good_temp->next;//goto next node
				if (!strcmp(second, good_temp->goods_name))//if good exists
				{
					good_temp->goods_price = atoi(third);
					printf("price changed!\n\n");
					return;//return from function
				}
			}
			//so good not found
			printf("error: good not found!\n\n");
		}
	}
}
