#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef struct st{
    char name[50];
    char pass[50];
    char phone[50];
}data; //structure to store retrived data from file




int x, t; //declaring variable
int check;
data user[500];
char name[50], pass[50], con_pass[50], phone_no[50], phn[20];
int cnt=0;
FILE *file;
char rout[250][200], bus[250][200], tmp[500], mixed_data[500][250];
char my_rout[250], my_bus[250], ac[3][200]; //0 = non-ac, 1 = ac
int t, rout_cnt, check;


void title(char str[50]){
    printf("\n\t");
    for(int i=1; i<=38+strlen(str); i++){
        printf("\033[0;33m\xdb\033[m");
    }
    printf("\n\t\033[0;33m\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb %s \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\033[m", str);
    printf("\t");
    for(int i=1; i<=38+strlen(str); i++){
        printf("\033[0;33m-\033[m");
    }
    printf("\n");
}

void choice(){ //function for taking user choice
    printf("\t\033[0;36mEnter Choice: \033[0m");
    scanf("%d", &check);
}


void clear_data(){ //function for clearing all booked seat information
    system("cls");
    title("CLEAR BOOKING DATA");
    printf("\n\033[0;31m\tYour all booking data will be permanently deleted.\n\tAre you sure?\n\n\033[0m");
    printf("\t\t1. YES\n\t\t2. NO\n\n");
    choice();
    if(check==1){
        t=0;
        file=fopen("rout-bus-seat.txt", "r");
        while(fgets(mixed_data[t], 300, file)!= NULL){
            t++;
        }
        fclose(file);
        for(int i=4; i<t; i+=5){
            strcpy(mixed_data[i], "A1 A2 A3 A4 B1 B2 B3 B4 C1 C2 C3 C4 D1 D2 D3 D4 E1 E2 E3 E4 F1 F2 F3 F4 G1 G2 G3 G4 H1 H2 H3 H4 I1 I2 I3 I4\n");
        }
        file=fopen("rout-bus-seat.txt", "w");
        for(int i=0; i<t; i++){
            fprintf(file, "%s", mixed_data[i]);
        }
        fclose(file);
        printf("\033[0;32m\n\tALL BOOK DATA HAS BEEN DELETED SUCCESSFULLY!\n\033[0m");
    }
    else{
        return;
    }
}


int login_flag=0;

