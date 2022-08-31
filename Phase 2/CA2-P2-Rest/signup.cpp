#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "signup.h"

void signup(char *user, char *pass, char *role, int numofseller, int numofbuyer, SELLER** sha, BUYER** bha)
{
	// sha is sellers_head_address
	// bha is buyers_head_address
	if (!strcmp(role, "seller"))//user is seller
	{
		SELLER* new_node = (SELLER*)malloc(sizeof(SELLER));//reallocate memory
		SELLER* sha_temp = *sha;
		for (int i = 0;i < numofseller-1;i++) {
			sha_temp = sha_temp->next;
		}
		sha_temp->next = new_node;
		new_node->username = (char*)malloc(sizeof(char)*strlen(user));//allocate memory
		new_node->username = user;//init username
		new_node->password= (char*)malloc(sizeof(char)*strlen(pass));//allocate memory
		new_node->password = pass;//init password
		new_node->money = 0;//init money
		new_node->numofgoods = 0;//init number of goods

		//Creat linked list of sellers_goods
		GOOD* sellers_goods_head = (GOOD*)malloc(sizeof(GOOD));
		sellers_goods_head->next = NULL;
		new_node->sellers_goods = sellers_goods_head;

		new_node->next = NULL;
		printf("user signed up!\n\n");
	}
	else
	{
		BUYER* new_node = (BUYER*)malloc( sizeof(BUYER));//reallocate memory
		BUYER* bha_temp = *bha;
		for (int i = 0;i < numofbuyer-1;i++) {
			bha_temp = bha_temp->next;
		}
		bha_temp->next = new_node;
		new_node->username = (char*)malloc(sizeof(char)*strlen(user));//allocate memory
		new_node->username = user;//init username
		new_node->password = (char*)malloc(sizeof(char)*strlen(pass));//allocate memory
		new_node->password = pass;//init passwprd
		new_node->money = 0;//init money
		new_node->numofgoods = 0;//init number of goods
		
		//Creat linked list of buyers_goods
		GOOD* buyers_goods_head = (GOOD*)malloc(sizeof(GOOD));
		buyers_goods_head->next = NULL;
		new_node->buyers_goods = buyers_goods_head;

		new_node->next = NULL;
		printf("user signed up!\n\n");
	}
}