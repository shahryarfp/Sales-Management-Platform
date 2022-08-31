#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "show_goods.h"
void show_goods(int* flagg, char* first, char* second, int numofseller, SELLER** sellersaddress)
{
	if (!strcmp(first, "show_goods") & second == NULL)//if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		int k = 0;//for counting goods
		int flag = 0;//to show if good exists or not
		for (int i = 0;i < numofseller;i++)//search in sellers
			for (int j = 0;j < (*sellersaddress)[i].numofgoods;j++)//search in sellers goods
			{
				flag = 1;//good found
				printf("good %d:\n", ++k);
				printf("sellers name: %s\n", (*sellersaddress)[i].username);//print sellers username
				printf("goods name: %s\n", (*sellersaddress)[i].sellers_goods[j].goods_name);//print goods_name
				printf("goods price: %d\n", (*sellersaddress)[i].sellers_goods[j].goods_price);//print goods price
				printf("number of this good: %d\n\n", (*sellersaddress)[i].sellers_goods[j].goods_count);//print goods_count
			}
		if (flag == 0)//good didn't found
			printf("there is no good\n\n");
		free(first);//free command line
	}
}