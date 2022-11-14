#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char* printPhrase(char arr[]){
    char *arr2 = calloc(20, sizeof(char));

    printf("\nEnter arr2:\n");
    fflush(stdin);
    gets(arr2);
    

    return arr2;
}