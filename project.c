#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define food_item_size 20
#define special_item_size 10
#define restaurant_size 10
#define live_order_size 10
struct item_details
{    char name[50];
    float price;
    //int hr;
    int min;/*service time*/
    //int sec;
    int key;
    
};

struct live_order_details
{    int order_time;
    char username[100];
    char user_address[20];
    int user_phone;
    int item_size;
    char order_item[5][20];
    int qty[5];
    int delivery_time;
    int order_id;
    int service_time;
};

struct restaurant_details
{    struct item_details food_items[food_item_size];
    struct item_details special_items[special_item_size];
    struct item_details special_day;/*28th 4pm*/
    char name[100];
    char address[100];    //stores only area of the restaurant
    //int key;    optional
    int total_items;    //************
    int total_special_items; /****25 oct*/
    int delivery_time;/*****26 oct*/
    struct live_order_details live_order[10];
    int order_size;
    struct live_order_details history[10];
    int total_order;
    
}restaurant[restaurant_size];


int count_restaurant=0;
int key_restaurant[restaurant_size];
enum status
{    FAILURE,
    SUCCESS
};
void key_initialisation(void);
void closeOrder(void);
int special_index(char item_name[],int rest_index);/******/
void add_db(char rest_name[],char address[],char food1[],char food2[],char sp1[],char sp2[],float p1,float p2,float spr1,float spr2,int t1,int t2,int st1,int st2,int rest_no,char day_special[],float day_price,int day_time,int d_time);
void display_restaurant(void);
void sort_restaurant(int size);
void addRestaurant(void);
void deleteRestaurant(void);
void addItem(void);
void deleteItem(void);
void updateItem(void);
void getRestauarantInArea(void);
void getTime(void);
int getMinTime(void);
void restaurant_enteries(void);
void getItemAvailability(char item_name[]);
void getItemOfDayListInSortedOrder(void);

int restaurant_index(char name[],char address[]);/*returns index at which restaurant found in restaurant array else returns -1*/
int item_index(char item_name[],int rest_index);/*returns index value of item in rest records else -1*/

void delivery_time(void);
void trackOrder(void);
void initialise(void);
int serviceTimeAssign(char restaurant_name[],char item_name[]);
int calc_time_lapsed(int previous_time,int current_time);
void getItemListInAreaSortedOrder(void);
void char_arr_sort(struct item_details str[],int size);
void getCommonItem(void);//new
void sort_list_key(char a[20][100],int key[],int size);
void getCommonSpecialItem(void);
void getAllUniqueItem(void);
void getAllSpecialItemListInSortedOrder(void);
int time_to_min(int hr,int min);
void placeOrder(void);
void display_item(struct item_details list[],int size);
void getItemListInSortedOrder(void);
void getSpecialItemListInSortedOrder(void);
void FindOrderAssignment(void);

int main()
{    int flag=1;
    int choice;
    key_initialisation();
    initialise();
    restaurant_enteries();/*****/
    /*have  modified the switch and added case 0 for exiting*/
    /*use char for switch??*/
    while (flag==1)
    {
        printf("\n\n\n\n--------------------------------------------------------------------------------\nMAIN MENU:\n--------------------------------------------------------------------------------\n1.ADD RESTAURANT\n2.DELETE RESTAURANT\n3.ADD ITEM\n4.DELETE ITEM\n5.UPDATE\n6.GET RESTAURANT IN AREA\n7.GET TIME \n8.GET MINIMUM TIME\n9.GET ITEM AVAILABILITY\n10.PLACE ORDER\n11.TRACK ORDER\n12.CLOSE ORDER\n13.GET ITEM LIST IN SORTED ORDER\n14.GET ITEMLIST IN AREA SORTED ORDER\n15.GET SPECIAL ITEM LIST IN SORTED ORDER\n16.GET ALL SPECIAL ITEM LIST IN SORTED ORDER\n17.GET ITEM OF DAY LIST IN SORTED ORDER\n18.GET COMMON ITEM\n19.GET COMMON SPECIAL ITEM\n20.GET ALL UNIQUE ITEM\n21.FIND ORDER ASSIGNMENT\nENTER YOUR CHOICE : ");
        scanf("%d",&choice);
        switch(choice)
        {   case 1:{addRestaurant();
                    break;
                        }
            case 2:{deleteRestaurant();
                break;}
            case 3:{addItem();
                break;}
	    case 4:{deleteItem();
                break;}
            case 5:{updateItem();
                break;}
            case 6:{getRestauarantInArea();
                break;}
            case 7:{getTime();
                break;}
            case 8:{int t=getMinTime();
                break;}
            case 9:{
                char item_name[20];
                printf("\n Enter the item you wish to check availabilty for :");
                scanf("%s",item_name);
                getItemAvailability(item_name);
                break;
            }
	    case 10:{placeOrder();
                break;}
	    case 11:{trackOrder();
                break;}
	    case 12:{closeOrder();
                break;}
	    case 13:{getItemListInSortedOrder();
                break;}
	    case 14:{getItemListInAreaSortedOrder();
                break;}
	    case 15:{getSpecialItemListInSortedOrder();
                break;}
	    case 16:{getAllSpecialItemListInSortedOrder();
                break;}
	    case 17:{getItemOfDayListInSortedOrder();
                break;}
	    case 18:{getCommonItem();
                break;}
	    case 19:{getCommonSpecialItem();
                break;}
	    case 20:{getAllUniqueItem();
                break;}
	    case 21:{FindOrderAssignment();
                break;}
            case 0:
            {printf("\n\nAre you sure you wish to leave? \n press 1 if you wish to continue \n press 0 if you wish to exit : ");
                scanf("%d",&flag);
                if(flag==0)
                {
                    printf("\n\nThank you for visiting!\n\n");
                }else
                {
                    printf("!!Please choose another option to continue browsing !!\n");
                }break;
                
            }
                
            default:printf("please select a valid choice and please be sure to use lowercase letters  or press 0 to exit\n");break;
        }
    }
    return 0;
    
}
void key_initialisation()
{    int i;
    for(i=0;i<restaurant_size;i++)
    {    key_restaurant[i]=i;
    	 
    }
}

