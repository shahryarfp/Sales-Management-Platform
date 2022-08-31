#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buy.h"
void buy(int* flagg, char* first, char* second, char* third, char* fourth, char* fifth, int loged_in_user, int numofseller, int loged_in_user_number, SELLER** sellersaddress, BUYER** buyersaddress)
{
	if (!strcmp(first, "buy")& second != NULL & third != NULL&fourth != NULL&fifth == NULL)//if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		if (loged_in_user == 1)//so loged in user is seller
			printf("warning: this action is just for buyers\n");//print warning
		////errors
		int flag = 1;//for checking if format is ok
		//check if number of goods is integer or not
		for (int i = 0;i < strlen(third);i++)
		{
			if (third[i] > 57 || third[i] < 48)
			{
				printf("warning: number of goods should be an integer number!\n");
				flag = 0;
				break;
			}
		}


		if (flag == 1)
			if (loged_in_user == 2)//so loged in user is buyer
			{
				int flag1 = 0;//to show if seller or good found or not
				for (int i = 0;i < numofseller;i++)//searching in sellers
					for (int j = 0;j < (*sellersaddress)[i].numofgoods;j++)//searching in goods
					{
						if (!strcmp((*sellersaddress)[i].username, fourth)&!strcmp((*sellersaddress)[i].sellers_goods[j].goods_name, second))//if seller[i] and good[j] found
						{
							if ((*buyersaddress)[loged_in_user_number].money >= (*sellersaddress)[i].sellers_goods[j].goods_price*atoi(third) & (*sellersaddress)[i].sellers_goods[j].goods_count >= atoi(third))//if any good exist and the money is enough
							{
								flag1 = 1;//seller and good found
								int flag2 = 1;//to show if buyer bought this good before or not
								for (int k = 0;k < (*buyersaddress)[loged_in_user_number].numofgoods;k++) {
									if (!strcmp((*buyersaddress)[loged_in_user_number].buyers_goods[k].goods_name, second)) {//so buyer bought this good before
										//sellers changes
										(*sellersaddress)[i].money += (*sellersaddress)[i].sellers_goods[j].goods_price*atoi(third);//increase sellers money
										(*sellersaddress)[i].sellers_goods[j].goods_count -= atoi(third);//decrease sellers goods_count
										//buyers changes
										(*buyersaddress)[loged_in_user_number].buyers_goods[k].goods_count += atoi(third);//increase buyers number of goods
										(*buyersaddress)[loged_in_user_number].money -= (*sellersaddress)[i].sellers_goods[j].goods_price*atoi(third);//decrease buyers money
										printf("buying process completed!\n\n");
										flag2 = 0;//so buyer bought this good before
									}
								}
								if (flag2 == 1) {//so buyer didn't buy yhis good before
									//sellers changes
									(*sellersaddress)[i].money += (*sellersaddress)[i].sellers_goods[j].goods_price*atoi(third);//increase sellers money
									(*sellersaddress)[i].sellers_goods[j].goods_count -= atoi(third);//decrease sellers goods_count
									//buyers changes
									(*buyersaddress)[loged_in_user_number].numofgoods++;//increase buyers kinds of goods
									(*buyersaddress)[loged_in_user_number].money -= (*sellersaddress)[i].sellers_goods[j].goods_price*atoi(third);//decrease buyers money
									(*buyersaddress)[loged_in_user_number].buyers_goods = (GOOD*)realloc((*buyersaddress)[loged_in_user_number].buyers_goods, sizeof(GOOD)*(*buyersaddress)[loged_in_user_number].numofgoods);//allocate mwmory
									(*buyersaddress)[loged_in_user_number].buyers_goods[(*buyersaddress)[loged_in_user_number].numofgoods - 1].goods_count = atoi(third);//init goods_count
									(*buyersaddress)[loged_in_user_number].buyers_goods[(*buyersaddress)[loged_in_user_number].numofgoods - 1].goods_price = (*sellersaddress)[i].sellers_goods[j].goods_price;//init goods_price
									(*buyersaddress)[loged_in_user_number].buyers_goods[(*buyersaddress)[loged_in_user_number].numofgoods - 1].seller_name = (char*)malloc(sizeof(char)*strlen(fourth));//allocate memory
									(*buyersaddress)[loged_in_user_number].buyers_goods[(*buyersaddress)[loged_in_user_number].numofgoods - 1].seller_name = fourth;//init seller_name
									(*buyersaddress)[loged_in_user_number].buyers_goods[(*buyersaddress)[loged_in_user_number].numofgoods - 1].goods_name = (char*)malloc(sizeof(char)*strlen(second));//allocate memory
									(*buyersaddress)[loged_in_user_number].buyers_goods[(*buyersaddress)[loged_in_user_number].numofgoods - 1].goods_name = second;//init goods_name
									printf("buying process completed!\n\n");
								}
							}
							else {//warning
								printf("warning: your money or number of goods is not enough!\n");
								flag1 = 1;//to show just one of warnings
							}
						}
					}
				if (flag1 == 0)//warning
					printf("warning: seller or good not found!\n");
			}
	}
}