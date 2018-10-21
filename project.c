#include<stdio.h>
#define food_item_size 20
#define special_item_size 10

struct item_details
{	char name[50];
	float price;
	int hr;
	int min;
	//int sec;
	int key;
};

struct restaurant
{	struct item_details food_items[food_item_size];
	struct item_details special_items[special_item_size];
	struct item_details special_day[7];	
	char name[100];
	char address[100];	//stores only area of the restaurant
	//int key;	optional
};