void add_db(char rest_name[],char address[],char food1[],char food2[],char sp1[],char sp2[],float p1,float p2,float spr1,float spr2,int t1,int t2,int st1,int st2,int rest_no,char day_special[],float day_price,int day_time,int d_time)
{
    strcpy(restaurant[rest_no].name,rest_name);
    strcpy(restaurant[rest_no].address,address);
    strcpy(restaurant[rest_no].food_items[0].name,food1);
    strcpy(restaurant[rest_no].food_items[1].name,food2);
    strcpy(restaurant[rest_no].special_items[0].name,sp1);
    strcpy(restaurant[rest_no].special_items[1].name,sp2);
    restaurant[rest_no].food_items[0].price=p1;
    restaurant[rest_no].food_items[0].min=t1;
    restaurant[rest_no].food_items[1].price=p2;
    restaurant[rest_no].food_items[1].min=t2;
    restaurant[rest_no].special_items[0].price=spr1;
    restaurant[rest_no].special_items[0].min=st1;
    restaurant[rest_no].special_items[1].price=spr2;
    restaurant[rest_no].special_items[1].min=st2;
	strcpy(restaurant[rest_no].special_day.name,day_special);
	restaurant[rest_no].special_day.price=day_price;
	restaurant[rest_no].special_day.min=day_time;
    count_restaurant++;
    restaurant[rest_no].total_items=restaurant[rest_no].total_items+2;
    restaurant[rest_no].total_special_items=restaurant[rest_no].total_special_items+2;
    restaurant[rest_no].delivery_time=d_time;
    
}

void display_restaurant()
{    int i;
    for(i=0;i<count_restaurant;i++)
    {    printf("%s \n",restaurant[key_restaurant[i]].name);
    }
}


void sort_restaurant(int size)
{    int i,pos=0;
    for(i=0;(strcmp(restaurant[count_restaurant].name,restaurant[key_restaurant[i]].name)>0)&&(i<count_restaurant);i++)
    {    pos++;
    }
    if((strcmp(restaurant[count_restaurant].name,restaurant[i].name)==0)&&(i<count_restaurant))
    {    if(strcmp(restaurant[count_restaurant].address,restaurant[key_restaurant[i]].address)>0)
    {    pos++;
    }
    }
    
    for(i=size;i>pos;i--)
    {    key_restaurant[i]=key_restaurant[i-1];
    }
    key_restaurant[pos]=count_restaurant;
}
void addRestaurant()
{    int item_no,found=0,i,special=0,item_num1,item_num2;
    printf("NAME : ");
    scanf(" %s",restaurant[count_restaurant].name);
    printf("ADDRESS ( AREA ) : ");
    scanf(" %s",restaurant[count_restaurant].address);
    printf("ENTER THE DELIVERY TIME OF THE RESTAURANT : ");
    scanf("%d",&restaurant[count_restaurant].delivery_time);
    printf("ENTER NO OF ITEMS TO BE ENTERED : ");
    scanf("%d",&item_no);
    for(i=1;i<=item_no;i++)/*initialised i with 1 and changed index to i-1 */
    {    printf("ENTER DETAILS OF ITEM NO %d : ",i);
        printf("\nNAME : ");
        scanf(" %s",restaurant[count_restaurant].food_items[i-1].name);
        printf("PRICE : ");
        scanf("%f",&restaurant[count_restaurant].food_items[i-1].price);
        printf("TIME : ");
        scanf("%d",&restaurant[count_restaurant].food_items[i-1].min);
        restaurant[count_restaurant].food_items[i-1].key=i-1;
	printf("\nIf you wish to add item to special menu press 1 else 0 : ");
    	scanf("%d",&special);
    	if (special==1)
	{	item_num1=restaurant[count_restaurant].total_special_items;
        	strcpy(restaurant[count_restaurant].special_items[i-1].name,restaurant[count_restaurant].food_items[item_num1].name);
		restaurant[count_restaurant].special_items[item_num1].price=restaurant[count_restaurant].food_items[i-1].price;
		restaurant[count_restaurant].special_items[item_num1].min=restaurant[count_restaurant].food_items[i-1].min;
		restaurant[count_restaurant].total_special_items++;
        	printf("\n!!Item has been added to special item menu!!\n");
        }
        restaurant[count_restaurant].total_items++;
    }
    
    found=1;
    if(count_restaurant>1)
        sort_restaurant(count_restaurant);
    count_restaurant++;
    if(found==1)
        printf("RESTAURANT ADDED \n");
    else
        printf("ERROR");
    display_restaurant();
    
    
}

