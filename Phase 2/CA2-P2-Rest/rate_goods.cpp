#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rate_goods.h"

void rate_goods(int* flagg, char* first, char* second, char* third, char* fourth, char* fifth, int loged_in_user, int numofseller, int loged_in_user_number, SELLER** sha, BUYER** bha)
{
	// sha is sellers_head_address
	// bha is buyers_head_address
	if (!strcmp(first, "rate_goods") & second != NULL & third != NULL & fourth != NULL & fifth == NULL)//if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		if (loged_in_user == 1)//so loged in user is seller
			printf("warning: this action is just for buyers\n");//print warning
		////errors
		int flag = 1;//for checking if format is ok
		//check if rate is integer or between 1 and 5
		if (fourth[0] > 53 || fourth[0] < 49 || fourth[1] != NULL)
		{
			printf("warning: enter integer number and number from 1 to 5!\n");
			flag = 0;
		}
		if (flag == 0)
			return;//end of function
		//else:
		//find the loged in buyer
		flag = 0;//to show if buyer had this good or not
		BUYER* bha_temp = *bha;//make temporary head
		for (int i = 0;i < loged_in_user_number+1;i++)
			bha_temp = bha_temp->next;//goto next node
		int k;//address of this good in buyers goods
		GOOD* good_temp = bha_temp->buyers_goods;//make temporary head
		for (k = 0;k < bha_temp->numofgoods;k++) {//search in goods
			good_temp = good_temp->next;
			if (!strcmp(good_temp->goods_name, second))//if the good found
				flag = 1;//so buyer had this good
		}
		if (flag == 0){
			printf("warning: you don't have this good!\n\n");
			return;//end of function
		}
		SELLER* sha_temp = *sha;//make temporary head
		sha_temp->sellers_goods->rate;
		for (int i = 0;i < numofseller;i++)//search in sellers
		{
			sha_temp = sha_temp->next;//goto next node
			if (!strcmp(sha_temp->username, third))//if user found
			{
				GOOD* good_temp2 = sha_temp->sellers_goods;//make temporary head
				for (int j = 0;j < sha_temp->numofgoods;j++)//search in goods
				{
					good_temp2 = good_temp2->next;
					if (!strcmp(good_temp2->goods_name, second))//if good found
					{
						if (good_temp->rate == 1)
						{
							printf("warning: you rated this good before!\n\n");
							return;
						}
						good_temp->rate = 1;//it means that this buyer had rated this good
						good_temp2->rate = (good_temp2->rate*good_temp2->numofrated+atoi(fourth))/(good_temp2->numofrated+1);
						good_temp2->numofrated++;//increase number of rated of this good of sellers
						printf("rated successfully!\n\n");
						return;
					}
				}
			}
		}
		printf("warning: user or good not found!\n\n");
	}
}