#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "search.h"
#include "get_cmd.h"
#include "sort_by_name.h"
#include "compare.h"

int isnumber(char* second)
{
	for (int i = 0;i < strlen(second);i++)
	{
		if (second[i]<'0' || second[i]>'9')
			return 0;
	}
	return 1;
}
void search(int* flagg, char* first, char* second,char* third, int numofseller, SELLER** sha)
{
	// sha is sellers_head_address
	if (!strcmp(first, "search") & second != NULL & third == NULL)//if inputs total format is ok
	{
		*flagg = 1;//inputs total format is ok
		int flag = 1;//for checking if format is ok
		//check if rate is integer or between 1 and 5
		if (second[0] > 52 || second[0] < 49 || second[1] != NULL)
		{
			printf("warning: enter integer number and you can just have 1 to 4 conditions!\n");
			flag = 0;
		}
		if (flag == 0)
			return;//end of function

	    ////////////else:

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
		//now temporary sorted list is created
		//from now on we can remove unwanted goods from this list
		for (int i = 0;i < atoi(second);i++)
		{

			char *cmdstr = get_cmd();//get command line
			// split command line and put them in strings
			char *first = strtok(cmdstr, " ");
			char *second = strtok(NULL, " ");
			char *third = strtok(NULL, " ");

			int p = 0;


			////////////////first condition
			if (!strcmp(first, "name") & second != NULL & third == NULL)
			{
				p = 1;
				GOOD* temporary = all_goods_head;
				while(temporary->next!=NULL)
				{
					int w = 1;
					if (strcmp(temporary->next->goods_name, second))
					{
						//removing unwanted goods
						GOOD* temporary2 = temporary->next;
						temporary->next = temporary2->next;
						free(temporary2);
						numof_all_goods--;
						w = 0;
					}
					if (w == 1)
						temporary = temporary->next;
				}
			}




			/////////////////////second condition
			if (!strcmp(first, "seller_username") & second != NULL & third == NULL)
			{
				p = 1;
				GOOD* temporary = all_goods_head;
				while (temporary->next != NULL)
				{
					int w = 1;
					if (strcmp(temporary->next->seller_name, second))
					{
						//removing unwanted goods
						GOOD* temporary2 = temporary->next;
						temporary->next = temporary2->next;
						free(temporary2);
						numof_all_goods--;
						w = 0;
					}
					if (w == 1)
						temporary = temporary->next;
				}
			}





			////////////////third condition
			if (!strcmp(first, "min_price") & second != NULL & third == NULL)
			{
				p = 1;
				//checking if the min_price is integer
				if (!isnumber(second))
				{
					printf("warning: please enter an integer number!\n");
					i--;
				}
				GOOD* temporary = all_goods_head;
				while (temporary->next != NULL)
				{
					int w = 1;
					if (temporary->next->goods_price < atoi(second))
					{
						//removing unwanted goods
						GOOD* temporary2 = temporary->next;
						temporary->next = temporary2->next;
						free(temporary2);
						numof_all_goods--;
						w = 0;
					}
					if(w==1)
						temporary = temporary->next;
				}
			}






			///////////////////fourth condition
			if (!strcmp(first, "max_price") & second != NULL & third == NULL)
			{
				p = 1;
				//checking if the min_price is integer
				if (!isnumber(second))
				{
					printf("warning: please enter an integer number!\n");
					i--;
				}
				GOOD* temporary = all_goods_head;
				while (temporary->next != NULL)
				{
					int w = 1;
					if (temporary->next->goods_price > atoi(second))
					{
						//removing unwanted goods
						GOOD* temporary2 = temporary->next;
						temporary->next = temporary2->next;
						free(temporary2);
						numof_all_goods--;
						w = 0;
					}
					if (w == 1)
						temporary = temporary->next;
				}
			}
			if (p == 0)
			{
				printf("warning: wrong format input!\n");
				i--;
			}
			free(cmdstr);
		}




		//now the list is ready to be printed
		GOOD* good_temp = all_goods_head;//make temporary head

		int k = 0;//for counting goods
		int flag3 = 0;//to show if good exists or not
		for (int i = 0;i < numof_all_goods;i++) //search in sellers
		{
			good_temp = good_temp->next;
			flag3 = 1;//good found
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
		if (flag3 == 0)//good didn't found
			printf("there is no good\n\n");
		free(all_goods_head);
		free(first);
	}
}
