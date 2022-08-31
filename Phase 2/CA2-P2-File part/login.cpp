#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
void login(char* user, char* pass, char* role, int *check, int numofseller, int numofbuyer, SELLER** sellersaddress, BUYER** buyersaddress)
{
	if (!strcmp(role, "seller")) {//user is seller
		for (int i = 0;i < numofseller;i++)//search in sellers
			if (!strcmp(user, (*sellersaddress)[i].username))//seller found
				if (!strcmp(pass, (*sellersaddress)[i].password)) {//password was right
					check[1] = i;//user Loged in
					check[0] = 1;//to show that this user was seller
				}
	}
	else
		for (int i = 0;i < numofbuyer;i++)//search in buyers
			if (!strcmp(user, (*buyersaddress)[i].username))//buyer found
				if (!strcmp(pass, (*buyersaddress)[i].password)) {//password was right
					check[1] = i;//user Loged in
					check[0] = 2;//to show that this user was buyer
				}
}