void book(){ //function for booking bus
    system("cls");
    if(login_flag==1){
        printf("\n\t\033[0;32mYOU HAVE SUCCESSFULLY LOGGED IN!\n\033[0m");
    }
    else{
        printf("\n\t\033[0;32mYOUR ACCOUNT IS CREATED SUCCESSFULLY! You are logged in.\n\033[0m");
    }
    printf("\033[0;32m\tWelcome \"%s\"\n\033[0m", name);
    t=0;
    file=fopen("rout-bus-seat.txt", "r");
    while(fgets(mixed_data[t], 300, file)!= NULL){ //retrive all data from file
        t++;
    }
    fclose(file);
    rout_cnt=0;
    for(int i=0; i<t; i+=5){ //getting unique rout from all data (stored in mixed_data[])
        int flag=0;
        strcpy(tmp, mixed_data[i]);
        for(int j=0; j<t/5; j++){
            if(strcmp(tmp, rout[j])==0){ //looking for unique rout (no rout will print more than 1 time)
                flag=1;
                break;
            }
        }
        if(flag==0){ //if checked rout is not already inserted in the rout array then push it in the array
            strcpy(rout[rout_cnt], tmp);
            rout_cnt++;
        }
    }
    title("AVAILABLE ROUTE");
    printf("\n");
    for(int i=0; i<rout_cnt; i++){ //print all available rout
        printf("\t\t%d. %s", i+1, strupr(rout[i]));
    }
    printf("\n");
    ta:
    choice();
    if(check>rout_cnt || check==0){
        printf("\033[0;31m\tWrong Choice. Please try again.\n\033[0m");
        goto ta;
    }
    else{
        strcpy(my_rout, rout[check-1]); //collecting selected rout from user
    }

    int bus_cnt=0;
    for(int i=0; i<t; i+=5){ //getting all available bus in that selected rout
        if(strcmp(my_rout, strupr(mixed_data[i]))==0){
            strcpy(bus[bus_cnt], mixed_data[i+1]); //storing in an array
            bus_cnt++;
        }
    }

    title("SELECT BUS");
    printf("\t\t\033[0;33m Route: %s\033[0m\n", my_rout);
    for(int i=0; i<bus_cnt; i++){ //printing available bus in the rout
        printf("\t\t%d. %s", i+1, bus[i]);
    }
    printf("\n");
    ba:
    choice();
    if(check>bus_cnt || check==0){
        printf("\033[0;31m\tWrong Choice. Please try again.\n\033[0m");
        goto ba;
    }
    else{
        strcpy(my_bus, bus[check-1]); //collecting selected bus from user
    }

    /*printf("\n\t######## SELECT BUS TYPE #########\n");
    printf("\t1. NON-AC\n\t2. AC\n");
    choice();*/

    int price_non_ac, p_cnt=0;
    for(int i=0; i<t; i+=5){ //getting each ticket price for that bus in that rout
        if(strcmp(mixed_data[i], my_rout)==0 && strcmp(mixed_data[i+1], my_bus)==0){
            strcpy(tmp, mixed_data[i+2]);
            tmp[strlen(tmp)]='\0';
            price_non_ac=atoi(tmp); //converting the price in integer
            break;
        }
    }


    for(int i=0; i<t; i+=5){ //getting all seats availability information in that bus
        if(strcmp(mixed_data[i], my_rout)==0 && strcmp(mixed_data[i+1], my_bus)==0){
            strcpy(tmp, mixed_data[i+4]);
            break;
        }
    }
    //printf("%s", tmp);
    int total_seat=0, ct=0;
    char individual_seat[50][10];
    for(int i=0; i<strlen(tmp); i+=3){ //breaking them in individual seat to make change in it
        individual_seat[total_seat][0]=tmp[i];
        individual_seat[total_seat][1]=tmp[i+1];
        individual_seat[total_seat][2]='\0';
        total_seat++;
    }
    total_seat--;
    int flag;
    flag=0;
    for(int i=0; i<total_seat; i++){ //checking if all seats in the bus is already booked
        if(strcmp(individual_seat[i], "xx")!=0){
            flag=1; //flag=1 means not booked. minimum 1 seat is not booked
            break;
        }
    }
    akib:


    system("cls");
    title("BOOKING INFORMATION");
    printf("\n\tPASSENGER: %s\n", name);
    printf("\tPHONE: %s\n", phn);
    printf("\tROUTE: %s\tBUS: %s", my_rout, my_bus); //printing my information including my rout, bus and fare of ticket
    printf("\tSEAT COST: %d/-\n\n", price_non_ac);
    for(int i=0; i<total_seat; i+=4){ //seat diagram building with availability of a seat
        if(strcmp(individual_seat[i], "xx")==0){
            printf("\033[0;31m");
        }
        else{
            printf("\033[0;32m");
        }
        printf("\t\t|%s  \033[0m", individual_seat[i]);

        if(strcmp(individual_seat[i+1], "xx")==0){
            printf("\033[0;31m");
        }
        else{
            printf("\033[0;32m");
        }
        printf("%s     \033[0m", individual_seat[i+1]);

        if(strcmp(individual_seat[i+2], "xx")==0){
            printf("\033[0;31m");
        }
        else{
            printf("\033[0;32m");
        }

        printf("%s  \033[0m", individual_seat[i+2]);

        if(strcmp(individual_seat[i+3], "xx")==0){
            printf("\033[0;31m");
        }
        else{
            printf("\033[0;32m");
        }
        printf("%s|\n\033[0m", individual_seat[i+3]);

        printf("\t\t-------     -------\n");
    }
    if(flag==0){ //if all seats is booked already
        printf("\033[0;31m\tSORRY, NO TICKET AVAILABLE IN THIS ROUT\n\033[0m");
        return;
    }
    ct++;
    if(ct==3){goto bill;}

    int booked_seat;
    char my_seats[50][10];

    again:
    printf("\tHOW MANY SEATS YOU WANT TO BOOK? ");
    scanf("%d", &booked_seat); //how many ticket i wanna buy
    printf("\tSELECT SEAT (ex- A1 A2 B1): ");

    for(int i=0; i<booked_seat; i++){ //taking seats ID (A1 A2 A3)
        scanf("%s", my_seats[i]);
        strupr(my_seats[i]);
    }
    int taken=0;
    for(int i=0; i<booked_seat; i++){
        int flag2=0;
        for(int j=0; j<=total_seat; j++){ //check if one of the selected ticket is already booked
            if(strcmp(my_seats[i], individual_seat[j])==0){
                flag2=1; break;
            }
        }
        if(flag2==0){
            printf("\033[0;31m\t%s is already taken. Try again\n\033[0m", my_seats[i]);
            taken=1;
        }
    }
    if(taken==1){ //if already taken take seat information again.
        goto again;
    }


    for(int i=0; i<booked_seat; i++){ //book selected seat in that bus in that rout
        for(int j=0; j<=total_seat; j++){
            if(strcmp(my_seats[i], individual_seat[j])==0){
                strcpy(individual_seat[j], "xx"); //and replace it with xx. so that we can identify it is booked
            }
        }
    }
    int itarate=0;
    for(int i=0; i<=total_seat; i++){ //making a seat information line. so that we can save it in the file
        tmp[itarate]=individual_seat[i][0];
        tmp[itarate+1]=individual_seat[i][1];
        tmp[itarate+2]=' ';
        itarate+=3;
    }
    tmp[itarate]='\n';

    printf("%s", tmp);
    for(int i=0; i<t; i+=5){ //replace seat information line with the previous one
        if(strcmp(mixed_data[i], my_rout)==0 && strcmp(mixed_data[i+1], my_bus)==0){
            strcpy(mixed_data[i+4], tmp);
            break;
        }
    }
    file=fopen("rout-bus-seat.txt", "w"); //write those information in the file
    for(int i=0; i<t; i++){
        fprintf(file, "%s", mixed_data[i]);
    }
    fclose(file);
    ct++;
    goto akib;

    bill: //generate bill if seat is booked
        printf("\033[0;32m\n\tYOUR BOOKING IS SUCCESSFUL!\033[0m");
        printf("\n\tSeat Booked: %d -> ", booked_seat);
        for(int i=0; i<booked_seat; i++){
            printf("%s ", my_seats[i]);
        }
        printf("\n\tPer Seat Cost: %d/-", price_non_ac);
        printf("\n\tTOTAL PAYABLE: %d/-\n", price_non_ac*booked_seat);

        file=fopen("user-info.txt", "a");
        fprintf(file, "%s\n", name);
        fprintf(file, "%s\n", phn);
        fprintf(file, "%s", my_rout);
        fprintf(file, "%s", my_bus);
        for(int i=0; i<booked_seat; i++){
            fprintf(file, "%s ", my_seats[i]);
        }
        fprintf(file, "\n%d\n", price_non_ac*booked_seat);
        fclose(file);
}

