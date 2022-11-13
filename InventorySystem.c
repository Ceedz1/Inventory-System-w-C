#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


void mainPage();
void registerPage();
int main();
int choose;

struct form{
  char firstName[30];
  char lastName[30];
  char username[30];
  char password[20];
};

//---------------------------------------------

// void staffPage(){
//
//   do{
//     printf("\nStaff Page\n");
//     printf("===============================\n");
//     printf("[1] Borrow Equipment\n");
//     printf("[2] Return Equipment\n");
//     printf("[3] Change Personal Password\n");
//     printf("[4] Exit");
//     printf("\n===============================\n\n");
//
//     printf("Enter option to proceed: ");
//     scanf("%d", &choose);
//
//     switch(choose) {
//       case 4:
//         system("cls");
//         mainPage();
//
//     }
//   }while(choose);
//
// }

//--------------------------------------------

void OUsersPage(){

  do{
    printf("\nOU Page\n");
    printf("===============================\n");
    printf("[1] Request for Borrowing Equipment\n");
    printf("[2] Request for Returning Equipment\n");
    printf("[3] Change Personal Password\n");
    printf("[4] Exit");
    printf("\n===============================\n\n");

    printf("Enter option to proceed: ");
    scanf("%d", &choose);

    switch(choose) {
      case 4:
        system("cls");
        main();

    }
  }while(choose);
}

//---------------------------------------------

void mngAcc(){
  printf("\nAccount Management\n");
  printf("===============================\n");
  printf("[11] Manage Staff\n");
  printf("[22] Manage Ordinary User\n");
  printf("[33] Back");
  printf("\n===============================\n\n");
}

void mngEquip(){
  printf("\nNothing for now");
  printf("");
}

void persPass(){
  char newPass[20];
  printf("\nChange Personal Password\n");
  printf("\nNew Password: \n");
  gets(newPass);
  printf("\nRepeat Password");
  gets(newPass);

}

//---------------------------------------------

void adminPage(){

  do{
    printf("\nAdmin Main Page\n");
    printf("===============================\n");
    printf("[1] Manage Accounts\n");
    printf("[2] Manage Equipments\n");
    printf("[3] Change Personal Password\n");
    printf("[4] Exit");
    printf("\n===============================\n\n");

    printf("Enter option to proceed: ");
    scanf("%d", &choose);

    switch (choose) {
      case 1:
        system("cls");
        mngAcc();
        break;
      case 2:
        system("cls");
        mngEquip();
        break;
      case 3:
        system("cls");
        persPass();
        break;
      case 4:
        system("cls");
        main();
        break;

    }
  }while(choose);
}

// //--------------------------------------------
//
// void mainPage(){
//
//   do{
//     printf("\nAdmin Main Page\n");
//     printf("===============================\n");
//     printf("[1] Administrator\n");
//     printf("[2] Ordinary Users\n");
//     printf("[3] Staff\n");
//     printf("[4] Exit\n");
//     printf("===============================\n\n");
//
//     printf("Enter option to proceed: ");
//     scanf("%d", &choose);
//
//     switch(choose) {
//       case 1:
//         printf("\n[1] Administrator Selected!\n");
//         system("cls");
//         adminPage();
//         getch();
//         break;
//       case 2:
//         printf("[2] Ordinary Users Selected!\n");
//         system("cls");
//         OUsersPage();
//         getch();
//
//         break;
//       case 3:
//         printf("[2] Staff Selected!\n");
//         system("cls");
//         staffPage();
//         getch();
//         break;
//       case 4:
//         system("cls");
//         main();
//         getch();
//         break;
//     }
//   }while(choose);
//
// }

//---------------------------------------------

void loginPage(){
  char adminUser[] = {"Christian"}, adminPass[] = {"Administrator"};
  char username[30], password[20], choose;
  FILE *log;

  log = fopen("login.txt", "r");
  if(log == NULL){
    fputs("\nPlease Create an Account First", stderr);
    fputs("\n\n\npress any key to go back...", stderr);
    getch();
    system("cls");
    main();
  }

  struct form login;

  fflush(stdin);
  printf("\nEnter Username: \n");
  //fgets(username, 30, stdin);
  gets(username);

  fflush(stdin);
  printf("Enter Password: \n");
  //fgets(password, 20, stdin);
  gets(password);
  system("cls");

  while(fread(&login, sizeof(login), 1, log)){
    if(strcmp(adminUser, username) == 0 && strcmp(adminPass, password) == 0 ){
      adminPage();
    }
    if(strcmp(username, login.username) == 0 && strcmp(password, login.password) == 0 ){
      OUsersPage();
    }else{
      system("cls");
      printf("\nIncorrect Username or Password...");
      printf("\n\nWant to try again?\n");
      printf("==================\n");
      printf("[Y] Re-login\n");
      printf("[N] Exit to Main Menu\n");
      printf("==================\n");
      printf("Enter Operation to proceed: ");
      scanf("%c", &choose);

      if(choose == 'Y' || choose == 'y'){
        system("cls");
        loginPage();
        getch();
      }

      if(choose == 'N' || choose == 'n'){
        system("cls");
        main();
        getch();
      }
    }
  }
}

//------------------------------------------------------------

void registerPage(){
  char firstName[50];
  int checku, checkp;

  FILE *log;

  log=fopen("login.txt", "w");
  if(log == NULL){
    fputs("Error at opening File!", stderr);
    getch();
    system("cls");
    main();
  }

  struct form registration;

  fflush(stdin);
  printf("\nEnter your First Name:\n");
  gets(registration.firstName);
  fflush(stdin);
  printf("\nEnter your Last Name:\n");
  gets(registration.lastName);
  fflush(stdin);
  printf("\nEnter your Username:\n");
  gets(registration.username);
  fflush(stdin);
  printf("\nEnter your Password:\n");
  gets(registration.password);

  fwrite(&registration, sizeof(registration), 1, log);
  fclose(log);

  printf("Account Successfully Created!\n");
  printf("\npress any key to go back...");
  system("cls");
  main();
  getch();
}

//--------------------------------------------------

int main(){
  char choose;

  do{

    printf("\nDo you already have an account?\n");
    printf("=========================\n");
    printf("[Y] to Login\n");
    printf("[N] to Registration");
    printf("\n=========================\n\n");
    printf("Enter Operation: ");
    scanf(" %c", &choose);

    if(choose == 'Y' || choose == 'y'){
      system("cls");
      loginPage();
      getch();

    }
    if(choose == 'N' || choose == 'n'){
      system("cls");
      registerPage();
      getch();

    }else{
      printf("You have entered the wrong [key]!\n\n");
      printf("Press enter to continue...");
      getch();
      system("cls");
    }
  }while(choose);
  return 0;
}
