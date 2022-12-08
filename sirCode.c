#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void addData();
void displayData();
void findData();


int main(){
    int choose = 0;

    do{
        printf("\n\nMenu Operation\n");
        printf("-------------------\n");
        printf("[1] Add Data\n");
        printf("[2] Display Data\n");
        printf("[3] Find Data\n");
        printf("-------------------\n");
        printf("Enter Operation: ");
        scanf("%d", &choose);

        switch(choose){
            case 1:
                addData();
                break;
            case 2:
                displayData();
                break;
            case 3:
                findData();
                break;
        }
    }while(choose);
    return 0;
}

void addData(){
    char csv[100];
    char fName[50];
    char lName[50];
    char age[10];

    FILE *fptr;

    if((fptr = fopen("program.txt", "a")) == NULL){
        printf("\nERROR!");
        exit(1);
    }

    printf("\nFirst Name: ");
    fflush(stdin);
    gets(fName);
    printf("\nLast Name: ");
    fflush(stdin);
    gets(lName);
    printf("\nAge: ");
    fflush(stdin);
    gets(age);

    strcpy(csv,"");
    strcat(csv, fName);
    strcat(csv, ",");
    strcat(csv, lName);
    strcat(csv, ",");
    strcat(csv, age);
    strcat(csv, "\n");

    puts(csv);
    fputs(csv, fptr);
    fclose(fptr);
    
   
}

void displayData(){
    char csv[100];

    FILE *fptr;

    if((fptr = fopen("program.txt", "r+")) == NULL){
        printf("Error! Opening File");
        exit(1);
    }

    fgets(csv, 200, fptr);
    puts(csv);
    fclose(fptr);
}

void findData(){
    char csv[100];
    char fName[50];
    char lName[50];
    char age[10];

    int a,b,c;

    FILE *fptr;

    if((fptr = fopen("program.txt", "r+")) == NULL){
        printf("Error! Opening File");
        exit(1);
    }

    printf("Enter First Name: ");
    fflush(stdin);
    gets(fName);

    while(fgets(csv, 200, fptr)){
        for(a = 0; a < strlen(csv); a++){
            if(csv[a] == ',')
                break;
            printf("%c", csv[a]);
        }
        printf("\n");

        for(c = b + 1; c < strlen(csv); c++){
            if(csv[c] == ',')
                break;
            printf("%c", csv[c]);
        }
        printf("\n");
    }
}