void deleteRestaurant()
{    char delete_name[100],delete_area[100];
    int i,found=0,pos=-1,key_pos=-1,j;
    printf("ENTER THE RESTAURANT NAME : ");
    scanf("%s",delete_name);
    printf("ENTER AREA : ");
    scanf("%s",delete_area);
    for(i=0;i<count_restaurant;i++)
    {    if((strcmp(restaurant[i].name,delete_name)==0)&&(strcmp(restaurant[i].address,delete_area)==0))
    {    pos=i;
        found=1;
    }
    }
    if(found==0)
    {    printf("NOT FOUND THE RESTAURANT!!\n");
    }
    else
    {
        for(i=pos;i<count_restaurant-1;i++)
        {   restaurant[i]=restaurant[i+1]; 
        	
           
        }
        for(i=0;key_restaurant[i]!=pos;i++)
            key_pos++;
        for(i=key_pos;i<count_restaurant;i++)
            key_restaurant[i]=key_restaurant[i+1];
        for(i=0;i<count_restaurant;i++)
        {    if(key_restaurant[i]>pos)
        {    key_restaurant[i]--;
        }
        }
        count_restaurant--;
        printf("DELETED THE GIVEN RESTAURANT ");
    }
}

/*c*/
void addItem()
{
    char restaurant_name[50],item_name[50],restaurant_address[50];
    int i,flag=0,item_num1 = 0,item_num2,pos = 0,special=0,special_day=0;
    printf("ENTER THE NAME OF THE RESTAURANT : ");
    scanf("%s",restaurant_name);
    printf("ENTER THE ADDRESS OF THE RESTAURANT : ");
    scanf("%s",restaurant_address);
    for(i=0;(i<count_restaurant)&&(flag==0);i++)
    {    if((strcmp(restaurant[i].name,restaurant_name)==0)&&(strcmp(restaurant[i].address,restaurant_address)==0))
    {
        item_num1=restaurant[i].total_items;
        if (item_num1<food_item_size)
        {
            /**<= ?*/
            pos=i;
            printf("ENTER NEW ITEM NAME :");
            scanf("%s",item_name);
            strcpy(restaurant[i].food_items[item_num1].name,item_name);
            printf("ENTER PRICE OF %s :",restaurant[i].food_items[item_num1].name);
            scanf("%f",&restaurant[i].food_items[item_num1].price);
            printf("ENTER SERVICE TIME IN MINUTES : ");
            scanf("%d",&restaurant[i].food_items[item_num1].min);
            restaurant[i].total_items++;
            flag=1;
        }
        
        
    }
        
    }
    if (flag==1) {
        printf("\nItem has been added succesfully!! \n");
    }
    else{
        printf("!!Failed to add item as restaurant not found or size limit exceeed !!\n");
    }
    printf("\nIf you wish to add item to special menu press 1 else 0 : ");
    scanf("%d",&special);
    if (special==1&&flag==1) {
        item_num2=restaurant[pos].total_special_items;
        restaurant[pos].special_items[item_num2]=restaurant[pos].food_items[item_num1];
        restaurant[pos].total_special_items++;
        printf("!!Item has been added to special item menu!!");
        
    }
    
     printf("If you wish to add item to special item of the day press 1 else 0 : ");
    scanf("%d",&special_day);
    if (special_day==1&&flag==1) {
        
        restaurant[pos].special_day,restaurant[pos].food_items[item_num1];
        
        printf("\n!!Item has been added as special item of the day !!\n");
        
    }
    
}

void deleteItem()
{   printf("ENTER THE NAME OF THE RESTAURANT : ");
    char restaurant_name[20],item_name[20],restaurant_address[20];
    scanf("%s",restaurant_name);
    printf("ENTER THE RESTAURANT ADDRESS : ");
    scanf("%s",restaurant_address);
    printf("ENTER THE FOOD ITEM YOU NEED TO DELETE : ");
    scanf("%s",item_name);
    int i,j,k;
    i=restaurant_index(restaurant_name, restaurant_address);
    if (i!=(-1))
    {
        j=item_index(item_name, i);
        if (j!=(-1))
        {
            for (k=j; k<restaurant[i].total_items-1; k++)
            {
                restaurant[i].food_items[k]=restaurant[i].food_items[k+1];
            }
            j=special_index(item_name,i);
            {
                if (j!=(-1))
                {
                    for (k=j; k<restaurant[i].total_special_items-1; k++)
                    {
                        restaurant[i].special_items[k]=restaurant[i].special_items[k+1];
                    }
                }
            }
            if(strcmp(restaurant[i].special_day.name, item_name))
            {
                restaurant[i].special_day.name[0]='\0';
            }
            printf("\n!!Item successfully deleted!!");
        }else{
            printf(" \n!!Item not found!! \n");
        }
    }else{
        printf("\n!!Restaurant not found!! \n");
    }
}


