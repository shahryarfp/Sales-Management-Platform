#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort_by_name.h"
#include "compare.h"
int sort_by_name(GOOD *head)
{
	GOOD* temp1;
	GOOD *temp2;
	GOOD *a;
	int flag = 0;
	for (a = head;a != NULL;a = a->next)
	{
		for (temp1 = a->next;temp1 != NULL;temp1 = temp1->next)
		{
			for (temp2 = temp1->next;temp2 != NULL;temp2 = temp2->next)
			{
				if (compare(temp1->goods_name, temp2->goods_name) == 2)
				{
					flag = 1;
					//change good name
					char* name = temp2->goods_name;
					temp2->goods_name = temp1->goods_name;
					temp1->goods_name = name;
					//change seller name
					char* name1 = temp2->seller_name;
					temp2->seller_name = temp1->seller_name;
					temp1->seller_name = name1;
					//change rate
					float rate = temp2->rate;
					temp2->rate = temp1->rate;
					temp1->rate = rate;
					//change good count
					int gc = temp2->goods_count;
					temp2->goods_count = temp1->goods_count;
					temp1->goods_count = gc;
					//change good price
					int gp = temp2->goods_price;
					temp2->goods_price = temp1->goods_price;
					temp1->goods_price = gp;
					//change numofrated
					int nor = temp2->numofrated;
					temp2->numofrated = temp1->numofrated;
					temp1->numofrated = nor;
				}
			}
		}
	}
	return flag;
}