void add_bus(){
    system("cls");
    t=0;
    file=fopen("rout-bus-seat.txt", "r");
    while(fgets(mixed_data[t], 300, file)!= NULL){ //retrive all data from file
        t++;
    }
    fclose(file);
    rout_cnt=0;
    for(int i=0; i<t; i+=5){ //getting unique rout from all data (stored in mixed_data[])
        int flag=0;
        strcpy(tmp, mixed_data[i]);
        for(int j=0; j<t/5; j++){
            if(strcmp(tmp, rout[j])==0){ //looking for unique rout (no rout will print more than 1 time)
                flag=1;
                break;
            }
        }
        if(flag==0){ //if checked rout is not already inserted in the rout array then push it in the array
            strcpy(rout[rout_cnt], tmp);
            rout_cnt++;
        }
    }

    char newRout[100], newBus[100];
    int seat_fare;
    title("ADD NEW BUS");
    printf("\n\tAlready Available Routs:\n\n");
    for(int i=0; i<rout_cnt; i++){ //print available rout
        printf("\t\t%d. %s", i+1, rout[i]);
    }
    printf("\n\t(Enter 0 if you want to add other rout)\n");
    choice();
    if(check==0){
        printf("\n\tENTER NEW ROUT: ");
        fflush(stdin);
        gets(newRout);
        strupr(newRout);
    }
    else{
        strcpy(newRout, rout[check-1]);
        newRout[strlen(newRout)-1]='\0';
        printf("\n\tADD BUS FOR ROUTE: %s\n", newRout);
    }
    printf("\tENTER BUS NAME: ");
    fflush(stdin);
    gets(newBus);
    printf("\tENTER EACH SEAT FARE: ");
    scanf("%d", &seat_fare);

    file=fopen("rout-bus-seat.txt", "a");
    fprintf(file, "%s\n", newRout);
    fprintf(file, "%s\n", newBus);
    fprintf(file, "%d\n", seat_fare);
    fprintf(file, "#AC_TICKET_PRICE_HERE\n");
    fprintf(file, "A1 A2 A3 A4 B1 B2 B3 B4 C1 C2 C3 C4 D1 D2 D3 D4 E1 E2 E3 E4 F1 F2 F3 F4 G1 G2 G3 G4 H1 H2 H3 H4 I1 I2 I3 I4\n");
    fclose(file);
    printf("\n\t-------------------------------------------------\n");
    printf("\tRout: %s\n\tBus: %s", newRout, newBus);
    printf("\033[0;32m\n\tBUS ADDED SUCCESSFULLY!\n\033[0m");
    printf("\t-------------------------------------------------\n");
}