void updateItem()
{    char update_name[100],update_address[100],update_fname[100],original_fname[100];
    float update_fprice;
    int i,/*pos=-1???remove if not required*/j,flag=0,found;
    printf("ENTER THE NAME OF THE RESTAURANT : ");
    scanf(" %s",update_name);
    printf("ENTER THE ADDRESS OF THE RESTAURANT : ");
    scanf(" %s",update_address);
    for(i=0;(i<count_restaurant)&&(flag==0);i++)
    {   if((strcmp(restaurant[i].name,update_name)==0)&&(strcmp(restaurant[i].address,update_address)==0))
    	  {    printf("THE FOOD ITEMS IN THE ABOVE RESTAURANT ARE : \n");
        for(j=0;j<restaurant[i].total_items;j++)
        {    printf(" %s   Rs %f   %d \n",restaurant[i].food_items[j].name,restaurant[i].food_items[j].price,restaurant[i].food_items[j].min);
            
        }
        printf("ENTER THE FOOD ITEM NAME TO BE MODIFIED : ");
        scanf("%s",original_fname);
        printf("ENTER THE MODIFIED FOOD ITEM NAME : ");
        scanf("%s",update_fname);
        printf("ENTER THE MODIFIED FOOD ITEM PRICE : ");
        scanf("%f",&update_fprice);
        found=0;
        for(j=0;(j<restaurant[i].total_items)&&(found==0);j++)
        {    if(strcmp(restaurant[i].food_items[j].name,original_fname)==0)
        {    strcpy(restaurant[i].food_items[j].name,update_fname);
            restaurant[i].food_items[j].price=update_fprice;
            found=1;
        }
        }
        for(j=0;j<restaurant[i].total_special_items;j++)
        {    if(strcmp(restaurant[i].special_items[j].name,original_fname)==0)
        {    strcpy(restaurant[i].special_items[j].name,update_fname);
            restaurant[i].special_items[j].price=update_fprice;
        }
        }
        if(found==0)
            printf("NOT FOUND THE FOOD ITEM!!");
       
        flag=1;
    }
    }
    if(flag==0)
        printf("NOT FOUND THE RESTAURANT WITH THE GIVEN DETAILS ");
    else if(found!=0)
    {    printf("MODIFIED\n");                //doubt how to use key and index ????????????
        //getItemListInSortedOrder(i-1);            //send the index of restaurant to the function so that food items of that particular restaurant is sorted
    }
}

void getRestauarantInArea()
{
    char area[20];
    int i,found=0;
    char *s ;
    printf("Enter the area name where you wish to find restaurant \n Area:");
    scanf("%s",area);
    for(i=0;i<(i<count_restaurant);i++)
    {
        s=strstr(restaurant[i].address, area);
        if (*s!='\0')
        {
            printf("%s \n",restaurant[i].name);
            found++;
        }
    }
    if (found==0) {
        printf("No restaurants with given area! \n Check address input and try again\n");
    }
}

void getTime()
{
    char item_name[20],address[20],rest_name[20];
    int quantity,flag1=0,flag2=0,i=0,j=0,total_time=0;
    printf("\n Enter the restaurant name:");
    scanf("%s",rest_name);
    printf("\n Address:");
    scanf("%s",address);
    printf("\n Item name:");
    scanf("%s",item_name);
    printf("Quantity:");
    scanf("%d",&quantity);
    
    for (i=0; i<count_restaurant&&flag1==0; i++)
    {
        if ((strcmp(rest_name,restaurant[i].name)==0)&&strcmp(address, restaurant[i].address)==0)
        {
            flag1=1;
            for (j=0; j<restaurant[i].total_items&&flag2==0; j++)
            {
                if (strcmp(restaurant[i].food_items[j].name, item_name)==0)
                {
                    total_time=restaurant[i].food_items[j].min+restaurant[i].delivery_time;/**does quantity affect time???*/
                    flag2=1;
                }
            }
            if (flag2==0)
            {
                printf("The given item was not found . Please check item name and try again \n");
            }
            else
            {
                printf("The total delivery time is \n %d \n service time: %d + \n transit time: %d",total_time,restaurant[i].food_items[j].min,restaurant[i].delivery_time);
            }
        }
        if (flag1==0)
        {
            printf("The given restaurant was not found . Please check restaurant name and address and try again \n");
        }
    }
}


