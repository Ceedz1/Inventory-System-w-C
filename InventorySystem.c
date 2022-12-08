#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


void adminPage();
void registerPage();
void mngAcc();
void mngStaff();
int main();
int choose;



struct form{
  int rNum;
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
        break;
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

int checkAvailRoll(int rollNo){
  struct form rollNumCheck;
  
  FILE *fptr;

  fptr = fopen("staffList.txt", "r");
  while(!feof(fptr)){
    fread(&rollNumCheck, sizeof(struct form), 1, fptr);

    if(rollNo == rollNumCheck.rNum){
      fclose(fptr);
      return 1;
    }
  }
  
  getch();
  fclose(fptr);
  return 0;
}

void editStaff(){
  int available, rollNo, save;

  struct form update;

  FILE *fptr;
  FILE *ftemp;

  printf("\nUpdate Staff Page");
  printf("\n=========================\n");
  printf("Enter Roll Number to update: \n");
  fflush(stdin);
  scanf("%d", &rollNo);
  
  available = checkAvailRoll(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    editStaff();
  }else{
    fptr = fopen("staffList.txt", "r");
    ftemp = fopen("tempFile.txt", "w");

    while(fread(&update, sizeof(struct form), 1, fptr)){
      save = update.rNum;
      if(save != rollNo){
        fwrite(&update, sizeof(struct form), 1, ftemp);
      }else{
        printf("\nWhich to Update");
        printf("\n=========================\n");
        printf("[1] Roll Number\n");
        printf("[2] First/Last Name\n");
        printf("[3] Email\n");
        printf("[4] Password\n");
        printf("[5] Back\n");
        printf("=========================\n");

        printf("Enter Operation: ");
        scanf("%d", &choose);

        switch(choose){
          case 1:
            printf("\nRoll Number: \n");
            fflush(stdin);
            scanf("%d", &update.rNum);
            break;
          case 2:
            printf("\nFirst Name: \n");
            fflush(stdin);
            gets(update.firstName);
            printf("\nLast Name: \n");
            fflush(stdin);
            gets(update.lastName);
            break;
          case 3:
            printf("\nEmail: \n");
            fflush(stdin);
            gets(update.username);
            break;
          case 4:
            printf("\nPassword: \n");
            fflush(stdin);
            gets(update.password);
            break;
          case 5:
            mngStaff();
            break;
        }
        fwrite(&update, sizeof(struct form), 1, ftemp);
      }
    }
    fclose(fptr);
    fclose(ftemp);
    fptr = fopen("staffList.txt", "w");
    ftemp = fopen("tempFile.txt", "r");

    while(fread(&update, sizeof(struct form), 1, ftemp)){
      fwrite(&update, sizeof(struct form), 1, fptr);
    }
    fclose(fptr);
    fclose(ftemp);
    printf("\n\nUpdate Success!");
    getch();
  } 

}

void allStaff(){
  FILE *fptr;

  struct form input;

  /*** open the accounts file ***/
  fptr = fopen ("staffList.txt","r");
  if(fptr == NULL){
    fprintf(stderr, "\nError opening accounts.dat\n\n");
    mngStaff();
  }

  printf("\nNo.   First Name      Last Name       Email                     Password\n");
  printf("==========================================================================\n");
  while (fread(&input, sizeof(struct form), 1, fptr))
  printf ("%-5d %-15s %-15s %-25s %-15s\n", input.rNum, input.firstName, input.lastName, input.username, input.password);

  fclose(fptr);
  printf("\n\nPress any key to continue...");
  getch();
}

void addStaff(){
  struct form staffLists;

  staffLists.rNum = 0;

  FILE *fptr;

  if((fptr = fopen("staffList.txt", "a")) == NULL){
    printf("\n[Error Opening file!]");
    mngStaff();
  }

  printf("\nAdd Staff");
  printf("\n===========");
  printf("\nRoll Number:\n");
  fflush(stdin);
  scanf("%d", &staffLists.rNum);
  printf("First Name: \n");
  fflush(stdin);
  gets(staffLists.firstName);
  printf("Last Name: \n");
  fflush(stdin);
  gets(staffLists.lastName);
  printf("Email: \n");
  fflush(stdin);
  gets(staffLists.username);
  printf("Password: \n");
  fflush(stdin);
  gets(staffLists.password);

  fwrite (&staffLists, sizeof(struct form), 1, fptr);
  fclose(fptr);
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
      case 111:
        system("cls");
        allStaff();
        system("cls");
        break;
      case 112:
        system("cls");
        addStaff();
        system("cls");
        break;
      case 113:
        system("cls");
        editStaff();
        system("cls");
        break;
      case 114:
        system("cls");
        mngAcc();
        system("cls");
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
    fflush(stdin);
    scanf("%d", &choose);

    switch(choose){
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
  }while(choose != 0);
}

//---------------------------------------------

void loginPage(){
  char adminUser[] = {"Christian"}, adminPass[] = {"Admin"};
  char ch, choose, username[30], password[20];
  int i, size = 0;

  FILE *log;

  struct form login;

  printf("\nLogin Page");
  printf("\n================");
  printf("\nEnter Username: \n");
  fflush(stdin);
  gets(username);
  printf("Enter Password: \n");
  fflush(stdin);
  gets(password);

  log = fopen("OrdinaryUsers.txt", "r");
  

  
//password encryption '*'-----------------------------------

  // for(i = 0; i != 13; i++){
  //   ch=getch();
  //   password[i]=ch;
  //   printf("*");
  // }
  //  password[i] = '\0';
  // getch();
  // while(1){
  //   ch = getch();
  //   if(ch == 13){
  //     password[i]=NULL;
  //     break;
  //   }else if(if == TAB)

  //   }
//-----------------------------------------------------------
  
//check account if its an admin or OU
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
      fflush(stdin);
      scanf("%c", &choose);

      switch(choose){
        case 'Y':
        case 'y':
          system("cls");
          loginPage();
          getch();
          break;
        case 'N':
        case 'n':
          system("cls");
          main();
          getch();
          break;
      }
    }
  }
}

//------------------------------------------------------------

void registerPage(){
  int checku, checkp;

  FILE *log;

  log=fopen("OrdinaryUsers.txt", "w");
  if(log == NULL){
    fputs("Error at opening File!", stderr);
    getch();
    system("cls");
    main();
  }

  struct form registration;

  printf("\nRegister Page\n");
  printf("======================\n");
  fflush(stdin);
  printf("Enter your First Name:\n");
  gets(registration.firstName);
  fflush(stdin);
  printf("Enter your Last Name:\n");
  gets(registration.lastName);
  fflush(stdin);
  printf("Enter your Username:\n");
  gets(registration.username);
  fflush(stdin);
  printf("Enter your Password:\n");
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
    fflush(stdin);
    scanf("%c", &choose);

    switch(choose){
      case 'Y':
      case 'y':
        system("cls");
        loginPage();
        system("cls");
        break;
      
      case 'N':
      case 'n':
        system("cls");
        registerPage();
        break;
      default:
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
