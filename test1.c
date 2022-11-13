#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "test2.c"

int main(){
    int choose;
    char arr[20], container[20];

    do{
        printf("\n\nOperation Menu\n");
        printf("[1] Print\n");
        printf("[2] Warning\n\n");

        printf("Enter Operation: ");
        scanf("%d", &choose);

        switch (choose){
        case 1:
            printf("Enter string:\n");
            fflush(stdin);
            gets(arr);
            system("cls");
            strcpy(container, printPhrase(arr));
            system("cls");
            printf("\n\n%s", container);
            getch();
            break;
        // case 2:
        //     system("cls");
        //     printWarn();
        //     break;
        } 
    }while(choose);

    return 0;
}