int getMinTime()
{    char food_item[100];
    int qty,min=restaurant[0].food_items[0].min+restaurant[0].delivery_time,i,posi = 0,posj = 0,j;
    printf("ENTER THE NAME OF THE FOOD ITEM : ");
    scanf("%s",food_item);
    printf("ENTER THE QUANTITY REQUIRED : ");
    scanf("%d",&qty);
    for(i=0;i<count_restaurant;i++)
    {    for(j=0;j<restaurant[i].total_items;j++)
    {    if((strcmp(restaurant[i].food_items[j].name,food_item)==0)&&(restaurant[i].food_items[j].min+restaurant[i].delivery_time<min))
    {    min=restaurant[i].food_items[j].min+restaurant[i].delivery_time;
        posi=i;
        posj=j;
    }
    }
    }
    printf("NAME OF THE RESTAURANT : %s \nADDRESS : %s \nDELIVERY TIME : %d \n ",restaurant[posi].name,restaurant[posi].address,restaurant[posi].food_items[posj].min+restaurant[posi].delivery_time);
    //delivery time calculation remaining just for now service time is considered
    return posi;
}

void getItemAvailability(char item_name[])
{
    int i,j,found=0;
    for (i=0; i<count_restaurant; i++)
    {
        j=item_index(item_name, i);
        if(j!=(-1))
        {
            found++;
            printf("\n Item available at Restaurant %s \t Price:%f",restaurant[i].name,restaurant[i].food_items[j].price);
        }
    }
    if(found==(-1))
    {
        printf("\nItem not available at any restaurant.");
    }
}


int restaurant_index(char name[],char address[])
{
    int i,found=-1;
    for (i=0; i<count_restaurant&&found==(-1); i++) {
        if ((strcmp(name, restaurant[i].name)==0)&&(strcmp(address, restaurant[i].address)==0)) {
            found=i;
            
        }
    }
    return found;
    
}
//new
int item_index(char item_name[],int rest_index)
{
    int i,found=-1;
    for (i=0; (i<restaurant[rest_index].total_items)&&found==(-1); i++) {
        if (strcmp(item_name, restaurant[rest_index].food_items[i].name)==0) {
            found=i;
        }
    }
    return found;
}


void restaurant_enteries()
{
    add_db("curry_house","lakshminagar","roti","biryani","roti","biryani",30,200,30,200,5,15,5,15,0,"biryani",200,15,30);
    
    add_db("desi_kitchen","mate_square","sandwiches","nuggets","sandwiches","nuggets",100,80,100,80,15,25,15,25,1,"nuggets",80,25,15);
    
     add_db("foodvilla","bajaj_nagar","burger","noodles","burger","noodles",60,30,60,30,10,10,10,10,2,"noodles",30,10,20);
    
    add_db("reds","sadar","paneer","chicken","paneer","chicken",100,150,100,150,15,20,15,20,3,"chicken",150,20,30);

}

void trackOrder()
{   int id;
    printf("ENTER THE ORDER ID THAT NEED TO BE TRACKED : ");
    scanf("%d",&id);
    int i,j,pos=-1,current_time_hr,current_time_min,time_lapsed=0,flag=0,current_time;
    char name[100];
    printf("ENTER THE NAME OF RESTAURANT : ");
    scanf("%s",name);
    printf("ENTER THE CURRENT TIME : \nhr :");
    scanf("%d",&current_time_hr);
	printf("minutes : ");
	scanf("%d",&current_time_min);
	current_time=time_to_min(current_time_hr,current_time_min);

		
    
    for(i=0;i<count_restaurant;i++)
    {    if(strcmp(restaurant[i].name,name)==0)
    {    pos=i;
    }
    }
    if(pos==-1)
        printf("RESTAURANT NOT FOUND ");
    else
    {   
    	for(j=0;(j<restaurant[pos].order_size)&&(flag==0);j++)            //10 is the max size of live order
    {   
    	if(restaurant[pos].live_order[j].order_id==id)
    {    time_lapsed=calc_time_lapsed(restaurant[pos].live_order[j].order_time,current_time);    //max service time to be calculated
        if(time_lapsed<restaurant[pos].live_order[j].service_time)
            printf("STATUS : IN PREPARATION");
        else if((time_lapsed>=restaurant[pos].live_order[j].service_time)&&(time_lapsed<restaurant[pos].live_order[j].delivery_time))
            printf("STATUS : OUT FOR DELIVERY");
        else if(time_lapsed>=restaurant[pos].live_order[j].delivery_time)
            printf("STATUS : DELIVERED ");
        flag=1;
    }
    else
    {	printf("ORDER ID NOT FOUND!!");
    }
    }
    }
}

void closeOrder()
{	char name[100],address[100];
	printf("ENTER THE NAME OF RESTAURANT : ");
	scanf("%s",name);
	printf("ENTER THE ADDRESS : ");
	scanf("%s",address);
	int index=restaurant_index(name,address);
	printf("ENTER THE ORDER ID WHICH HAS TO BE CLOSED : ");
	int id,i,j,k=0,pos,found=0;
	scanf("%d",&id);
	if(index!=-1)
	{
	for(i=0;i<10;i++)
	{	if(restaurant[index].live_order[i].order_id==id)
		{	pos=i;
			found=1;
			restaurant[index].history[k]=restaurant[index].live_order[pos];
			k++;
			for(j=pos;j<restaurant[index].order_size;j++)
			{	
				restaurant[index].live_order[j]=restaurant[index].live_order[j+1];
			}
			
		}
	}
	if(found==0)
		printf("ORDER ID NOT FOUND IN THE GIVEN RESTAURANT !!!");
	else
		printf("THE GIVEN ORDER IS CLOSED\n ");
	}
	else
		printf("RESTAURANT NOT FOUND!!!");
		
	
}

