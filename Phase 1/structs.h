#ifndef STRUCTS_H_
#define STRUCTS_H_

typedef struct GOOD {
	char* seller_name = NULL;
	char* goods_name = NULL;
	int goods_price;
	int goods_count;
}GOOD;
typedef struct SELLER {
	char* username;
	char* password;
	int money;
	GOOD *sellers_goods = NULL;
	int numofgoods;//number of good's kinds
}SELLER;
typedef struct BUYER {
	char* username = NULL;
	char* password = NULL;
	int money;
	GOOD *buyers_goods = NULL;
	int numofgoods;//number of good's kinds
}BUYER;
#endif