void delete_bus(){
    system("cls");
    t=0;
    file=fopen("rout-bus-seat.txt", "r");
    while(fgets(mixed_data[t], 300, file)!= NULL){ //retrive all data from file
        t++;
    }
    fclose(file);
    rout_cnt=0;
    for(int i=0; i<t; i+=5){ //getting unique rout from all data (stored in mixed_data[])
        int flag=0;
        strcpy(tmp, mixed_data[i]);
        for(int j=0; j<t/5; j++){
            if(strcmp(tmp, rout[j])==0){ //looking for unique rout (no rout will print more than 1 time)
                flag=1;
                break;
            }
        }
        if(flag==0){ //if checked rout is not already inserted in the rout array then push it in the array
            strcpy(rout[rout_cnt], tmp);
            rout_cnt++;
        }
    }

    char del_rout[100], del_bus[100];
    title("REMOVE A BUS");
    printf("\n\tAll available Route:\n\n");
    for(int i=0; i<rout_cnt; i++){ //print available rout
        printf("\t\t%d. %s", i+1, rout[i]);
    }
    printf("\n");
    choice();
    strcpy(del_rout, rout[check-1]);

    printf("\033[0;33m\n\tAll available Bus in rout %s\033[0m\n", del_rout);
    int bus_cnt=0;
    for(int i=0; i<t; i+=5){ //getting all available bus in that selected rout
        if(strcmp(del_rout, strupr(mixed_data[i]))==0){
            strcpy(bus[bus_cnt], mixed_data[i+1]); //storing in an array
            bus_cnt++;
        }
    }
    for(int i=0; i<bus_cnt; i++){ //print available bus in the rout
        printf("\t\t%d. %s", i+1, bus[i]);
    }
    printf("\n");
    choice();
    strcpy(del_bus, bus[check-1]);
    for(int i=0; i<t; i++){
        if(strcmp(mixed_data[i], del_rout)==0 && strcmp(mixed_data[i+1], del_bus)==0){
            for(int j=i; j<t; j++){ //remove lines regarding that rout, bus and fare
                strcpy(mixed_data[j], mixed_data[j+5]);
            }
            break;
        }
    }
    file=fopen("rout-bus-seat.txt", "w"); //edit in file
    for(int i=0; i<t; i++){
        fprintf(file, "%s", mixed_data[i]);
    }
    fclose(file);
    printf("\n\t-------------------------------------------------\n");
    printf("\tRoute: %s", del_rout);
    printf("\tBus: %s", del_bus);
    printf("\033[0;32m\tBUS REMOVED SUCCESSFULLY!\n\033[0m");
    printf("\t-------------------------------------------------\n");

}



