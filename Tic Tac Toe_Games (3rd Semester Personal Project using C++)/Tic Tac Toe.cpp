#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

//declaring some functions
void game();
void history();
void about();
void main_menu();

char mark[12];
char player1[50], player2[50];
int choice, turn = 1;

//structure to calculate match statistical information
typedef struct{
    int played = 0;
    int player1_win = 0;
    int player2_win = 0;
    int draw = 0;
} inf;
inf match;

void title(char header[100]){ //function for the title bar
    int m, n;
    m=ceil((55-strlen(header))/2.0)-1;
    n=floor((55-strlen(header))/2.0)-1;
    cout << endl;
    cout << "\t\t\033[0;36m";
    for(int i=0; i<55; i++){cout << "\xdb";}
    cout << "\n\t\t";
    for(int i=0; i<m; i++){cout << "\xdb";}
    cout << " \033[0m\033[0;93m" << header << "\033[0m \033[0;36m";
    for(int i=0; i<n; i++){cout << "\xdb";}
    cout << endl << "\t\t";
    for(int i=0; i<55; i++){cout << "=";}
    cout << "\033[0m" << endl << endl;
}

void take_user(){ //take two players name
    title("TIC TAC TOE - Players");
    cout << "\t\033[0;33mEnter Player 1 Name (X) : \033[0m";
    fflush(stdin);
    gets(player1);
    strupr(player1); //make it uppercase
    cout << "\t\033[0;33mEnter Player 2 Name (O) : \033[0m";
    fflush(stdin);
    gets(player2);
    strupr(player2);
    if(strcmp(player1, player2)==0){ //check if both name is same
        system("cls");
        cout << "\t\033[0;31mBoth player name is same. Please Try Again!\033[0m" << endl;
        take_user();
    }
}

void print_board(){ //function to print the game board with sign
    system("cls");
    title("TIC TAC TOE - Games");
    cout << "\t\033[0;91mX : " << player1 << "\033[0m" << endl;
    cout << "\t\033[0;92mO : " << player2 << "\033[0m" << endl;

    //print who won how many times in the game and how many matched played and drawn
    cout << "\n\t" << player1 << " " << match.player1_win << " - " << match.player2_win << " " << player2 << " (Played: " << match.played << ", Drawn: " << match.draw << ")" << endl;

    cout << "\n\t     \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb" << endl;
    cout << "\t     \xdb                 \xdb" << endl; //for bordering

    for(int i=0; i<9; i+=3){
        cout << "\t     \xdb    ";
        //i used ternary operators to print signs with coloring
        mark[i]=='X'? cout << "\033[0;91m" << mark[i] << "\033[0m" : mark[i]=='O'? cout << "\033[0;92m" << mark[i] << "\033[0m" : cout << "\033[0;90m" << mark[i] << "\033[0m";
        cout << " | ";
        mark[i+1]=='X'? cout << "\033[0;91m" << mark[i+1] << "\033[0m" : mark[i+1]=='O'? cout << "\033[0;92m" << mark[i+1] << "\033[0m" : cout << "\033[0;90m" << mark[i+1] << "\033[0m";
        cout << " | ";
        mark[i+2]=='X'? cout << "\033[0;91m" << mark[i+2] << "\033[0m" : mark[i+2]=='O'? cout << "\033[0;92m" << mark[i+2] << "\033[0m" : cout << "\033[0;90m" << mark[i+2] << "\033[0m";
        cout << "    \xdb" << endl ;
        if(i!=6){
            cout << "\t     \xdb   ---|---|---   \xdb" << endl;
        }
    }
    cout << "\t     \xdb                 \xdb" << endl; //for bordering
    cout << "\t     \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb" << endl;

}

FILE *file;
void saveInfo(char str[50]){ //function to save players result with time in a file
    file = fopen("history.txt", "a");
    fprintf(file, "%s vs %s\n", player1, player2);
    if(strcmp(str, "DRAWN")==0){ //if game is draw
        fprintf(file, "%s\n", str);
    }
    else{ //if not draw
        fprintf(file, "%s won\n", str);
    }
    time_t my_time = time(NULL); //for printing time
    fprintf(file, "%s", ctime(&my_time));
    fclose(file);
}

bool check_availability(int n){ //function to check if player want to put 'X' or 'O' in the right place
    if(n>9 || n<1){
        return false;
    }
    n--;
    if(mark[n]=='X' || mark[n]=='O'){
        return false;
    }
    return true;
}

