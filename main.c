/* 
    retrieve file
    display menu - (add, display, save and exit)
    if add
        prompt user for name, date of birth, and account balance
        generate client number and account number
        add data to data structure
    if display
        display all client details
    if save and exit
        save to a file and exit program
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>                   // library for srand 
#include <malloc.h>
#include <string.h>
#include <windows.h>

typedef struct rec
{
    char name[51], dob[11];         //date of birth
    int aNum;                 //client number, account number
    long long int balance;          //account balance
}REC;

typedef struct list
{
    REC srec;
    struct list * next; //changed node to list said by rams - 6:32 PM 4/10
}LIST;


LIST *l;

void init()
{
    l = NULL;
}
int isEmpty()
{
    return(l == NULL);
}

//Operations
void getrec(REC *acc);
void add(REC acc);
void display();
void savefile();
void retrievefile();
int menu();
void gotoxy(int x, int y);
int cNum;

//Initialization of Main Function
int main(void)
{
    REC user;
    init();
    retrievefile();

    system("color 06");
    while(1)
    {
        switch (menu())
        {
            case 1: getrec(&user); add(user); break;
            case 2: display(); break;
            case 3: savefile(); exit(0); 
            default: printf("OUT OF RANGE. PRESS 1-4 ONLY."); system("pause"); fflush(stdin); break;
        }
    }
}

void getrec(REC *acc)
{
    system("cls");
    gotoxy(5, 1); printf(".-------------------------------------------------------------------------------------------------------------.");
    gotoxy(5, 2); printf("|                                        INPUT BANK USER INFORMATION                                          |");
    gotoxy(5, 3); printf("|                                 Currently adding new input in bank record                                   |");
    gotoxy(5, 4); printf("|                                                                                                             |");
    gotoxy(5, 5); printf("|                           Instruction: Enter the name of the user and information                           |");
    gotoxy(5, 6); printf(".-------------------------------------------------------------------------------------------------------------.");
    srand(time(NULL));
    acc->aNum = rand() % 90000 + 10000;
    gotoxy(48, 8); printf("Account # %d\n", acc->aNum);
    gotoxy(48, 9); printf("Name: "); scanf(" %[^\n]s", acc->name);
    gotoxy(48, 10); printf("Date of Birth (MM/DD/YYYY): "); scanf(" %[^\n]s", acc->dob);
    gotoxy(48, 11); printf("Balance: "); scanf("%lld", &acc->balance);

}

void add(REC acc)
{
    LIST *p, *q, *newnode;
    p = q = l;

    newnode = (LIST*) malloc(sizeof(LIST));
    newnode->srec = acc;

    while(p != NULL)
    {
        q = p;
        p = p->next;
    }

    if(p == l)
    {
        l = newnode;
    }
    else
    {
        q->next = newnode;
    }
    newnode->next = p;
}


void savefile()
{
    FILE *fp;
    LIST *p;
    p = l;
    int cNum = 0;
    fp = fopen("clientsREC.csv", "w+");
    while(p!=NULL)
    {
        fprintf(fp, "%i,%s,%s,%d,%lld\n", ++cNum, p->srec.name, p->srec.dob, p->srec.aNum, p->srec.balance);
        p = p->next;
    }      
    fclose(fp);   
}

void retrievefile()
{   
    FILE *fp;
    REC s;

    fp = fopen("clientsREC.csv", "r+");
    if (fp == NULL)
    {
        printf("File error.\n");
        system("pause");
    }
    else
    {
        while(fscanf(fp, "%i,%[^,],%[^,],%d,%lld", &cNum, s.name, s.dob, &s.aNum, &s.balance) != EOF)
        {
            add(s);
        }
        fclose(fp);
    }
}

void display()
{
    LIST *p;
    p = l;
    int i = 0;
    system("cls");
    gotoxy(5, 1); printf(".-------------------------------------------------------------------------------------------------------------.");
    gotoxy(5, 2); printf("|                                                 BANK RECORDS                                                |");
    gotoxy(5, 3); printf("|                                   Currently viewing bank users information                                  |");
    gotoxy(5, 4); printf(".-------------------------------------------------------------------------------------------------------------.");

    //Prints the table
    gotoxy(22, 7); printf("Client #");
    gotoxy(35, 7); printf("Name/s");
    gotoxy(58, 7); printf("Date of Birth");
    gotoxy(74, 7); printf("Account #");
    gotoxy(88, 7); printf("Balance");

    while(p != NULL)
    {
        ++i;
        //Prints the user input
        gotoxy(25, 8+i); printf("%d", i);
        gotoxy(35, 8+i); printf("%s", p->srec.name);
        gotoxy(58, 8+i); printf("%s", p->srec.dob);
        gotoxy(74, 8+i); printf("%d", p->srec.aNum);
        gotoxy(88, 8+i); printf("%lld", p->srec.balance);
        p = p -> next;

    }
    gotoxy(45, 9 + i + 1); system("pause");
}

int menu()
{
    system("cls");
    int choice;
    gotoxy(12, 4);  printf(".-----------------------------------------------------------------------------------------------.");
    gotoxy(12, 5);  printf("|                                       Bank Raft Co.                                           |");
    gotoxy(12, 6);  printf("|-----------------------------------------------------------------------------------------------|");
    gotoxy(12, 7);  printf("|                             Instruction: Choose from 1-3 only!                                |");
    gotoxy(12, 8);  printf("|                                                                                               |");
    gotoxy(12, 9);  printf("|                        [1] Bank Register       [2]  Display Records                           |");
    gotoxy(12, 10); printf("|                                                                                               |");
    gotoxy(12, 11); printf("|                                 [3] Save and Exit Program                                     |");
    gotoxy(12, 12); printf("|                                                                                               |");
    gotoxy(12, 13); printf(".-----------------------------------------------------------------------------------------------.");
    gotoxy(12, 14); printf("                               PRESS THE CORRESPONDING NUMBER: ");
    scanf("%d", &choice);
    return choice;
}

void gotoxy(int x, int y)
{
    COORD coord = {0,0};
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}