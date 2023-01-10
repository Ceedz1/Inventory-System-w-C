#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

struct form{
    int rNum;
    int qty;
    char availability[20];
    char firstName[30];
    char lastName[30];
    char username[30];
    char password[20];
    char status[10];
    char roles[10];
};

int main(){
    struct form addAdmin;

    FILE *fptr;

    if((fptr = fopen("adminAcc.txt", "w")) == NULL){
        return 1;
    }

    printf("rollNo: ");
    fflush(stdin);
    scanf("%d", &addAdmin.rNum);
    printf("\nusername: ");
    fflush(stdin);
    scanf("%s", &addAdmin.username);
    printf("\npassword: ");
    fflush(stdin);
    scanf("%s", &addAdmin.password);
    strcpy(addAdmin.roles, "Admin");

    fwrite(&addAdmin, sizeof(struct form), 1, fptr);
    fclose(fptr);
}