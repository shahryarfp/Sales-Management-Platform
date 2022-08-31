#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"view.h"
void view(int* flagg, char* first, char* second, int loged_in_user, int loged_in_user_number, int numofseller, SELLER** sellersaddress, BUYER** buyersaddress)
{
	if (!strcmp(first, "view") & second == NULL) // if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		if (loged_in_user == 1)//it means that our loged in user was seller
		{
			printf("username: %s\n", (*sellersaddress)[loged_in_user_number].username);
			printf("role: seller\n");
			printf("money: %d\n", (*sellersaddress)[loged_in_user_number].money);
			printf("goods:\n");
			if ((*sellersaddress)[loged_in_user_number].numofgoods == 0)//check if any good exists
				printf("no good\n\n");
			for (int i = 0;i < (*sellersaddress)[loged_in_user_number].numofgoods;i++)//search in goods
				printf("good[%d]:\nname: %s\nprice: %d\nnumber of this good: %d\n\n", i + 1, (*sellersaddress)[loged_in_user_number].sellers_goods[i].goods_name, (*sellersaddress)[loged_in_user_number].sellers_goods[i].goods_price, (*sellersaddress)[loged_in_user_number].sellers_goods[i].goods_count);
			free(first);//free command line
		}
		else//it means that our loged in user was buyer
		{
			printf("username: %s\n", (*buyersaddress)[loged_in_user_number].username);
			printf("role: buyer\n");
			printf("money: %d\n", (*buyersaddress)[loged_in_user_number].money);
			printf("shoppings:\n\n");
			if ((*buyersaddress)[loged_in_user_number].numofgoods == 0)//search in shoppings
				printf("not any shopping yet\n\n");
			for (int i = 0;i < (*buyersaddress)[loged_in_user_number].numofgoods;i++) {//search in buyers goods
				printf("good[%d]:\nname: %s\nprice: %d\nnumber of this good you have: %d\n", i + 1, (*buyersaddress)[loged_in_user_number].buyers_goods[i].goods_name, (*buyersaddress)[loged_in_user_number].buyers_goods[i].goods_price, (*buyersaddress)[loged_in_user_number].buyers_goods[i].goods_count);
				for (int k = 0;k < numofseller;k++)//search in sellers
					for (int j = 0;j < (*sellersaddress)[k].numofgoods;j++)//search in sellers goods
						if (!strcmp((*buyersaddress)[loged_in_user_number].buyers_goods[i].goods_name, (*sellersaddress)[k].sellers_goods[j].goods_name))//goods seller found
							printf("this good's seller: %s\n\n", (*sellersaddress)[k].username);
			}
			free(first);//free command line
		}
	}
}