void retrive_data(){ //function to collect data from user and password file
    file=fopen("user.txt", "r");
    while(fscanf(file, "%s", user[cnt].name)!=EOF){
        cnt++;
    }
    fclose(file);
    file=fopen("password.txt", "r");
    cnt=0;
    while(fscanf(file, "%s", user[cnt].pass)!=EOF){
        cnt++;
    }
    fclose(file);
    file=fopen("phone.txt", "r");
    cnt=0;
    while(fscanf(file, "%s", user[cnt].phone)!=EOF){
        cnt++;
    }
    fclose(file);
}

void signup(){ //function for signing up
    system("cls");// clear screen
    title("SIGN UP");
    take_user:
    printf("\n\tUsername: ");
    //scanf("%s", name);
    fflush(stdin);
    gets(name);
    for(int i=0; i<strlen(name); i++){ //check if user used space in username
        if(name[i]==' '){
            printf("\033[0;31m\tSpace is not allowed. try '.', '-' or '_' instead! \033[0m");
            goto take_user;
        }
    }
    for(int i=0; i<cnt; i++){ //check if the username is exist using linear search
        if(strcmp(name, user[i].name)==0){
            printf("\033[0;31m\tSorry, this username is already taken. try another! \033[0m");
            goto take_user; break;
        }
    }
    printf("\033[0;32m\tUsername \"%s\" is AVAILABLE \n \033[0m", name);
    take_pass:
    printf("\tPassword: ");
    int q=0;
    while(1){ //for printing star
        if(q<0){q=0; continue;}
        pass[q]=getch();
        if(pass[q]=='\r'){
            pass[q]='\0';
            break;
        }
        if(pass[q]==8){
            putch('\b');
            putch(' ');
            q--;
            pass[q]='\0';
            putch('\b');

        }
        else{
            putch('*');
            q++;
        }
    }
    printf("\n\tConfirm Password: ");
    q=0;
    while(1){ //for printing star
        if(q<0){q=0; continue;}
        con_pass[q]=getch();
        if(con_pass[q]=='\r'){
            con_pass[q]='\0';
            break;
        }
        if(con_pass[q]==8){
            putch('\b');
            putch(' ');
            q--;
            con_pass[q]='\0';
            putch('\b');

        }
        else{
            putch('*');
            q++;
        }
    }

    if(strcmp(pass, con_pass)!=0){ //check if both password are matched.
        printf("\033[0;31m \n\tPassword didn't match. Try again.\n\033[0m");
        goto take_pass;
    }
    printf("\n\tEnter your Phone no: ");
    scanf("%s", phone_no);
    strcpy(phn, phone_no);

    //now assign all valid information in file and get registered
    file=fopen("user.txt", "a");
    fprintf(file, "%s\n", name);
    fclose(file);
    file=fopen("password.txt", "a");
    fprintf(file, "%s\n", pass);
    fclose(file);
    file=fopen("phone.txt", "a");
    fprintf(file, "%s\n", phone_no);
    fclose(file);
    system("cls");
    printf("\033[0;32m\n\tAccount Created Successfully. YOU ARE LOGGED IN! \033[0m"); //logged in msg
    printf("\033[0;32m \n\tWelcome \"%s\"\n \033[0m", name); //logged in msg

    book();
}

void login(){ //function for login to the system
    system("cls");// clear screen
    title("USER LOGIN");
    log:
    printf("\n\tEnter Username: ");
    //scanf("%s", name);
    fflush(stdin);
    gets(name);
    for(int i=0; i<strlen(name); i++){ //check if user used space in username
        if(name[i]==' '){
            printf("\033[0;31m\tInvalid username. Please try again! \033[0m");
            goto log;
        }
    }
    printf("\tEnter Password: ");
    int q=0;

    while(1){ //for printing star
        if(q<0){q=0; continue;}
        pass[q]=getch();
        if(pass[q]=='\r'){
            pass[q]='\0';
            break;
        }
        if(pass[q]==8){
            putch('\b');
            putch(' ');
            q--;
            pass[q]='\0';
            putch('\b');

        }
        else{
            putch('*');
            q++;
        }
    }



    int flag=0;
    for(int i=0; i<cnt; i++){
        if(strcmp(name, user[i].name)==0 && strcmp(pass, user[i].pass)==0){
            //textcolor();
            system("cls");
            login_flag=1;
            strcpy(phn, user[i].phone);
            book();

            flag=1; break;
        }
    }
    if(flag==0){ //username or password didn't match
        printf("\033[0;31m \n\tSORRY, USERNAME or PASSWORD IS INCORRECT.\n \033[0m\t\t1. TRY AGAIN\n\t\t2. SIGN UP\n");
        choice();
        if(check==1){
            login();
        }
        else{
            signup();
        }
    }
}

