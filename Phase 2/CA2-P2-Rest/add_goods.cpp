#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "add_goods.h"
#include "mallcheck.h"
void add_goods(int* flagg, char* first, char* second, char* third, char* fourth, char* fifth, char* sixth, int loged_in_user, int loged_in_user_number, SELLER** sha)
{
	// sha is sellers_head_address
	if (!strcmp(first, "add_goods")& second != NULL & third != NULL&fourth != NULL&fifth != NULL&sixth == NULL)//if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		if (loged_in_user == 2)//so loged in user is buyer
			printf("warning: this action is just for sellers\n\n");
		else//so loged in user is seller
		{
			int flag = 1;//for checking if format is ok
			for (int i = 0;i < strlen(fourth);i++)
			{
				if (fourth[i] > 57 || fourth[i] < 48)
				{
					printf("warning: please enter integer price!\n\n");
					flag = 0;
					break;
				}
			}
			for (int i = 0;i < strlen(fifth);i++)
			{
				if (i == 0)
				{
					if ((fifth[i] > 57 || fifth[i] < 48) & fifth[i] != '-')
					{
						printf("warning: please enter integer money!\n\n");
						flag = 0;
						break;
					}
				}
				else
				{
					if (fifth[i] > 57 || fifth[i] < 48)
					{
						printf("warning: number of goods should be an integer number!\n\n");
						flag = 0;
						break;
					}
				}
			}
			SELLER* sha_temp = *sha;//make temporary head
			for (int i = 0;i < loged_in_user_number + 1;i++)
			{
				sha_temp = sha_temp->next;//goto next node
			}
			if (strcmp(second, sha_temp->username))
			{
				printf("warning: you entered wrong username!\n\n");
				flag = 0;

			}
			GOOD* good_temp = sha_temp->sellers_goods;//make temporary head
			for (int i = 0;i < sha_temp->numofgoods;i++) {
				good_temp = good_temp->next;//goto next node
				if (!strcmp(third, good_temp->goods_name) & atoi(fourth) != good_temp->goods_price)
				{
					printf("warning: this goods name has taken before!\n\n");
					flag = 0;
				}
			}
			if (flag == 1)//so format is OK
			{
				int flag = 0;//to show if this good existed before or not
				GOOD* good_temp = sha_temp->sellers_goods;//make temporary head
				for (int i = 0;i < sha_temp->numofgoods;i++) {
					good_temp = good_temp->next;//goto next node
					if (!strcmp(third, good_temp->goods_name)&atoi(fourth) == good_temp->goods_price)
					{
						if (good_temp->goods_count + atoi(fifth) < 0) {
							printf("warning: not possible. goods_count should not be less than zero!\n\n");
							flag = 1;
						}
						else
						{
							flag = 1;
							good_temp->goods_count += atoi(fifth);
							printf("goods added!\n\n");
						}
					}
				}
				if (flag == 0) {//so good did not exist before
					sha_temp->numofgoods++;//increase number of goods

					GOOD* new_node = (GOOD*)malloc(sizeof(GOOD));//allocate memory
					if (new_node == NULL)//mallcheck
					{
						printf("Malloc Error!\n\n");
						exit(EXIT_FAILURE);
					}
					GOOD* good_temp = sha_temp->sellers_goods;
					for (int i = 0;i < sha_temp->numofgoods-1;i++) {
						good_temp = good_temp->next;
					}
					good_temp->next = new_node;

					new_node->goods_name = (char*)malloc(sizeof(char)*strlen(third));//allocate memory for goods name
					new_node->goods_name = third;//init goods_name
					new_node->seller_name = (char*)malloc(sizeof(char)*strlen(second));//allocate memory for goods name
					new_node->seller_name = second;//init seller_name
					new_node->goods_price = atoi(fourth);//init goods_price
					new_node->goods_count = atoi(fifth);//init goods_count
					new_node->rate = 0;
					new_node->numofrated = 0;
					new_node->next = NULL;
					printf("goods added!\n\n");
				}
			}
		}
	}
}