int calc_time_lapsed(int previous_time,int current_time)
{    int ans;
    ans=current_time-previous_time;
    return ans;
}




void initialise()
{    int i;
    for(i=0;i<restaurant_size;i++)
    {    restaurant[i].order_size=0;
        restaurant[i].total_items=0;
        restaurant[i].total_special_items=0;
        restaurant[i].total_order=0;
    }
    
}

int serviceTimeAssign(char restaurant_name[],char item_name[])
{    int i,j,pos=-1,ans = 0;
    for(i=0;i<count_restaurant;i++)
    {    if(strcmp(restaurant[i].name,restaurant_name)==0)
    {    pos=i;
    }
    }
    for(j=0;j<restaurant[pos].total_items;i++)
    {    if(strcmp(restaurant[pos].food_items[i].name,item_name)==0)
    {    ans=restaurant[pos].food_items[i].min;
    }
    }
    return ans;
}

void getItemListInAreaSortedOrder()
{    printf("ENTER THE AREA : ");
    char area[100]/*a[50][100]*/;
    scanf("%s",area);
    int i,j=0;
    
    for(i=0;i<count_restaurant;i++)
    {   
    		if(strcmp(restaurant[key_restaurant[i]].address,area)==0)
    {    printf("RESTAURANT NAME : %s\n",restaurant[key_restaurant[i]].name);
        for(j=0;j<restaurant[key_restaurant[i]].total_items;j++)
        {    printf("%d.%s\n",j+1,restaurant[key_restaurant[i]].food_items[j].name);
        }
        printf("\n\n");
    }
    }
}


void char_arr_sort(struct item_details str[],int size)/*28th 5 pm*/
{
    
    int i, j;
    struct item_details key;
    for (i = 1; i < size; i++)
    {
        key=str[i];
        j = i-1;
        while (j >= 0 && strcmp(str[j].name,key.name)>=0)
        {
            if (strcmp(str[j].name,key.name)>0)
            {
                str[j+1]=str[j];
                j = j-1;
            }
            else if (strcmp(str[j].name,key.name)==0&&str[j].price>key.price)
            {
                str[j+1]=str[j];
                j = j-1;
                
            }
        }
        str[j+1]=key;
    }

}

int time_to_min(int hr,int min)
{
    return hr*60+min;
    
}
//new
void getCommonItem()
{	printf("ENTER NO OF RESTAURANTS : ");
	int size,i,j,k,flag=0,list[restaurant_size];
	float price[restaurant_size];	
	char a[restaurant_size][100];
	scanf("%d",&size);
	printf("ENTER THE LIST OF RESTAURANTS WHOSE SPECIAL ITEMS NEED TO BE SORTED : ");
	for(i=0;i<size;i++)
	{	scanf("%s",a[i]);
	}
	for(i=0;i<size;i++)
	{	flag=0;
		for(j=0;(j<count_restaurant)&&(flag==0);j++)
		{	if(strcmp(a[i],restaurant[key_restaurant[j]].name)==0)
			{	list[i]=key_restaurant[j];
				flag=1;
			}
		}
	}
	int count=1;
	for(i=0;i<restaurant[list[0]].total_items;i++)
	{	for(j=1;j<size;j++)
		{	
			for(k=0;k<restaurant[list[j]].total_items;k++)
			{	if(strcmp(restaurant[list[j]].food_items[k].name,restaurant[list[0]].food_items[i].name)==0)
				{	count++;
					price[j]=restaurant[list[j]].food_items[k].price;
				}
			}
		}
		if(count==size)
			{	printf("%s \n%d \t %f\n",restaurant[list[0]].food_items[i].name,1,restaurant[list[0]].food_items[i].price);
				for(j=1;j<size;j++)
				{	printf("%d. \t %f \n",j+1,price[j]);
				}
			}
		count=1;
	}
}	
void getCommonSpecialItem()
{	printf("ENTER NO OF RESTAURANTS : ");
	int size,i,j,k,flag=0,list[restaurant_size];
	float price[restaurant_size];	
	char a[restaurant_size][100];
	scanf("%d",&size);
	printf("ENTER THE LIST OF RESTAURANTS WHOSE SPECIAL ITEMS NEED TO BE SORTED : ");
	for(i=0;i<size;i++)
	{	scanf("%s",a[i]);
	}
	for(i=0;i<size;i++)
	{	flag=0;
		for(j=0;(j<count_restaurant)&&(flag==0);j++)
		{	if(strcmp(a[i],restaurant[key_restaurant[j]].name)==0)
			{	list[i]=key_restaurant[j];
				flag=1;
			}
		}
	}
	int count=1;
	for(i=0;i<restaurant[list[0]].total_special_items;i++)
	{	for(j=1;j<size;j++)
		{	
			for(k=0;k<restaurant[list[j]].total_special_items;k++)
			{	if(strcmp(restaurant[list[j]].special_items[k].name,restaurant[list[0]].special_items[i].name)==0)
				{	count++;
					price[j]=restaurant[list[j]].special_items[k].price;
				}
			}
		}
		if(count==size)
			{	printf("%s \n%d \t %f\n",restaurant[list[0]].special_items[i].name,1,restaurant[list[0]].special_items[i].price);
				for(j=1;j<size;j++)
				{	printf("%d \t %f \n",j+1,price[j]);
				}
			}
		count=1;
	}
}

