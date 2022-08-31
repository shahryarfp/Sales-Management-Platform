#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "remove_goods.h"
void remove_goods(int* flagg, char* first, char* second, char* third, int loged_in_user, int loged_in_user_number, SELLER** sha)
{
	// sha is sellers_head_address
	if (!strcmp(first, "remove_goods")& second != NULL & third == NULL)//if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		if (loged_in_user == 2)//so loged in user is buyer
			printf("warning: this action is just for sellers\n\n");
		else//so loged in user is seller
		{
			SELLER* sha_temp = *sha;//make temporary head
			for (int i = 0;i < loged_in_user_number + 1;i++)
			{
				sha_temp = sha_temp->next;//goto next node
			}
			GOOD* good_temp = sha_temp->sellers_goods;//make temporary head
			for (int i = 0;i <  sha_temp ->numofgoods ;i++)//search in goods
			{
				if (!strcmp(second, good_temp->next->goods_name))//if good exists
				{
					GOOD* temp = good_temp->next;//save good_temp->next to free it later
					good_temp->next = temp->next;
					free(temp);//delete
					sha_temp->numofgoods--;//decrease number of goods
					printf("removed!\n\n");
					return;//return from function
				}
				good_temp = good_temp->next;
			}
			//so good not found
			printf("error: good not found!\n\n");
		}
	}
}