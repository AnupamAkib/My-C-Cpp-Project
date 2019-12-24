#include<stdio.h>
#include<string.h>

int digit(int n){ //function for counting digits in an integer
    char s[15];
    sprintf(s, "%d", n);
    return strlen(s);
}

typedef struct inf{ //a structure to save customers informations
    char name[50], address[120], phone[20];
    int food_buy[15], food_quantity[15];
} info;

int main(){
    int i, j, q;
    info customer[100];
    char food[10][30]={"", "Pasta", "Pizza", "Chowmein", "Kacchi Biriyani", "Chicken Burger", "Fried Chicken", "Coca Cola", "Sprite"}; //food items
    int price[10]={0, 180, 400, 150, 200, 140, 300, 25, 25}; //food items price respectfully
    char username[20];
    int password;

    printf(" Username: ");
    scanf("%s", username);
    printf(" Password: ");
    scanf("%d", &password);

    if(strcmp(username, "anupam")==0 && password==1234){
        printf("\tYOU HAVE SUCCESSFULLY LOGGED IN!\n\n");
        printf(" Available food:\n");
        for(i=1; i<=8; i++){
            printf("\t%d. %s  :  %d/-\n", i, food[i], price[i]); //show available food list with serial
        }

        int k=1, value;
        double amount_paid=0;
        while(1){
            printf("\n Generate Cash Memo: enter 1\n Show total account: enter 2\n");
            scanf("%d", &value);
            if(value==1){
                int cnt=0, sc=0;
                double total=0; //total amount initially
                printf("\n Customer Name: ");
                fflush(stdin);
                gets(customer[k].name);
                printf(" Customer Address: ");
                gets(customer[k].address);
                printf(" Customer Phone: ");
                gets(customer[k].phone);

                printf("\n Enter 0 to generate cash memo\n Food Serial | Quantity (Use space to separate.)\n");
                for(j=1; ; j++){
                    printf("\t    ");
                    scanf("%d", &customer[k].food_buy[j]); //enter food items serial
                    if(customer[k].food_buy[j]==0){ //0 is found, so break the loop & start making the memo
                        break;
                    }
                    scanf("%d", &customer[k].food_quantity[j]); //enter quantity of the food
                    cnt++;
                }

                //GENERATE CASH MEMO
                printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf("                  CASH MEMO\n");
                printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
                printf(" Customer Name: %s\n", customer[k].name);
                printf(" Address: %s\n", customer[k].address);
                printf(" Phone: %s\t\tCash Memo SL: %d\n\n", customer[k].phone, k);
                printf(" SL |        ITEM        | Quantity |    PRICE\n");
                printf("------------------------------------------------\n");

                for(i=1; i<=cnt; i++){
                    printf(" %d.     %s", i, food[customer[k].food_buy[i]]);

                    for(j=1; j<=17-strlen(food[customer[k].food_buy[i]]); j++){ //space control loop
                        printf(" ");
                    }
                    printf("|    x%d    |", customer[k].food_quantity[i]);
                    for(j=1; j<=8-digit(price[customer[k].food_buy[i]]*customer[k].food_quantity[i]); j++){ //space control loop
                        printf(" ");
                    }
                    printf("%d/-\n", price[customer[k].food_buy[i]]*customer[k].food_quantity[i]);
                    total+=price[customer[k].food_buy[i]]*customer[k].food_quantity[i]; //add price with total
                }
                printf("------------------------------------------------\n");
                printf("                               Total:");
                for(j=1; j<=7-digit(total); j++){ //space control loop
                    printf(" ");
                }
                printf("%.1lf/-\n", total);
                if(total>=500){ //20 taka service charge will be added if 500 taka or more amount of food is bought
                    printf("                      Service Charge:     20.0/-\n");
                    sc=20;
                }
                printf("                            VAT (5%%):");
                for(j=1; j<=7-digit(total+(total*0.05)); j++){ //space control loop
                    printf(" ");
                }
                printf("%.1lf/-\n", total*0.05); //5% vat
                printf("------------------------------------------------\n");
                printf("                          TOTAL BILL:");
                total+=sc+(total*0.05); //final total bill to be paid
                for(j=1; j<=7-digit(total); j++){ //space control loop
                    printf(" ");
                }
                printf("%.1lf/-\n", total); //show total bill
                printf("------------------------------------------------\n\n");
                amount_paid+=total;
                k++;
            }
            else{
                printf("\t\t\tTOTAL AMOUNT OF MONEY: %.1lf\n\n\n", amount_paid); //total money that he sold till now
            }
        }
    }
    else{
        puts(" Wrong username or password. Try again.");
    }

    getch();
    return 0;
}






