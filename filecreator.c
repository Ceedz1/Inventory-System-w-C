#include <stdio.h>
#include <stdlib.h>

struct form{
    char username[30];
    char password[20];
};

int main(){
struct form add;

FILE *fptr;

if((fptr = fopen("adminAcc.txt", "a")) == NULL){
    printf("\nError Opening File!");
}

printf("\nUsername: ");
fflush(stdin);
gets(add.username);
printf("Password: ");
fflush(stdin);
gets(add.password);

fwrite(&add, sizeof(struct form), 1, fptr);

fclose(fptr);

    return 0;
}