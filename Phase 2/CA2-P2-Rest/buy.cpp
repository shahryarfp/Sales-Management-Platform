#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buy.h"
void buy(int* flagg, char* first, char* second, char* third, char* fourth, char* fifth, int loged_in_user, int numofseller, int loged_in_user_number, SELLER** sha, BUYER** bha)
{
	// sha is sellers_head_address
	// bha is buyers_head_address
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
				SELLER* sha_temp = *sha;//make temporary head
				BUYER* bha_temp = *bha;//make temporary head
				for (int i = 0;i < loged_in_user_number + 1;i++)
				{
					bha_temp = bha_temp->next;//goto next node
				}
				int flag1 = 0;//to show if seller or good found or not
				int flag2 = 1;//to show if good is active or not
				for (int i = 0;i < numofseller;i++)//searching in sellers
				{
					sha_temp = sha_temp->next;//goto next node
					GOOD* good_temp = sha_temp->sellers_goods;//make temporary head
					for (int j = 0;j < sha_temp->numofgoods;j++)//searching in goods
					{
						good_temp = good_temp->next;
						if (!strcmp(sha_temp->username, fourth)&!strcmp(good_temp->goods_name, second))//if seller[i] and good[j] found
						{

							if (good_temp->numofrated >= 5 & good_temp->rate < 2)//to inactivate good
								flag2 = 0;

							if(flag2==1)//if good was active
							{
								if (bha_temp->money >= good_temp->goods_price*atoi(third) & good_temp->goods_count >= atoi(third))//if any good exist and the money is enough
								{
									flag1 = 1;//seller and good found
									int flag2 = 1;//to show if buyer bought this good before or not
									GOOD* good_temp2 = bha_temp->buyers_goods;//make temporary head
									for (int k = 0;k < bha_temp->numofgoods;k++) {
										good_temp2 = good_temp2->next;
										if (!strcmp(good_temp2->goods_name, second)) {//so buyer bought this good before
											//sellers changes
											sha_temp->money += good_temp->goods_price*atoi(third);//increase sellers money
											good_temp->goods_count -= atoi(third);//decrease sellers goods_count
											//buyers changes
											good_temp2->goods_count += atoi(third);//increase buyers number of goods
											bha_temp->money -= good_temp->goods_price*atoi(third);//decrease buyers money
											printf("buying process completed!\n\n");
											flag2 = 0;//so buyer bought this good before
										}
									}
									if (flag2 == 1) {//so buyer didn't buy this good before
										//sellers changes
										sha_temp->money += good_temp->goods_price*atoi(third);//increase sellers money
										good_temp->goods_count -= atoi(third);//decrease sellers goods_count
										//buyers changes
										GOOD* new_node = (GOOD*)malloc(sizeof(GOOD));//allocate memory
										if (new_node == NULL)//mallcheck
										{
											printf("Malloc Error!\n\n");
											exit(EXIT_FAILURE);
										}
										GOOD* good_temp2 = bha_temp->buyers_goods;
										for (int i = 0;i < bha_temp->numofgoods - 1;i++) {
											good_temp2 = good_temp2->next;
										}
										good_temp2->next = new_node;

										bha_temp->numofgoods++;//increase buyers kinds of goods
										bha_temp->money -= good_temp->goods_price*atoi(third);//decrease buyers money
										//bha_temp->buyers_goods = (GOOD*)realloc(bha_temp->buyers_goods, sizeof(GOOD)*bha_temp->numofgoods);//allocate mwmory
										new_node->goods_count = atoi(third);//init goods_count
										new_node->goods_price = good_temp->goods_price;//init goods_price
										new_node->seller_name = (char*)malloc(sizeof(char)*strlen(fourth));//allocate memory
										new_node->seller_name = fourth;//init seller_name
										new_node->goods_name = (char*)malloc(sizeof(char)*strlen(second));//allocate memory
										new_node->goods_name = second;//init goods_name
										new_node->rate = 0;
										new_node->numofrated = 0;
										new_node->next = NULL;
										printf("buying process completed!\n\n");
									}
								}
								else {//warning
									printf("warning: your money or number of goods is not enough!\n");
									flag1 = 1;//to show just one of warnings
								}
							}
						}
					}
					}
				if (flag1 == 0)//warning
					printf("warning: seller or good not found!\n");
			}
	}
}