void sort_list_key(char a[20][100],int key[],int size)
{	int i,sorted=0,temp1,j;
	char temp[100];
	for(j=0;(j<size-1)&&(sorted==0);j++)
	{	sorted=1;
		for(i=1;i<size-j;i++)
		{	if(strcmp(a[i],a[i-1])<0)
			{	strcpy(temp,a[i]);
				strcpy(a[i],a[i-1]);
				strcpy(a[i-1],temp);
				temp1=key[i];
				key[i]=key[i-1];
				key[i-1]=temp1;
				sorted=0;
			}
		}
	}
}

void getAllUniqueItem()
{	printf("ENTER NO OF RESTAURANTS : ");
	int size,i,j,k,flag=0,list[restaurant_size],p,l=0,key_unique[20];
	char a[restaurant_size][100],temp[20][100];
	scanf("%d",&size);
	printf("ENTER THE LIST OF RESTAURANTS WHOSE UNIQUE ITEMS NEED TO BE SEARCHED AND SORTED : ");
	for(i=0;i<size;i++)
	{	scanf("%s",a[i]);
	}
	for(i=0;i<size;i++)
	{	flag=0;
		for(j=0;(j<count_restaurant)&&(flag==0);j++)
		{	if(strcmp(a[i],restaurant[key_restaurant[j]].name)==0)
			{	list[i]=key_restaurant[j];
				flag=1;
			}
		}
	}
	int count=1;
	for(p=0;p<size;p++)
	{count=1;
	for(i=0;i<restaurant[list[p]].total_special_items;i++)
	{	for(j=p+1;j<size;j++)
		{	
			for(k=0;k<restaurant[list[j]].total_items;k++)
			{	if(strcmp(restaurant[list[j]].food_items[k].name,restaurant[list[p]].food_items[i].name)==0)
				{	count++;
				}
			}
		}
		if(count==1)
		{	strcpy(temp[l],restaurant[list[p]].food_items[i].name);
			key_unique[l]=list[p];
			l++;
		}
		
	}
	}
	sort_list_key(temp,key_unique,l);
	for(i=0;i<l;i++)
	{	printf("%d. %s \t %s \t %s \n",i+1,temp[i],restaurant[key_unique[i]].name,restaurant[key_unique[i]].address);
	}
}
	
void getAllSpecialItemListInSortedOrder()
{	printf("ENTER NO OF RESTAURANTS : ");
	int size,i,j,k=0,flag=0,list[restaurant_size],key_special[20];
	char a[restaurant_size][100],temp[20][100];
	scanf("%d",&size);
	printf("ENTER THE LIST OF RESTAURANTS WHOSE SPECIAL ITEMS NEED TO BE SORTED : ");
	for(i=0;i<size;i++)
	{	scanf("%s",a[i]);
	}
	for(i=0;i<size;i++)
	{	flag=0;
		for(j=0;(j<count_restaurant)&&(flag==0);j++)
		{	if(strcmp(a[i],restaurant[key_restaurant[j]].name)==0)
			{	list[i]=key_restaurant[j];
				flag=1;
			}
		}
	}
	for(i=0;i<size;i++)
	{	for(j=0;j<restaurant[list[i]].total_special_items;j++)
		{	strcpy(temp[k],restaurant[list[i]].special_items[j].name);
			key_special[k]=list[i];
			k++;
		}
	}
	sort_list_key(temp,key_special,k);
	for(i=0;i<k;i++)
	{	printf("%d. %s \t %s \t %s \n",i+1,temp[i],restaurant[key_special[i]].name,restaurant[key_special[i]].address);
	}
}

