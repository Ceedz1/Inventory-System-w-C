#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "test2.c"

int main(){
    char arr[20], container[20];

    printf("\nEnter string:\n");
    fflush(stdin);
    gets(arr);
    system("cls");
    strcpy(container, printPhrase(arr));
    system("cls");
    printf("\n\nReturn Value: %s", container);
    getch();


    return 0;
}