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

#include "get_fline.h"
//Main
int main(){
	printf("Welcome to UT_KALA\n");
	int numofseller = 0;//number of sellers
	int numofbuyer = 0;//number of buyers
	BUYER* buyers = NULL;//lsit of buyers
	SELLER *sellers = NULL;//list of sellers
	int loged_in_user_number = -1;//it is a number of user in his/her role list
	int loged_in_user = 0;//1 means seller & 2 means buyer
	
	//////////////
	//Load Files//
	//////////////

	//Load sellers.txt
	FILE *myfile = fopen("sellers.txt", "r");
	if (myfile == NULL)//error opening file
		printf("Error while opening file");
	

	while (true)
	{
		char *fline_str = get_fline(myfile);
		if (*fline_str == NULL)//end of file
			break;
		char *token = strtok(fline_str, ",");
		sellers = (SELLER*)realloc(sellers, (numofseller+1)*sizeof(SELLER));//allocate memory
		sellers[numofseller].username = token;
		token = strtok(NULL, ",");
		sellers[numofseller].password = token;
		token = strtok(NULL, ",");
		sellers[numofseller].money = atoi(token);
		sellers[numofseller].numofgoods = 0;
		sellers[numofseller].sellers_goods = NULL;
		//Load seller_goods.txt
		FILE *myfile1 = fopen("seller_goods.txt", "r");
		if (myfile == NULL)//error opening file
			printf("Error while opening file");
		while (true)
		{
			char *fline_strr = get_fline(myfile1);
			if (*fline_strr == NULL)//end of file
				break;
			char *token = strtok(fline_strr, ",");
			char* token1 = strtok(NULL, ",");
			if (!strcmp(sellers[numofseller].username, token1))
			{
				sellers[numofseller].sellers_goods = (GOOD*)realloc(sellers[numofseller].sellers_goods, (sellers[numofseller].numofgoods+1)*sizeof(GOOD));//allocate memory
				sellers[numofseller].sellers_goods[sellers[numofseller].numofgoods].goods_name = token;
				sellers[numofseller].sellers_goods[sellers[numofseller].numofgoods].seller_name = token1;
				token = strtok(NULL, ",");
				sellers[numofseller].sellers_goods[sellers[numofseller].numofgoods].goods_price = atoi(token);
				token = strtok(NULL, ",");
				sellers[numofseller].sellers_goods[sellers[numofseller].numofgoods].goods_count = atoi(token);
				sellers[numofseller].numofgoods++;
			}
		}
		fclose(myfile1);
		numofseller++;
	}
	fclose(myfile);
	
	//Load buyers.txt
	myfile = fopen("buyers.txt", "r");
	if (myfile == NULL)//error opening file
		printf("Error while opening file");
	
	while (true)
	{
		char *fline_strr = get_fline(myfile);
		if (*fline_strr == NULL)//end of file
			break;
		char *token = strtok(fline_strr, ",");
		buyers = (BUYER*)realloc(buyers, (numofbuyer+1)*sizeof(BUYER));//allocate memory
		buyers[numofbuyer].username = token;
		token = strtok(NULL, ",");
		buyers[numofbuyer].password = token;
		token = strtok(NULL, ",");
		buyers[numofbuyer].money = atoi(token);
		buyers[numofbuyer].numofgoods = 0;
		buyers[numofbuyer].buyers_goods = NULL;
		//Load buyer_goods.txt
		FILE* myfile1 = fopen("buyer_goods.txt", "r");
		if (myfile == NULL)//error opening file
			printf("Error while opening file");
		while (true)
		{
			char *fline_str = get_fline(myfile1);
			if (*fline_str == NULL)//end of file
				break;
			char *token = strtok(fline_str, ",");
			if (!strcmp(buyers[numofbuyer].username, token))
			{
				buyers[numofbuyer].buyers_goods = (GOOD*)realloc(buyers[numofbuyer].buyers_goods, (sellers[numofbuyer].numofgoods + 1)*sizeof(GOOD));//allocate memory
				token = strtok(NULL, ",");
				buyers[numofbuyer].buyers_goods[buyers[numofbuyer].numofgoods].goods_name = token;
				token = strtok(NULL, ",");
				buyers[numofbuyer].buyers_goods[buyers[numofbuyer].numofgoods].seller_name = token;
				token = strtok(NULL, ",");
				buyers[numofbuyer].buyers_goods[buyers[numofbuyer].numofgoods].goods_price = atoi(token);
				token = strtok(NULL, ",");
				buyers[numofbuyer].buyers_goods[buyers[numofbuyer].numofgoods].goods_count = atoi(token);
				buyers[numofbuyer].numofgoods++;
			}
		}
		fclose(myfile1);
		numofbuyer++;
	}
	fclose(myfile);
	
	while (true) {//total loop

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
				for (int i = 0;i < numofseller;i++)
					if (!strcmp(user, sellers[i].username))
					{
						printf("Warning: this username already taken before!\n\n");
						flag = 1;//so this username taken before
						break;
					}
			}
			else if (!strcmp(role, "buyer")&!strcmp(action, "signup"))//search in buyers
			{
				for (int i = 0;i < numofbuyer;i++)
					if (!strcmp(user, buyers[i].username))
					{
						printf("Warning: this username already taken before!\n\n");
						flag = 1;//so this username taken before
						break;
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
				//signup
				signup(user, pass, role, numofseller, numofbuyer, &sellers, &buyers);
				if (!strcmp(role, "seller"))
				{
					FILE *myfile = fopen("sellers.txt", "a");
					if (myfile == NULL)//error opening file
						printf("Error while opening file");
					fprintf(myfile, "%s,", user);
					fprintf(myfile, "%s,", pass);
					fprintf(myfile, "%d\n", 0);
					fclose(myfile);
				}
				else {
					FILE *myfile = fopen("buyers.txt", "a");
					if (myfile == NULL)//error opening file
						printf("Error while opening file");
					fprintf(myfile, "%s,", user);
					fprintf(myfile, "%s,", pass);
					fprintf(myfile, "%d\n", 0);
					fclose(myfile);
				}
			}
			//login
			else if (!strcmp(action, "login"))
			{
				int check[2] = { 0,-1 };//kind of flag
				login(user, pass, role, check, numofseller, numofbuyer, &sellers, &buyers);
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
			view(&flagg,first,second ,loged_in_user,loged_in_user_number,numofseller, &sellers, &buyers);
			///////deposit <amount_of_money>
			deposit(&flagg, first, second, third, loged_in_user, loged_in_user_number, &buyers);
			/////////add_goods <user_name> <goods_name> <goods_price> <goods_count>
			add_goods(&flagg, first, second,  third,  fourth,  fifth, sixth,  loged_in_user,  loged_in_user_number,  &sellers);
			/////////show_goods
			show_goods(&flagg, first,second, numofseller, &sellers);
			/////////buy <goods_name> <goods_count> <seller_username>
			buy(&flagg, first, second, third, fourth, fifth, loged_in_user,  numofseller, loged_in_user_number, &sellers,  &buyers);
			/////////second error for wrong input format
			if (flagg == 0) {
				printf("warning: wrong input format!\n");
				free(cmdstr);//free command line
			}
		}
	}
	return 0;
}