int check_result(){ //function to check whether the game is over or not
    ///player1
    //return 1 if player1 wins
    //horizontal check
    if(mark[0]=='X' && mark[1]=='X' && mark[2]=='X'){return 1;}
    if(mark[3]=='X' && mark[4]=='X' && mark[5]=='X'){return 1;}
    if(mark[6]=='X' && mark[7]=='X' && mark[8]=='X'){return 1;}
    //vertical check
    if(mark[0]=='X' && mark[3]=='X' && mark[6]=='X'){return 1;}
    if(mark[1]=='X' && mark[4]=='X' && mark[7]=='X'){return 1;}
    if(mark[2]=='X' && mark[5]=='X' && mark[8]=='X'){return 1;}
    //corner check
    if(mark[0]=='X' && mark[4]=='X' && mark[8]=='X'){return 1;}
    if(mark[2]=='X' && mark[4]=='X' && mark[6]=='X'){return 1;}

    ///player2
    //return 2 if player2 wins
    //horizontal check
    if(mark[0]=='O' && mark[1]=='O' && mark[2]=='O'){return 2;}
    if(mark[3]=='O' && mark[4]=='O' && mark[5]=='O'){return 2;}
    if(mark[6]=='O' && mark[7]=='O' && mark[8]=='O'){return 2;}
    //vertical check
    if(mark[0]=='O' && mark[3]=='O' && mark[6]=='O'){return 2;}
    if(mark[1]=='O' && mark[4]=='O' && mark[7]=='O'){return 2;}
    if(mark[2]=='O' && mark[5]=='O' && mark[8]=='O'){return 2;}
    //corner check
    if(mark[0]=='O' && mark[4]=='O' && mark[8]=='O'){return 2;}
    if(mark[2]=='O' && mark[4]=='O' && mark[6]=='O'){return 2;}

    //check if the game is a draw
    bool flag=true;
    for(int i=0; i<9; i++){
        if(mark[i] >= '1' && mark[i] <= '9'){
            flag=false;
            break;
        }
    }
    if(flag==true){return 0;} //return 0 if the game is draw
}

void play(){ //the function that control the whole game taking the help of other functions
    system("cls");
    print_board();
    cout << endl;
    if(turn%2==1){ //used to move the turn one player to other player. odd - player1, even - player2
        cout << "\t\033[0;91m" << player1 << "'s Turn (X)\033[m" << endl;
        again1:
        cout << "\tEnter choice where you want to put 'X'" << endl << "\t";

        choice = getch(); //take players input (player doesn't need to press enter.)
        int k = choice - '0'; //as getch() takes character input so we convert it in integer
        if(choice==27){main_menu();} //if user wants to leave from a running game the he need to press ESC key
        if(check_availability(k)==true){ //check if the choice is valid
            mark[k-1]='X';
        }
        else{
            cout << "\033[0;31mInvalid choice. Please Try another!\033[0m" << endl;
            goto again1; //if choice is invalid take input again.
        }
    }
    else{
        cout << "\t\033[0;92m" << player2 << "'s Turn (O)\033[0m" << endl;
        again2:
        cout << "\tEnter choice where you want to put 'O'" << endl << "\t";

        choice = getch(); //take players input (player doesn't need to press enter.)
        int k = choice - '0'; //as getch() takes character input so we convert it in integer
        if(choice==27){main_menu();} //if user wants to leave from a running game the he need to press ESC key
        if(check_availability(k)==true){ //check if the choice is valid
            mark[k-1]='O';
        }
        else{
            cout << "\033[0;31mInvalid choice. Please Try another!\033[0m" << endl;
            goto again2; //if choice is invalid take input again.
        }
    }
    turn++; //increase turn. so that, other player can get the turn
    if(check_result() == 1){
        //increase all property related to player1 wins
        match.player1_win++;
        match.played++;
        print_board();
        cout << endl;
        cout << "\t\033[0;33m" << player1 << " has won the match!!!\033[0m\n\tCongratulation " << player1 << ", bad luck " << player2 << endl;
        saveInfo(player1); //save the info
        return;
    }
    else if(check_result() == 2){
        //increase all property related to player2 wins
        match.player2_win++;
        match.played++;
        print_board();
        cout << endl;
        cout << "\t\033[0;33m" << player2 << " has won the match!!!\033[0m\n\tCongratulation " << player2 << ", bad luck " << player1 << endl;
        saveInfo(player2); //save the info
        return;
    }
    else if(check_result() == 0){ //the game is draw
        match.played++;
        match.draw++;
        print_board();
        cout << endl;
        cout << "\t\033[0;95mOpps! It's a DRAW!\033[0m" << endl;
        saveInfo("DRAWN");
        return;
    }
    play(); //recursively call play() function
}

void game(){ //game starts with this function
    system("cls");
    int playAgain = 1;
    take_user(); //take two players name first
    while(playAgain){
        for(int i=0, j=49; i<9; j++, i++){
            mark[i] = j; //make the board blank (contains 1 to 9)
        }
        play();
        cout << "\t\033[0;92mDo you want to play again? (1=Yes, 0=No)\033[0m\n\t";
        cin >> playAgain;
    }
    match.draw=0;
    match.played=0;
    match.player1_win=0;
    match.player2_win=0;
    main_menu();
}

