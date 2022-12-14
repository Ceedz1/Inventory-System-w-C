#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void mngAcc();
void mngOu();
void OUsersPage();

int choose;

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

int checkOrdinaryUser(int rollNo){
  struct form rollNumCheck;
  
  FILE *fptr;

  if((fptr = fopen("ordinaryUsers.txt", "r")) == NULL){
    fprintf(stderr, "\nError opening file!\n\n");
    mngOu();
  }

  while(!feof(fptr)){
    fread(&rollNumCheck, sizeof(struct form), 1, fptr);

    if(rollNo == rollNumCheck.rNum){
      fclose(fptr);
      return 1;
    }
  }
  fclose(fptr);
  return 0;
}

void deleteOrdinary(){
  int available, rollNo, save;

  struct form delete;

  FILE *fptr;
  FILE *ftemp;

  if((fptr = fopen("ordinaryUsers.txt", "r")) == NULL){
    fprintf(stderr, "\nError opening file!\n\n");
    mngOu();
  }

  printf("\nDelete Ordinary User Page\n");
  printf("=====================================================================================================");
  printf("\nNo.   First Name      Last Name       Email                  Roles           Password        Status\n");
  printf("=====================================================================================================\n");
  while (fread(&delete, sizeof(struct form), 1, fptr))
    printf ("%-5d %-15s %-15s %-22s %-15s %-15s %-15s\n", delete.rNum, delete.firstName, delete.lastName, delete.username, delete.roles, delete.password, delete.status);
  
  fclose(fptr);

  printf("\nEnter Roll Number to Delete: ");
  fflush(stdin);
  scanf("%d", &rollNo);

  available = checkOrdinaryUser(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    mngOu();
  }else{
    fptr = fopen("ordinaryUsers.txt", "r");
    ftemp = fopen("tempOrdinaryUser.txt", "w");

    while(fread(&delete, sizeof(struct form), 1, fptr)){
      save = delete.rNum;

      if(save != rollNo){
        fwrite(&delete, sizeof(struct form), 1, ftemp);
      }
    }
    fclose(fptr);
    fclose(ftemp);

    remove("ordinaryUsers.txt");
    rename("tempOrdinaryUser.txt", "ordinaryUsers.txt");

    printf("\n\nDeleted Succesfully!");
    getch();
  }
}


void editOrdinary(){
  int available, rollNo, save;

  struct form update;

  FILE *fptr;
  FILE *ftemp;

  if((fptr = fopen("ordinaryUsers.txt", "r")) == NULL){
    fprintf(stderr, "\nError opening file!\n\n");
    mngOu();
  }
  
  printf("\nUpdate Ordinary User Page\n");
  printf("=====================================================================================================");
  printf("\nNo.   First Name      Last Name       Email                  Roles           Password        Status\n");
  printf("=====================================================================================================\n");
  while (fread(&update, sizeof(struct form), 1, fptr))
    printf ("%-5d %-15s %-15s %-22s %-15s %-15s %-15s\n", update.rNum, update.firstName, update.lastName, update.username, update.roles, update.password, update.status);
  fclose(fptr);

  printf("\nEnter Roll Number to update: ");
  fflush(stdin);
  scanf("%d", &rollNo);
  
  available = checkOrdinaryUser(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    mngOu();
  }else{
    fptr = fopen("ordinaryUsers.txt", "r");
    ftemp = fopen("tempOrdinaryUser.txt", "w");

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
        printf("[5] Status\n");
        printf("[6] Back\n");
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
            printf("\nStatus: \n");
            fflush(stdin);
            gets(update.status);
            break;
          case 6:
            system("cls");
            mngOu();
            break;
        }
        fwrite(&update, sizeof(struct form), 1, ftemp);
      }
    }
    fclose(fptr);
    fclose(ftemp);
    fptr = fopen("ordinaryUsers.txt", "w");
    ftemp = fopen("tempOrdinaryUser.txt", "r");

    while(fread(&update, sizeof(struct form), 1, ftemp)){
      fwrite(&update, sizeof(struct form), 1, fptr);
    }
    fclose(fptr);
    fclose(ftemp);
    printf("\n\nUpdate Success!");
    getch();
  } 

}

void allOrdinary(){
  FILE *fptr;

  struct form display;

  fptr = fopen ("ordinaryUsers.txt","r");
  if(fptr == NULL){
    fprintf(stderr, "\nError opening accounts.dat\n\n");
    mngOu();
  }

  printf("\nNo.   First Name      Last Name       Email                  Roles           Password        Status\n");
  printf("=====================================================================================================\n");
  while (fread(&display, sizeof(struct form), 1, fptr))
    printf ("%-5d %-15s %-15s %-22s %-15s %-15s %-15s\n", display.rNum, display.firstName, display.lastName, display.username, display.roles, display.password, display.status);
  
  fclose(fptr);
  printf("\n\nPress any key to continue...");
  getch();
}

void addOrdinary(){
  char roles[] = {"OU"}, disOrdinary[] = {"Disable"};

  struct form ordinary;

  FILE *fptr;

  if((fptr = fopen("ordinaryUsers.txt", "a")) == NULL){
    printf("\n[Error Opening file!]");
    mngOu();
  }

  printf("\nAdd Ordinary User");
  printf("\n===========");
  printf("\nRoll Number:\n");
  fflush(stdin);
  scanf("%d", &ordinary.rNum);
  printf("First Name: \n");
  fflush(stdin);
  gets(ordinary.firstName);
  printf("Last Name: \n");
  fflush(stdin);
  gets(ordinary.lastName);
  printf("Email: \n");
  fflush(stdin);
  gets(ordinary.username);
  printf("Password: \n");
  fflush(stdin);
  gets(ordinary.password);

  strcpy(ordinary.status, disOrdinary);
  strcpy(ordinary.roles, roles);
  fwrite (&ordinary, sizeof(struct form), 1, fptr);
  fclose(fptr);

  printf("\n\nAdded Successfully!");
  getch();
}

void mngOu(){
   do{
    printf("\nManage Ordinary User Page\n");
    printf("===============================\n");
    printf("[121] List all Ordinary User\n");
    printf("[122] Edit Ordinary User Details\n");
    printf("[123] Delete Ordinary User\n");
    printf("[124] Add Ordinary User\n");
    printf("[125] Back");
    printf("\n===============================\n\n");

    printf("Enter operation: ");
    scanf("%d", &choose);

    switch(choose) {
      case 121:
        system("cls");
        allOrdinary();
        system("cls");
        break;
      case 122:
        system("cls");
        editOrdinary();
        system("cls");
        break;
      case 123:
        system("cls");
        deleteOrdinary();
        system("cls");
        break;
      case 124:
        system("cls");
        addOrdinary();
        system("cls");
        break;
      case 125:
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

//----------------------------------------------------------------------------------

void mngAcc(){

  do{
    printf("\nAccount Management\n");
    printf("===============================\n");
    // printf("[11] Manage Staff\n");
    printf("[12] Manage Ordinary User\n");
    // printf("[13] Back");
    printf("\n===============================\n");

    printf("Enter Operation: ");
    scanf("%d", &choose);

    switch(choose){
    //   case 11:
    //     system("cls");
    //     mngStaff();
    //     break;
      case 12:
        system("cls");
        mngOu();
        break;
    //   case 13:
    //     system("cls");
    //     adminPage();
    //     break;
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

int main(){

    mngAcc();

    return 0;
}