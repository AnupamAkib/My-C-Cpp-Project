#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    char title[500];
    char details[1000];
} information;

information text[500];
FILE *file;
int cnt=0;

void title(char s[1000]){
    printf("\n\n\033[0;36mTITLE: \033[0m%s", s);
    for(int i=0; i<strlen(s)+6; i++){
        printf("-");
    }
    printf("\n");
}

void retrive_data(){
    cnt=0;
    char temp[500][1000];
    file=fopen("note.txt", "r");
    while(fgets(temp[cnt], 1000, file)!=NULL){
        cnt++;
    }
    fclose(file);
    for(int i=0, j=0; i<cnt; i+=2, j++){
        strcpy(text[j].title, temp[i]);
        strcpy(text[j].details, temp[i+1]);
    }
}

void add(){
    char ttl[500], dtls[1000];
    printf("\033[0;36m\n\n\tADD A NEW NOTE\n\t==============\n\033[0m");
    printf("\t\033[0;32mYour Title: \033[0m");
    gets(ttl);
    printf("\t\033[0;32mDescription: \033[0m");
    gets(dtls);
    file=fopen("note.txt", "a");
    fprintf(file, "%s\n", ttl);
    fprintf(file, "%s\n", dtls);
    fclose(file);
    notepad(1);
}

void notepad(int flag){
    system("cls");
    retrive_data();
    printf("\033[0;33m\n\t\t\t\t  SIMPLE NOTEPAD FOR ALL\n\t\t\t\t--------------------------\033[0m");
    for(int i=0; i<cnt/2; i++){
        title(text[i].title);
        printf("%s", text[i].details);
    }
    if(flag==1){
        printf("\033[0;32m\n\tYour Note has been added successfully\033[0m");
    }
    add();
}

int main(){
    notepad(0);
    getch();
    return 0;
}

