void placeOrder()
{
    char address[20],rest_name[20],item_name[20];
    int pos,i,flag=1,j,item_key,ser_time,hr,min;
    printf("\n Enter the restaurant name:");
    scanf("%s",rest_name);
    printf("\n Address:");
    scanf("%s",address);
    printf("\n Item name:");
    i=restaurant_index(rest_name,address);
    if(i!=(-1))
    {
        pos=restaurant[i].order_size;
        if(pos<live_order_size)
        {
            ser_time=0;
			printf("\n ENTER YOUR NAME:");
                scanf("%s",restaurant[i].live_order[pos].username);
                printf("\n ENTER CONTACT NUMBER:");
                scanf("%d",&restaurant[i].live_order[pos].user_phone);
                printf("\n ENTER ADDRESS");
                scanf("%s",restaurant[i].live_order[pos].user_address);
               
				printf("ENTER THE CURRENT TIME OF PLACING ORDER : \nhr :");
				scanf("%d",&hr);
				printf("minutes : ");
				scanf("%d",&min);
				restaurant[i].live_order[pos].order_time=time_to_min(hr,min);
            for (j=0; (j<5)&&(flag==1); j++)
            {
                 printf("\n Item name:");
                scanf("%s",item_name);
                
				
                strcpy(restaurant[i].live_order[pos].order_item[j],item_name);
                item_key=item_index(item_name, i);
                if(restaurant[i].food_items[item_key].min>ser_time)
                {
                    ser_time=restaurant[i].food_items[item_key].min;
                }
                printf("\n ENTER QUANTITY");
                scanf("%d",&restaurant[i].live_order[pos].qty[j]);
                printf("\n if you wish to add another item press 1 else press 0");
                scanf("%d",&flag);
                if(j==4)
                {
                    printf("\n SORRY THE ITEM LIMIT FOR THIS ORDER HAS EXCEEDED ,CANNOT ADD ITEM");
                }
                restaurant[i].live_order[pos].service_time=ser_time;
                restaurant[i].live_order[pos].delivery_time=restaurant[i].delivery_time+ser_time;
                
            }
            restaurant[i].live_order[pos].order_id=pos+1;
            printf("\n THANK YOU FOR PLACING THE ORDER WITH ORDER ID %d,IT WILL BE DELIVERED TO YOU SHORTLY IN %d minutes \n",restaurant[i].live_order[pos].order_id,restaurant[i].live_order[pos].delivery_time);
            restaurant[i].order_size++;
        }
    }
    
}

void getItemListInSortedOrder()
{
    int i;
    char address[20],rest_name[20];
    printf("\n Enter the restaurant name:");
    scanf("%s",rest_name);
    printf("\n Address:");
    scanf("%s",address);
    i=restaurant_index(rest_name, address);
    char_arr_sort(restaurant[i].food_items,restaurant[i].total_items);
    display_item(restaurant[i].food_items,restaurant[i].total_items);
}

void getSpecialItemListInSortedOrder()
{
    int i;
    char address[20],rest_name[20];
    printf("\n Enter the restaurant name:");
    scanf("%s",rest_name);
    printf("\n Address:");
    scanf("%s",address);
    i=restaurant_index(rest_name, address);
    char_arr_sort(restaurant[i].special_items,restaurant[i].total_items);
    display_item(restaurant[i].special_items,restaurant[i].total_items);
}
void display_item(struct item_details list[],int size)
{	
    int i;
    for (i=0; i<size; i++) {
        printf("%s\n",list[i].name);
        
    }
    
}

int special_index(char item_name[],int rest_index)
{
    int i,found=-1;
    for (i=0; (i<restaurant[rest_index].total_special_items)&&found==(-1); i++) {
        if (strcmp(item_name, restaurant[rest_index].special_items[i].name)==0) {
            found=i;
        }
    }
    return found;
}
void getItemOfDayListInSortedOrder()
{
    char area[20];
    int i,j=0;
    char *s;
    struct item_details special[count_restaurant];
    printf("\n ENTER THE AREA IN WHICH YOU WISH TO SEE SPECIAL ITEM OF THE DAY");
    scanf("%s",area);
    for(i=0;i<count_restaurant;i++)
    {
        s=strstr(restaurant[i].address, area);
        if (*s!='\0')
        {
            if(restaurant[i].special_day.name[0]!='\0')
            {
                special[j]=restaurant[i].special_day;
                j++;
            }
        }
        char_arr_sort(special, j);
    }
    display_item(special, j);
        
}

void FindOrderAssignment()
{	printf("ENTER THE NO OF ITEMS YOU WANT TO ENTER : ");
	int size,i,posk,posj,qty[20],min,flag,j,k,total=0,t,flag2,count=0;
	int index[20];
	char a[20][100];
	scanf("%d",&size);
	printf("ENTER THE NAMES OF THE FOOD ITEMS : ");
	
	for(i=0;i<size;i++)
	{	printf("\n ENTER ITEM NAME \n");
		scanf("%s",a[i]);
		printf("QUANTITY : ");
		scanf("%d",&qty[i]);
		flag=0;
		for(j=0;j<count_restaurant;j++)
		{	for(k=0;k<restaurant[j].total_items;k++)
			{if((strcmp(restaurant[j].food_items[k].name,a[i])==0)&&(flag==0))
			{	min=restaurant[j].food_items[k].price;
				posj=j;
				posk=k;
				flag=1;
			}
		
			if((strcmp(restaurant[j].food_items[k].name,a[i])==0)&&(min>restaurant[j].food_items[k].price))
			{	min=restaurant[j].food_items[j].price;
				posj=j;
				posk=k;
			}
			}
			total=min*qty[i]+total;
			flag2=0;
			for(t=0;t<=i&&flag2==0;t++)
			{
				if(index[t]==posj)
				{
					flag2=1;
				}
			}
			if(flag2==0)
			{
				index[count]=posj;
				count++;	
			}
		}
		
	}
	printf("\n THE TPOTAL MINIMUM PRICE IS %d by restaurants\n",total);
	for(i=0;i<count;i++)
	{
	printf("\t%s\n",restaurant[index[i]].name);
	}
}









