#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
void login(char* user, char* pass, char* role, int *check, int numofseller, int numofbuyer, SELLER** sha, BUYER** bha)
{
	// sha is sellers_head_address
	// bha is buyers_head_address
	if (!strcmp(role, "seller")) {//user is seller
		SELLER* sha_temp = *sha;
		for (int i = 0;i < numofseller;i++) {//search in sellers
			sha_temp = sha_temp->next;
			if (!strcmp(user, sha_temp->username))//seller found
				if (!strcmp(pass, sha_temp->password)) {//password was right
					check[1] = i;//user Loged in   0 1 2 3 4 5 6 ...    0 is the first user after head
					check[0] = 1;//to show that this user was seller
				}
		}
	}
	else {
		BUYER* bha_temp = *bha;
		for (int i = 0;i < numofbuyer;i++) {//search in buyers
			bha_temp = bha_temp->next;
			if (!strcmp(user, bha_temp->username))//buyer found
				if (!strcmp(pass, bha_temp->password)) {//password was right
					check[1] = i;//user Loged in   0 1 2 3 4 5 6 ...    0 is the first user after head
					check[0] = 2;//to show that this user was buyer
				}
		}
	}
}