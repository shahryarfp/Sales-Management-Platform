#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "show_goods.h"
#include "sort_by_name.h"
#include "compare.h"

void show_goods(int* flagg, char* first, char* second, int numofseller, SELLER** sha)
{
	// sha is sellers_head_address
	if (!strcmp(first, "show_goods") & second == NULL)//if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok

		//make linked list of all goods
		GOOD* all_goods_head = (GOOD*)malloc(sizeof(GOOD));
		all_goods_head->next = NULL;

		GOOD* coppy_all_goods_head = all_goods_head;
		int numof_all_goods = 0;
		int flag2 = 1;//to show if good is active or not
		SELLER* sha_temp = *sha;//make temporary head
		for (int i = 0;i < numofseller;i++) //search in sellers
		{
			sha_temp = sha_temp->next;//goto next node
			GOOD* good_temp = sha_temp->sellers_goods;//make temporary head
			for (int j = 0;j < sha_temp->numofgoods;j++)//search in sellers goods
			{
				good_temp = good_temp->next;
				if (good_temp->numofrated >= 5 & good_temp->rate < 2)//to inactivate good
					flag2 = 0;

				if (flag2 == 1)//if good was active
				{
					numof_all_goods++;//increase number of all_goods_list
					GOOD* temp = (GOOD*)malloc(sizeof(GOOD));//allocate memory
					temp->next = NULL;
					//make coppy
					temp->goods_count = good_temp->goods_count;
					temp->goods_name = good_temp->goods_name;
					temp->goods_price = good_temp->goods_price;
					temp->numofrated = good_temp->numofrated;
					temp->rate = good_temp->rate;
					temp->seller_name = good_temp->seller_name;
					//add to all goods linked list
					for (int i = 0;i < numof_all_goods - 1;i++)
						all_goods_head = all_goods_head->next;
					all_goods_head->next = temp;
					all_goods_head = coppy_all_goods_head;//recover heads address
				}
			}
		}
		
		sort_by_name(all_goods_head);//sort list by goods name

		GOOD* good_temp = all_goods_head;//make temporary head

		int k = 0;//for counting goods
		int flag = 0;//to show if good exists or not
		for (int i = 0;i < numof_all_goods;i++) //search in sellers
		{
			good_temp = good_temp->next;
			flag = 1;//good found
			printf("good %d:\n", ++k);
			printf("sellers name: %s\n", good_temp->seller_name);//print sellers username
			printf("goods name: %s\n", good_temp->goods_name);//print goods_name
			printf("goods price: %d\n", good_temp->goods_price);//print goods_price
			printf("number of this good: %d\n", good_temp->goods_count);//print goods_count
			if (good_temp->rate == 0)
				printf("there is no rate for this good yet\n\n");
			else
				printf("this goods rate: %.2f\n\n", good_temp->rate);
		}
		if (flag == 0)//good didn't found
			printf("there is no good\n\n");
		free(all_goods_head);
		free(first);//free command line
	}
}