void del_user_data(){
    system("cls");
    title("DELETE ALL USER BOOKING INFO");
    printf("\n\t\033[0;31mAll user booking information including all user booking records will be deleted permanently.\n\tAre you sure?\n\033[0m");
    printf("\n\t\t1. YES\n\t\t2. NO\n\n");
    choice();
    if(check==1){
        file=fopen("user-info.txt", "w");
        fprintf(file, "");
        fclose(file);
        printf("\t\033[0;32mAll user booking data has been deleted successfully!\n\033[0m");
    }
    else{
        return;
    }
}

void DisplayUserData(){
    system("cls");
    char userdata[500][100], rem_user[50];
    int i=0;
    file=fopen("user-info.txt", "r");
    while(fgets(userdata[i], 200, file)!=NULL){
        i++;
    }
    fclose(file);
    title("USER INFORMATION of Booking");
    puts("");
    for(int k=0; k<i; k+=6){
        printf("\t\033[0;33mPASSERGER:\033[0m\033[0;32m %s\033[0m", userdata[k]);
        printf("\t\033[0;33mPHONE:\033[0m %s", userdata[k+1]);
        printf("\t\033[0;33mROUTE:\033[0m %s", userdata[k+2]);
        printf("\t\033[0;33mBUS:\033[0m %s", userdata[k+3]);
        printf("\t\033[0;33mSEAT BOOKED:\033[0m %s", userdata[k+4]);
        printf("\t\033[0;33mTOTAL PAYABLE:\033[0m %s\n", userdata[k+5]);
    }
    int flag=0;
    agn:
    printf("\tENTER USERNAME TO REMOVE USER INFO: ");
    scanf("%s", rem_user);
    rem_user[strlen(rem_user)]='\n';
    for(int k=0; k<i; k+=6){
        if(strcmp(userdata[k], rem_user)==0){
            for(int j=k; j<i; j++){
                strcpy(userdata[j], userdata[j+6]);
            }
            flag=1;
            break;
        }
    }
    if(flag==1){
        i-=6;
        file=fopen("user-info.txt", "w");
        for(int k=0; k<i; k++){
            fprintf(file, "%s", userdata[k]);
        }
        fclose(file);

        system("cls");
        title("USER INFORMATION of Booking");
        puts("");
        for(int k=0; k<i; k+=6){
            printf("\t\033[0;33mPASSERGER:\033[0m\033[0;32m %s\033[0m", userdata[k]);
            printf("\t\033[0;33mPHONE:\033[0m %s", userdata[k+1]);
            printf("\t\033[0;33mROUTE:\033[0m %s", userdata[k+2]);
            printf("\t\033[0;33mBUS:\033[0m %s", userdata[k+3]);
            printf("\t\033[0;33mSEAT BOOKED:\033[0m %s", userdata[k+4]);
            printf("\t\033[0;33mTOTAL PAYABLE:\033[0m %s\n", userdata[k+5]);
        }

        printf("\t\033[0;32mUsername is removed successfully!\033[0m\n");
        printf("\n\t\t1. REMOVE MORE\n\t\t2. EXIT\n\n");
        choice();
        if(check==1){
            DisplayUserData();
        }
        else{
            return;
        }
    }
    else{
        printf("\t\033[0;31mThis username does not exist!\033[0m\n");
        goto agn;
    }
}


