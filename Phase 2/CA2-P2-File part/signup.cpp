#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "signup.h"

void signup(char *user, char *pass, char *role, int numofseller, int numofbuyer, SELLER** sellersaddress, BUYER** buyersaddress)
{
	if (!strcmp(role, "seller"))//user is seller
	{
		*sellersaddress = (SELLER*)realloc(*sellersaddress, numofseller*sizeof(SELLER));//reallocate memory
		(*sellersaddress)[numofseller - 1].username = (char*)malloc(sizeof(char)*strlen(user));//allocate memory
		(*sellersaddress)[numofseller - 1].username = user;//init username
		(*sellersaddress)[numofseller - 1].password= (char*)malloc(sizeof(char)*strlen(pass));//allocate memory
		(*sellersaddress)[numofseller - 1].password = pass;//init password
		(*sellersaddress)[numofseller - 1].money = 0;//init money
		(*sellersaddress)[numofseller - 1].numofgoods = 0;//init number of goods
		(*sellersaddress)[numofseller - 1].sellers_goods = NULL;
		printf("user signed up!\n\n");
	}
	else
	{
		*buyersaddress = (BUYER*)realloc(*buyersaddress, numofbuyer*sizeof(BUYER));//reallocate memory
		(*buyersaddress)[numofbuyer - 1].username = (char*)malloc(sizeof(char)*strlen(user));//allocate memory
		(*buyersaddress)[numofbuyer - 1].username = user;//init username
		(*buyersaddress)[numofbuyer - 1].password = (char*)malloc(sizeof(char)*strlen(pass));//allocate memory
		(*buyersaddress)[numofbuyer - 1].password = pass;//init passwprd
		(*buyersaddress)[numofbuyer - 1].money = 0;//init money
		(*buyersaddress)[numofbuyer - 1].numofgoods = 0;//init number of goods
		(*buyersaddress)[numofbuyer - 1].buyers_goods = NULL;
		printf("user signed up!\n\n");
	}
}