bool ifInvalid=false;
void main_menu(){ //main menu appearing function
    system("cls");
    title("TIC TAC TOE - Main Menu");
    //if user press invalid choice then show this msg
    if(ifInvalid==true){cout << "\t\t\033[0;91mInvalid choice. Try again!\033[0m" << endl; ifInvalid=false;}
    //print all options with coloring
    cout << "\t\t----------------------------" << endl;
    cout << "\t\t\033[0;33m\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\033[0m 1. START GAME     \033[0;33m\xdb\033[0m" << endl;
    cout << "\t\t----------------------------" << endl;
    cout << "\t\t\033[0;32m\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\033[0m 2. RESULT HISTORY \033[0;32m\xdb\033[0m" << endl;
    cout << "\t\t----------------------------" << endl;
    cout << "\t\t\033[0;95m\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\033[0m 3. ABOUT          \033[0;95m\xdb\033[0m" << endl;
    cout << "\t\t----------------------------" << endl;
    cout << "\t\t\033[0;31m\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\033[0m 4. EXIT           \033[0;31m\xdb\033[0m" << endl;
    cout << "\t\t----------------------------" << endl;
    cout << "\n\t\tEnter Your Choice: ";

    choice = getch(); //take user input
    if(choice=='0'+1) game(); //convert it in Integer and check
    else if(choice=='0'+2) history();
    else if(choice=='0'+3) about();
    else if(choice=='0'+4) return;
    else{ //invalid choice
        ifInvalid=true;
        main_menu();
    }
}

void about(){ //about displaying function
    system("cls");
    title("TIC TAC TOE - About");
    cout << "\n\t";
    for(int i=0; i<60; i++){cout << "\xdb";}
    cout << "\n\t\xdb                                                          \xdb";
    cout << "\n\t\xdb \033[0;33mApp Name:\033[0m Tic Tac Toe Game (Double Player)               \xdb";
    cout << "\n\t\xdb \033[0;33mCreator and Programmer:\033[0m MIR ANUPAM HOSSAIN AKIB          \xdb";
    cout << "\n\t\xdb \033[0;33mProgramming Language Used:\033[0m C++                           \xdb";
    cout << "\n\t\xdb \033[0;33mDate:\033[0m 9th January, 2020 (11:02 PM) BDT                   \xdb";
    cout << "\n\t\xdb \033[0;33mEmail:\033[0m mirakib25@gmail.com                               \xdb";
    cout << "\n\t\xdb \033[0;33mLocation:\033[0m Mirpur, Dhaka, Bangladesh, Earth               \xdb";
    cout << "\n\t\xdb \033[0;33mTags:\033[0m Anupam's Personal Project, 3rd semester            \xdb";
    cout << "\n\t\xdb                                                          \xdb";
    cout << "\n\t\xdb \033[0;92mUseful links\033[0m                                             \xdb";
    cout << "\n\t\xdb \033[0;92m------------\033[0m                                             \xdb";
    cout << "\n\t\xdb \033[0;33mMy Github:\033[0m https://github.com/AnupamAkib                 \xdb";
    cout << "\n\t\xdb \033[0;33mCodeforces:\033[0m http://codeforces.com/profile/anupam.akib    \xdb";
    cout << "\n\t\xdb \033[0;33mFacebook:\033[0m http://facebook.com/anupam.akib                \xdb";
    cout << "\n\t\xdb                                                          \xdb\n\t";
    for(int i=0; i<60; i++){cout << "\xdb";}
    cout << "\n\n\t\033[0;91mPress any key to go back \033[0m";
    char s = getch();
    if(s){
        main_menu(); //when user press any key, goto main menu.
    }
}

void history(){ //this function display game result history
    system("cls");
    title("TIC TAC TOE - History");
    char data[500][150];
    int cnt=0;
    //collecting data from 'history.txt' file and keep data in 'data' array
    file = fopen("history.txt", "r");
    while(fgets(data[cnt], 100, file)!= NULL){ //retrive all history data from file
        cnt++;
    }
    fclose(file);
    if(cnt==0){ //if the file is empty or not created yet
        cout << "\n\tNo History Available. Play some game first." << endl;
    }
    else{
        for(int i=0; i<cnt; i+=3){ //showing history
            cout << "\t\033[0;92mMatch: \033[0m" << data[i];
            cout << "\t\033[0;91mResult: \033[0m" << data[i+1];
            cout << "\t\033[0;33mTime: \033[0m" << data[i+2];
            cout << "\t---------------------------------------" << endl;
        }
    }
    cout << "\n\n\t\033[0;91mPress any key to go back \033[0m";
    char s = getch();
    if(s){
        main_menu();
    }
}

///main function
int main(){
    system("cls");
    //show main menu by default
    main_menu();
    return 0;
}



