void manager_login(){
    system("cls");
    title("MANAGER LOGIN");
    wp:
    printf("\n\tUsername: ");
    scanf("%s", name);
    printf("\tPassword: ");
    //scanf("%s", pass);
    int q=0;
    while(1){ //for printing star
        if(q<0){q=0; continue;}
        pass[q]=getch();
        if(pass[q]=='\r'){
            pass[q]='\0';
            break;
        }
        if(pass[q]==8){
            putch('\b');
            putch(' ');
            q--;
            pass[q]='\0';
            putch('\b');

        }
        else{
            putch('*');
            q++;
        }
    }

    if(strcmp(name, "admin")==0 && strcmp(pass, "0000")==0){
        system("cls");
        printf("\033[0;32m\n\tYou have successfully logged in as MANAGER \n\033[0m");
        title("MANAGER MENU");
        aaa:
        printf("\n\t\t1. OPEN USER BOOKING RECORDS\n\t\t2. ADD A BUS\n\t\t3. REMOVE A BUS\n\t\t4. DELETE ALL BOOKED SEAT DATA\n\t\t5. DELETE ALL USER BOOKING DATA\n\n");
        choice();
        if(check==1){
            DisplayUserData();
        }
        else if(check==2){
            add_bus();
        }
        else if(check==3){
            delete_bus();
        }
        else if(check==4){
            clear_data();
        }
        else if(check==5){
            del_user_data();
        }
        else{
            system("cls");
            title("MANAGER MENU");
            printf("\n\033[0;31m\tSorry, incorrect selection. Try again.\033[0m\n");
            goto aaa;
        }
    }
    else{
        system("cls");
        title("MANAGER LOGIN");
        printf("\033[0;31m\n\tSorry, username or password is wrong. Try again. \n\033[0m");

        goto wp;
    }
}

void log_menu(){
    system("cls");
    title("LOGIN MENU");
    aaa:
    printf("\n\tSelect Login Method:\n\n");
    printf("\t\t1. LOGIN AS USER\n\t\t2. SIGN UP AS USER\n\t\t3. LOGIN AS MANAGER\n\n");
    choice();
    if(check==1){
        login();
    }
    else if(check==2){
        signup();
    }
    else if(check==3){
        manager_login();
    }
    else{
        system("cls");
        title("LOGIN MENU");
        printf("\n\033[0;31m\tSorry, incorrect selection. Try again.\033[0m\n");
        goto aaa;
    }
}
void start(){
    system("cls");
    printf("\033[0;33m");
    printf("\n\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb BUS TICKET BOOKING SYSTEM \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
    printf("\033[0m\n\n");
    printf("\033[0;36m\tPROGRAMMER's INFORMATON:\033[0m\n\t------------------------------\n");
    printf("\t\033[0;33mName:\033[0m Mir Anupam Hossain Akib\n");
    printf("\t\033[0;33mID:\033[0m 191-35-2640\n");
    printf("\t\033[0;33mSection:\033[0m B\n");
    printf("\t\033[0;33mEmail:\033[0m anupam35-2640@diu.edu.bd\n");
    printf("\t\033[0;33mDepartment of Software Engineering, \n\tDaffodil International University\033[0m\n");

    printf("\033[0;36m\n\n\tPROJECT's INFORMATON:\033[0m\n\t------------------------------\n");
    printf("\t\033[0;33mProject:\033[0m Bus Ticket Booking System\n");
    printf("\t\033[0;33mCourse Title:\033[0m Software Development Project\n");
    printf("\t\033[0;33mCourse Code:\033[0m SE133\n");
    printf("\t\033[0;33mCourse Teacher:\033[0m DR. MD. ASRAF ALI\n");
    printf("\t\033[0;33mDate:\033[0m 8th December, 2019\n");
    printf("\t\033[0;33mDepartment of Software Engineering, \n\tDaffodil International University\033[0m\n");

    printf("\n\n\t\033[0;35mPress any key to continue\033[0m");
    if(getch()){
        log_menu();
    }
}

int main(){
    retrive_data();
    //add_bus();
    start();
    printf("\n\n\t\033[0;35mPRESS ANY KEY TO EXIT\033[0m\n");
    getch();
    return 0;
}


































