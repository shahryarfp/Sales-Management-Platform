#include <stdio.h>
#include <stdlib.h>//used for malloc
#include <string.h>//used for strcmp & strlen
//My Functions
#include "buy.h"
#include "show_goods.h"
#include "add_goods.h"
#include "deposit.h"
#include "view.h"
#include "login.h"
#include "mallcheck.h"
#include "get_cmd.h"
#include "signup.h"
#include "remove_goods.h"
#include "change_goods_price.h"
#include "rate_goods.h"
#include "search.h"

///////////////////////////////////////////////ÊÇ ÞÓãÊ 4 ÇäÌÇã ÔÏ ÍÇáÇ ÈÇ?Ï ÞÓãÊ 4 Èå ÈÚÏ Ñæ ÇäÌÇã ÈÏ? + Ç?ä˜å È?Ç? ˜ÇáÇåÇ? ÏÇÎá ÎÑ?ÏÇÑ åÇ æ ÝÑæÔäÏå åÇÑæ åã á?ä˜ á?ÓÊ ˜ä?
//Main
int main()
{
	printf("Welcome to UT_KALA\n");
	
	//Creat linked lsit of buyers
	BUYER* buyers_head = (BUYER*)malloc(sizeof(BUYER));
	buyers_head->next = NULL;

	//Creat linked list of sellers
	SELLER* sellers_head = (SELLER*)malloc(sizeof(SELLER));
	sellers_head->next = NULL;

	int numofseller = 0;//number of sellers
	int numofbuyer = 0;//number of buyers
	int loged_in_user_number = -1;//it is a number of user in his/her role list
	int loged_in_user = 0;//1 means seller & 2 means buyer

	while (true) {//Total Loop

		//before loging in
		while (true)//loop fpr signup and login
		{
			printf("signup or login if you had account before:\n");
			char *cmdstr = get_cmd();//get command line
			// split command line and put them in strings
			char *action = strtok(cmdstr, " ");
			char *user = strtok(NULL, " ");
			char *pass = strtok(NULL, " ");
			char *role = strtok(NULL, " ");
			//find input format error
			if (action == NULL || user == NULL || pass == NULL || role == NULL || strtok(NULL, " ") != NULL)
			{
				printf("warning: wrong input format\n\n");
				free(cmdstr);//free command line
				continue;
			}
			if (strcmp(action, "signup") & strcmp(action, "login") || strcmp(role, "seller") & strcmp(role, "buyer"))
			{
				printf("warning: wrong input format\n\n");
				free(cmdstr);//free command line
				continue;
			}
			//find repeated username error
			int flag = 0;//to find if this username taken before or not
			if (!strcmp(role, "seller")&!strcmp(action, "signup"))//search in sellers
			{
				SELLER* sellers_head_temp = sellers_head;
				for (int i = 0;i < numofseller;i++)
				{
					if (!strcmp(user, sellers_head_temp->next->username))
					{
						printf("Warning: this username already taken before!\n\n");
						flag = 1;//so this username taken before
						break;
					}
					sellers_head_temp = sellers_head_temp->next;
				}
			}
			else if (!strcmp(role, "buyer")&!strcmp(action, "signup"))//search in buyers
			{
				BUYER* buyers_head_temp = buyers_head;
				for (int i = 0;i < numofbuyer;i++) {
					if (!strcmp(user, buyers_head_temp->next->username))
					{
						printf("Warning: this username already taken before!\n\n");
						flag = 1;//so this username taken before
						break;
					}
					buyers_head_temp = buyers_head_temp->next;
				}
			}
			if (flag == 1) {
				continue;//stop and get command line again
				free(cmdstr);//free command line
			}
			//signup
			if (!strcmp(action, "signup"))
			{
				if (!strcmp(role, "seller"))
					numofseller++;//increase number of sellers
				else
					numofbuyer++;//increase number of buyers
				
				signup(user, pass, role, numofseller, numofbuyer, &sellers_head, &buyers_head);
			}
			//login
			else if (!strcmp(action, "login"))
			{
				int check[2] = { 0,-1 };//kind of flag
				login(user, pass, role, check, numofseller, numofbuyer, &sellers_head, &buyers_head);
				if (check[0] == 1) {//so user is seller
					if (check[1] != -1) {//so user can login
						loged_in_user = 1;//1 means seller
						loged_in_user_number = check[1];
						printf("you loged in!\n\n");
						break;
					}
				}
				else if (check[0] == 2) {//so user is buyer
					if (check[1] != -1) {//so user can login
						loged_in_user = 2;//2 means buyer
						loged_in_user_number = check[1];
						printf("you loged in!\n\n");
						break;
					}
				}
				else {
					printf("Wrong username or password!\n\n");
					free(cmdstr);//free command line
				}

			}
		}








		////////now user loged in with known identity
		while (true)
		{
			int flagg = 0;//to check if input format is OK or not
			char *cmdstr = get_cmd();//get command line
			// split command line and put them in strings
			char *first = strtok(cmdstr, " ");
			char *second = strtok(NULL, " ");
			char *third = strtok(NULL, " ");
			char *fourth = strtok(NULL, " ");
			char *fifth = strtok(NULL, " ");
			char *sixth = strtok(NULL, " ");
			/////////first error for wrong input format
			if (first == NULL)//when user typed nothing and pressed enter
			{
				printf("warning: wrong input format\n\n");
				free(cmdstr);//free input command line
				continue;
			}
			////////logout
			if (!strcmp(first, "logout") & second == NULL)
			{
				printf("you loged out!\n\n");
				free(cmdstr);//free input command line
				break;
			}
			//////view
			view(&flagg,first,second ,loged_in_user,loged_in_user_number,numofseller, &sellers_head, &buyers_head);
			///////deposit <amount_of_money>
			deposit(&flagg, first, second, third, loged_in_user, loged_in_user_number, &buyers_head);
			/////////add_goods <user_name> <goods_name> <goods_price> <goods_count>
			add_goods(&flagg, first, second,  third,  fourth,  fifth, sixth,  loged_in_user,  loged_in_user_number,  &sellers_head);
			/////////show_goods
			show_goods(&flagg, first,second, numofseller, &sellers_head);
			/////////buy <goods_name> <goods_count> <seller_username>
			buy(&flagg, first, second, third, fourth, fifth, loged_in_user,  numofseller, loged_in_user_number, &sellers_head,  &buyers_head);
			/////////remove_goods <goods_name>
			remove_goods(&flagg, first, second, third, loged_in_user, loged_in_user_number, &sellers_head);
			/////////change_goods_price <goods_name> <new_price>
			change_goods_price(&flagg, first, second, third, fourth,loged_in_user, loged_in_user_number, &sellers_head);
			/////////rate_goods <goods_name> <seller_username> <rating>
			rate_goods(&flagg, first, second, third, fourth,fifth, loged_in_user, numofseller,loged_in_user_number, &sellers_head, &buyers_head);
			/////////search <number_of_conditions> ==> good_name, seller_username, min_price, max_price
			search(&flagg, first, second, third, numofseller, &sellers_head);
			/////////second error for wrong input format
			if (flagg == 0){
				printf("warning: wrong input format!\n");
				free(cmdstr);//free command line
			}
		}
	}


	return 0;
}