#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


void adminPage();
void registerPage();
void mngAcc();
int main();
int choose;

struct form{
  char firstName[30];
  char lastName[30];
  char username[30];
  char password[20];
};

//---------------------------------------------

void OUsersPage(){

  do{
    printf("\nOrdinary Users Page\n");
    printf("===============================\n");
    printf("[1] Barrow Equipment\n");
    printf("[2] Return Equipment\n");
    printf("[3] Change Personal Password\n");
    printf("[4] Exit");
    printf("\n===============================\n");

    printf("Enter option to proceed: ");
    scanf("%d", &choose);

    switch(choose) {
      case 4:
        system("cls");
        main();
      default:
        system("cls");
        printf("\nInvalid Operation!\n\nPress Enter to go back...");
        getch();
        system("cls");
        OUsersPage();
        break;

    }
  }while(choose);
}

//---------------------------------------------

void mngStaff(){

  do{
    printf("\nManage Staff Page\n");
    printf("===============================\n");
    printf("[111] List all Staff\n");
    printf("[112] Add New Staff\n");
    printf("[113] Edit Staff Details\n");
    printf("[114] Back");
    printf("\n===============================\n\n");

    printf("Enter operation: ");
    scanf("%d", &choose);

    switch(choose) {
      case 114:
        system("cls");
        mngAcc();
        break;
      default:
        system("cls");
        printf("\nInvalid Operation!\n\nPress Enter to go back...");
        getch();
        system("cls");
        mngStaff();
        break;
    }
  }while(choose);

}

void mngOu(){
   do{
    printf("\nManage Ordinary User Page\n");
    printf("===============================\n");
    printf("[121] List all OU\n");
    printf("[122] Edit OU Details\n");
    printf("[123] Back");
    printf("\n===============================\n\n");

    printf("Enter operation: ");
    scanf("%d", &choose);

    switch(choose) {
      case 123:
        system("cls");
        mngAcc();
        break;
      default:
        system("cls");
        printf("\nInvalid Operation!\n\nPress Enter to go back...");
        getch();
        system("cls");
        mngOu();
        break;
    }
  }while(choose);
}

//--------------------------------------------

void mngAcc(){

  do{
    printf("\nAccount Management\n");
    printf("===============================\n");
    printf("[11] Manage Staff\n");
    printf("[12] Manage Ordinary User\n");
    printf("[13] Back");
    printf("\n===============================\n");

    printf("Enter Operation: ");
    scanf("%d", &choose);

    switch(choose){
      case 11:
        system("cls");
        mngStaff();
        break;
      case 12:
        system("cls");
        mngOu();
        break;
      case 13:
        system("cls");
        adminPage();
        break;
      default:
        system("cls");
        printf("\nInvalid Operation!\n\nPress Enter to go back...");
        getch();
        system("cls");
        mngAcc();
        break;
  }
  }while(choose);
  
}

void mngEquip(){
  do{
    printf("\nManage Equipment\n");
    printf("===============================\n");
    printf("[21] List of all Equipments\n");
    printf("[22] Add New Equipment\n");
    printf("[23] Edit Equipment\n");
    printf("[24] Delete Equipment\n");
    printf("[25] Back\n");
    printf("\n===============================\n");

    printf("Enter Operation: ");
    scanf("%d", &choose);

    switch(choose){
      case 25:
        system("cls");
        adminPage();
        break;
      default:
        system("cls");
        printf("\nInvalid Operation!\n\nPress Enter to go back...");
        getch();
        system("cls");
        mngEquip();
        break;
  }
  }while(choose);
}

void adminPass(){
  char newPass[20];
  printf("\nChange Personal Password\n");
  printf("\nNew Password: \n");
  fflush(stdin);
  gets(newPass);
  printf("\nRepeat Password: \n");
  fflush(stdin);
  gets(newPass);

  system("cls");
  adminPage();
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

    printf("Enter operation: ");
    scanf("%d", &choose);

    switch (choose) {
      case 1:
        system("cls");
        mngAcc();
        getch();
        break;
      case 2:
        system("cls");
        mngEquip();
        break;
      case 3:
        system("cls");
        adminPass();
        break;
      case 4:
        system("cls");
        main();
        break;
      default:
        system("cls");
        printf("\nInvalid Operation!\n\nPress Enter to go back...");
        getch();
        system("cls");
        adminPage();
        break;


    }
  }while(choose);
}

//---------------------------------------------

void loginPage(){
  char adminUser[] = {"Christian"}, adminPass[] = {"Admin"};
  char choose, username[30], password[20];

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
  

  while(fread(&login, sizeof(login), 1, log)){
    if(strcmp(adminUser, username) == 0 && strcmp(adminPass, password) == 0 ){
      system("cls");
      adminPage();
    }
    if(strcmp(username, login.username) == 0 && strcmp(password, login.password) == 0 ){
      system("cls");
      OUsersPage();
    }else{

      system("cls");
      printf("\nIncorrect Username or Password...");
      printf("\n\nWant to try again?\n");
      printf("==================\n");
      printf("[Y] Re-login\n");
      printf("[N] Exit to Main Menu\n");
      printf("==================\n");

      printf("Enter Operation: ");
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
  printf("\nPress Enter to go back...");
  system("cls");
  main();
  getch();
}

//Frist Screen--------------------------------------------------

int main(){
  char choose;

  do{

    printf("\nDo you already have an account?\n");
    printf("=========================\n");
    printf("[Y] Login\n");
    printf("[N] Register");
    printf("\n=========================\n");

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
      // system("cls");
      // printf("\n[%c] You have entered the wrong key!\n\n", choose);
      // printf("Press enter to go back...");
      // getch();
      // system("cls");
        system("cls");
        printf("\nInvalid Operation!\n\nPress Enter to go back...");
        getch();
        system("cls");
        main();
        break;
    }
  }while(choose);
  return 0;
}
