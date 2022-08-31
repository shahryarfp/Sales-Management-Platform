#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"view.h"

void view(int* flagg, char* first, char* second, int loged_in_user, int loged_in_user_number, int numofseller, SELLER** sha, BUYER** bha)
{
	// sha is sellers_head_address
	// bha is buyers_head_address
	if (!strcmp(first, "view") & second == NULL) // if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		if (loged_in_user == 1)//it means that our loged in user was seller
		{
			SELLER* sha_temp = *sha;//make temporary head
			for (int i = 0;i < loged_in_user_number + 1;i++)
			{
				sha_temp = sha_temp->next;//goto next node
			}
			printf("username: %s\n", sha_temp->username);
			printf("role: seller\n");
			printf("money: %d\n", sha_temp->money);
			printf("goods:\n");
			if (sha_temp->numofgoods == 0)//check if any good exists
				printf("no good\n\n");

			GOOD* good_temp = sha_temp->sellers_goods;//make temporary head

			for (int i = 0;i < sha_temp->numofgoods;i++) {//search in goods
				good_temp = good_temp->next;//goto next node
				printf("good[%d]:\nname: %s\nprice: %d\nnumber of this good: %d\n", i + 1, good_temp->goods_name, good_temp->goods_price, good_temp->goods_count);
				if (good_temp->rate == 0)
					printf("there is no rate for this good yet\n\n");
				else
					printf("this goods rate: %.2f\n\n", good_temp->rate);
			}
			free(first);//free command line
		}
		else//it means that our loged in user was buyer
		{
			BUYER* bha_temp = *bha;//make temporary head
			for (int i = 0;i < loged_in_user_number + 1;i++)
			{
				bha_temp = bha_temp->next;//goto next node
			}
			printf("username: %s\n", bha_temp->username);
			printf("role: buyer\n");
			printf("money: %d\n", bha_temp->money);
			printf("shoppings:\n\n");
			if (bha_temp->numofgoods == 0)//search in shoppings
				printf("not any shopping yet\n\n");
			GOOD* good_temp = bha_temp->buyers_goods;//make temporary head
			for (int i = 0;i < bha_temp->numofgoods;i++) {//search in buyers goods
				good_temp = good_temp->next;//goto next node
				printf("good[%d]:\nname: %s\nprice: %d\nnumber of this good you have: %d\n", i + 1, good_temp->goods_name, good_temp->goods_price, good_temp->goods_count);
				SELLER* sha_temp = *sha;
				for (int k = 0;k < numofseller;k++) {//search in sellers
					sha_temp = sha_temp->next;
					GOOD* good_temp2 = sha_temp->sellers_goods;//make temporary head
					for (int j = 0;j < sha_temp->numofgoods;j++) {//search in sellers goods
						good_temp2 = good_temp2->next;//goto next node
						if (!strcmp(good_temp->goods_name, good_temp2->goods_name))//goods seller found
							printf("this good's seller: %s\n\n", sha_temp->username);
					}
				}
			}
			free(first);//free command line
		}
	}
}