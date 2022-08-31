#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "add_goods.h"
#include "get_fline.h"
void add_goods(int* flagg, char* first, char* second, char* third, char* fourth, char* fifth, char* sixth, int loged_in_user, int loged_in_user_number, SELLER** sellersaddress)
{
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
			if (strcmp(second, (*sellersaddress)[loged_in_user_number].username))
			{
				printf("warning: you entered wrong username!\n\n");
				flag = 0;

			}
			for (int i = 0;i < (*sellersaddress)[loged_in_user_number].numofgoods;i++) {
				if (!strcmp(third, (*sellersaddress)[loged_in_user_number].sellers_goods[i].goods_name) & atoi(fourth) != (*sellersaddress)[loged_in_user_number].sellers_goods[i].goods_price)
				{
					printf("warning: this goods name has taken before!\n\n");
					flag = 0;
				}
			}
			if (flag == 1)//so format is OK
			{
				int flag = 0;//to show if this good existed before or not
				for (int i = 0;i < (*sellersaddress)[loged_in_user_number].numofgoods;i++) {
					if (!strcmp(third, (*sellersaddress)[loged_in_user_number].sellers_goods[i].goods_name)&atoi(fourth) == (*sellersaddress)[loged_in_user_number].sellers_goods[i].goods_price)
					{
						if ((*sellersaddress)[loged_in_user_number].sellers_goods[i].goods_count + atoi(fifth) < 0) {
							printf("warning: not possible. goods_count should not be less than zero!\n\n");
							flag = 1;
						}
						else
						{
							flag = 1;
							(*sellersaddress)[loged_in_user_number].sellers_goods[i].goods_count += atoi(fifth);
							FILE *myfile = fopen("seller_goods.txt", "r");
							if (myfile == NULL)//error opening file
								printf("Error while opening file");
							FILE *mytempfile = fopen("seller_goods_temp.txt", "w");
							if (mytempfile == NULL)//error opening file
								printf("Error while opening file");
							while (true)
							{
								char *fline_str = get_fline(myfile);
								if (*fline_str == NULL)//end of file
									break;

								char *token = strtok(fline_str, ",");
								if (!strcmp(third, token))
								{
									fprintf(mytempfile, "%s,", token);
									token = strtok(NULL, ",");
									fprintf(mytempfile, "%s,", token);
									token = strtok(NULL, ",");
									fprintf(mytempfile, "%s,", token);
									token = strtok(NULL, ",");
									fprintf(mytempfile, "%d\n", atoi(token) + atoi(fifth));
									free(fline_str);
								}
								else
								{
									fprintf(mytempfile, "%s,", token);
									token = strtok(NULL, ",");
									fprintf(mytempfile, "%s,", token);
									token = strtok(NULL, ",");
									fprintf(mytempfile, "%s,", token);
									token = strtok(NULL, ",");
									fprintf(mytempfile, "%s\n", token);
									free(fline_str);
								}
							}
							fclose(myfile);
							fclose(mytempfile);
							remove("seller_goods.txt");
							rename("seller_goods_temp.txt", "seller_goods.txt");
							printf("goods added!\n\n");
						}
					}
				}
				if (flag == 0) {//so good did not exist before
					(*sellersaddress)[loged_in_user_number].numofgoods++;//increase number of goods
					(*sellersaddress)[loged_in_user_number].sellers_goods = (GOOD*)realloc((*sellersaddress)[loged_in_user_number].sellers_goods, sizeof(GOOD)*(*sellersaddress)[loged_in_user_number].numofgoods);//reallocate memory for sellers_goods
					if ((*sellersaddress)[loged_in_user_number].sellers_goods == NULL)//our mallcheck function is not gonna work here so we are gonna check it without that function
					{
						printf("Malloc Error!\n\n");
						exit(EXIT_FAILURE);
					}
					(*sellersaddress)[loged_in_user_number].sellers_goods[(*sellersaddress)[loged_in_user_number].numofgoods - 1].goods_name = (char*)malloc(sizeof(char)*strlen(third));//allocate memory for goods name
					(*sellersaddress)[loged_in_user_number].sellers_goods[(*sellersaddress)[loged_in_user_number].numofgoods - 1].goods_name = third;//init goods_name
					(*sellersaddress)[loged_in_user_number].sellers_goods[(*sellersaddress)[loged_in_user_number].numofgoods - 1].seller_name = (char*)malloc(sizeof(char)*strlen(second));//allocate memory for goods name
					(*sellersaddress)[loged_in_user_number].sellers_goods[(*sellersaddress)[loged_in_user_number].numofgoods - 1].seller_name = second;//init seller_name
					(*sellersaddress)[loged_in_user_number].sellers_goods[(*sellersaddress)[loged_in_user_number].numofgoods - 1].goods_price = atoi(fourth);//init goods_price
					(*sellersaddress)[loged_in_user_number].sellers_goods[(*sellersaddress)[loged_in_user_number].numofgoods - 1].goods_count = atoi(fifth);//init goods_count
					FILE* myfile = fopen("seller_goods.txt", "a");
					if (myfile == NULL)//error opening file
						printf("Error while opening file");
					fprintf(myfile, "%s,", third);//goods_name
					fprintf(myfile, "%s,", second);//sellers_user
					fprintf(myfile, "%s,", fourth);//price
					fprintf(myfile, "%s\n", fifth);//count
					fclose(myfile);
					printf("goods added!\n\n");
				}
			}
		}
	}
}