#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <unistd.h>
#include "test2.h"

#define ITEM_NAME_LEN 50
#define ITEM_QUANTITY_LEN 20
#define ITEM_FILE "equipments.txt"

void adminPage();
void registerPage();
int OUsersPage();
void mngAcc();
void mngOu();
void mngStaff();
void mngEquip();
void borrowEquip();
void loginPage();
int main();
int checkEquip(int rollNo);
int checkEquipReturn(int rollNo);
int checkOrdinaryUser(int rollNo);


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

static int file_initialized, i = 0;
int choose;

//----------------------------------------------------------------------------------
   
void borrowEquip(struct form *items, int num_items){
  char name[ITEM_NAME_LEN];
  int i, quantity;

  printf("Enter Item name: ");
  fflush(stdin);
  scanf("%s", &name);
  
  for(i = 0; i < num_items; i++){
    if(strcmp(name, items[i].firstName) == 0) {
        printf("Enter quantity: ");
        scanf("%d", &quantity);

        if (quantity > items[i].qty) {
            printf("Error: Not enough items in stock.\n");
        } else {
            items[i].qty -= quantity;
            printf("Successfully borrowed %d %s.\n", quantity, name);
        }
        return;
    }
  }
  
}

void returnEquip(struct form *items, int num_items){
  char name[ITEM_NAME_LEN];
  int i, quantity;

  struct form retEq;

  FILE *ftemp;
  FILE *fptr;

  if((ftemp = fopen("tempEquipment.txt", "r")) == NULL){
    printf("\n[Error Opening file!]");
    OUsersPage();
  }
  
  printf("\nReturn Equipments Page");
  printf("\n=======================================================================");
  printf("\nNo.   Name                      Status       Quantity      Availability\n");
  printf("=======================================================================\n");
  while (fread(&retEq, sizeof(struct form), 1, fptr))
    printf ("%-5d %-25s %-15s %-10d %-15s\n", retEq.rNum, retEq.firstName, retEq.status, retEq.qty, retEq.availability);

  fclose(ftemp);

  printf("Enter item name: ");
  fflush(stdin);
  scanf("%s", name);

  for(i = 0; i < num_items; i++) {
    if (strcmp(name, items[i].firstName) == 0) {
      printf("Enter quantity: ");
      scanf("%d", &quantity);
      items[i].qty += quantity;
      printf("Successfully returned %d %s.\n", quantity, name);
      return;
    }
  }
  printf("Error: Item not found.\n");
}

void changePersPassOU(){
  char newPass[20];
  int rollNo, available, save, value = 0;

  struct form chngPers;

  FILE *fptr;
  FILE *ftemp;

  printf("\nChange Personal Password");
  printf("\n========================");
  printf("\nEnter your Roll Number: ");
  scanf("%d", &rollNo);

  available = checkOrdinaryUser(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    OUsersPage();
  }else{
    fptr = fopen("ordinaryUsers.txt", "r");
    ftemp = fopen("tempOrdinaryUser.txt", "w");
    
    while(fread(&chngPers, sizeof(struct form), 1, fptr)){
      save = chngPers.rNum;

      if(save != rollNo){
        fwrite(&chngPers, sizeof(struct form), 1, ftemp);
      }else{
        printf("\nEnter New Password:\n");
        fflush(stdin);
        gets(chngPers.password);
        
        do{
          printf("\nRe-enter Password:\n");
          fflush(stdin);
          gets(newPass);

          if(strcmp(newPass, chngPers.password) != 0){
            printf("\n========================");
            printf("\nPassword did not match!!");
            printf("\n========================");
          }
        }while(strcmp(newPass, chngPers.password) != 0);
        fwrite(&chngPers, sizeof(struct form), 1, ftemp);
      }
    }
    fclose(fptr);
    fclose(ftemp);
    fptr = fopen("ordinaryUsers.txt", "w");
    ftemp = fopen("tempOrdinaryUser.txt", "r");

    while(fread(&chngPers, sizeof(struct form), 1, ftemp)){
      fwrite(&chngPers, sizeof(struct form), 1, fptr);
    }
    fclose(fptr);
    fclose(ftemp);
    printf("\n\nUpdate Success!");
    getch();
  }
}

void OUsersPage(){
  struct form *items;
  int num_items = 0;

  //load items from file
  FILE *fptr;

  if((fptr = fopen(ITEM_FILE, "r")) == NULL){
    printf("\nError Opening File!");
    getch();
    OUsersPage();
  }

  if(fptr){
    char name[ITEM_NAME_LEN];
    int quantity;

    while(fscanf(fptr, "%s %d", name, &quantity) == 2){
        num_items++;
        items = realloc(items, num_items * sizeof(struct form));

        strcpy(items[num_items - 1].firstName, name);
        items[num_items - 1].qty = quantity;
    }
    fclose(fptr);
  }

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
      case 1:
        system("cls");
        borrowEquip(items, num_items);
        system("cls");
        break;
      case 2:
        system("cls");
        returnEquip(items, num_items);
        system("cls");
        break;
      case 3:
        system("cls");
        changePersPassOU();
        system("cls");
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
  }while(choose != 4 );

  fptr = fopen(ITEM_FILE, "w");
  if(fptr){
    for (int i = 0; i < num_items; i++) {
    fprintf(fptr, "%s %d\n", items[i].firstName, items[i].qty);
    }
    fclose(fptr);
  }
  free(items);
}

//----------------------------------------------------------------------------------

int checkAvailRoll(int rollNo){
  struct form rollNumCheck;
  
  FILE *fptr;

  if((fptr = fopen("staffList.txt", "r")) == NULL){
    fprintf(stderr, "\nError opening file!\n\n");
    mngStaff();
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

void deleteStaff(){
  int available, rollNo, save;

  struct form staffDelete;

  FILE *fptr;
  FILE *ftemp;

  if((fptr = fopen("staffList.txt", "r")) == NULL){
    fprintf(stderr, "\nError opening file!\n\n");
    mngStaff();
  }

  printf("\nUpdate Staff Page\n");
  printf("==========================================================================================");
  printf("\nNo.   First Name      Last Name       Email                     Role            Password\n");
  printf("==========================================================================================\n");
 while (fread(&staffDelete, sizeof(struct form), 1, fptr))
    printf ("%-5d %-15s %-15s %-25s %-15s %-15s\n", staffDelete.rNum, staffDelete.firstName, staffDelete.lastName, staffDelete.username, staffDelete.roles, staffDelete.password);
  
  fclose(fptr);

  printf("\nEnter Roll Number to Delete: ");
  fflush(stdin);
  scanf("%d", &rollNo);

  available = checkAvailRoll(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    mngStaff();
  }else{
    fptr = fopen("staffList.txt", "r");
    ftemp = fopen("tempFile.txt", "w");

    while(fread(&staffDelete, sizeof(struct form), 1, fptr)){
      save = staffDelete.rNum;

      if(save != rollNo){
        fwrite(&staffDelete, sizeof(struct form), 1, ftemp);
      }
    }
    fclose(fptr);
    fclose(ftemp);

    remove("staffList.txt");
    rename("tempFile.txt", "staffList.txt");

    printf("\n\nDeleted Succesfully!");
    getch();
  }
}


void editStaff(){
  int available, rollNo, save;

  struct form update;

  FILE *fptr;
  FILE *ftemp;


  /*** open the accounts file ***/
  if((fptr = fopen("staffList.txt", "r")) == NULL){
    fprintf(stderr, "\nError opening file!\n\n");
    mngStaff();
  }
  
  printf("\nUpdate Staff Page\n");
  printf("==========================================================================================");
  printf("\nNo.   First Name      Last Name       Email                     Role            Password\n");
  printf("==========================================================================================\n");
  while (fread(&update, sizeof(struct form), 1, fptr))
    printf ("%-5d %-15s %-15s %-25s %-15s %-15s\n", update.rNum, update.firstName, update.lastName, update.username, update.roles, update.password);
  fclose(fptr);

  printf("\nEnter Roll Number to update: ");
  fflush(stdin);
  scanf("%d", &rollNo);
  
  available = checkAvailRoll(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    mngStaff();
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

  printf("\nNo.   First Name      Last Name       Email                     Role            Password\n");
  printf("==========================================================================================\n");
  while (fread(&input, sizeof(struct form), 1, fptr))
  printf ("%-5d %-15s %-15s %-25s %-15s %-15s\n", input.rNum, input.firstName, input.lastName, input.username, input.roles, input.password);

  fclose(fptr);
  printf("\n\nPress any key to continue...");
  getch();
}

void addStaff(){
  char role[] = "Staff";

  struct form staffLists;

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
  strcpy(staffLists.roles, role);
  printf("Password: \n");
  fflush(stdin);
  gets(staffLists.password);

  fwrite (&staffLists, sizeof(struct form), 1, fptr);
  fclose(fptr);

  printf("\n\nAdded Successfully!");
  getch();
}

void mngStaff(){

  do{
    printf("\nManage Staff Page\n");
    printf("===============================\n");
    printf("[111] List all Staff\n");
    printf("[112] Add New Staff\n");
    printf("[113] Edit Staff Details\n");
    printf("[114] Delete Staff\n");
    printf("[115] Back");
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
        deleteStaff();
        system("cls");
        break;
      case 115:
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
//----------------------------------------------------------------------------------
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

// void addOrdinary(){
//   char roles[] = {"OU"}, disOrdinary[] = {"Disable"};

//   struct form ordinary;

//   FILE *fptr;

//   if((fptr = fopen("ordinaryUsers.txt", "a")) == NULL){
//     printf("\n[Error Opening file!]");
//     mngOu();
//   }

//   printf("\nAdd Ordinary User");
//   printf("\n===========");
//   printf("\nRoll Number:\n");
//   fflush(stdin);
//   scanf("%d", &ordinary.rNum);
//   printf("First Name: \n");
//   fflush(stdin);
//   gets(ordinary.firstName);
//   printf("Last Name: \n");
//   fflush(stdin);
//   gets(ordinary.lastName);
//   printf("Email: \n");
//   fflush(stdin);
//   gets(ordinary.username);
//   printf("Password: \n");
//   fflush(stdin);
//   gets(ordinary.password);

//   strcpy(ordinary.status, disOrdinary);
//   strcpy(ordinary.roles, roles);
//   fwrite (&ordinary, sizeof(struct form), 1, fptr);
//   fclose(fptr);

//   printf("\n\nAdded Successfully!");
//   getch();
// }

void mngOu(){
   do{
    printf("\nManage Ordinary User Page\n");
    printf("===============================\n");
    printf("[121] List all Ordinary User\n");
    printf("[122] Edit Ordinary User Details\n");
    // printf("[123] Delete Ordinary User\n");
    // printf("[124] Add Ordinary User\n");
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
      // case 124:
      //   system("cls");
      //   addOrdinary();
      //   system("cls");
      //   break;
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
        system("cls");
        break;
      case 12:
        system("cls");
        mngOu();
        system("cls");
        break;
      case 13:
        system("cls");
        adminPage();
        system("cls");
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
//--------------------------------------------------------------------------
int checkEquip(int rollNo){
  struct form rollNumCheck;

  FILE *fptr;

  if((fptr = fopen("equipments.txt", "r")) == NULL){
    printf("\n[Error Opening file!]");
    mngEquip();
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

int checkEquipReturn(int rollNo){
  struct form rollNumCheck;

  FILE *fptr;

  if((fptr = fopen("tempEquipment.txt", "r")) == NULL){
    printf("\n[Error Opening file!]");
    mngEquip();
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



void deleteEquip(){
  int available, rollNo, save;

  struct form equipDelete;

  FILE *fptr;
  FILE *ftemp;

  if((fptr = fopen("equipments.txt", "r")) == NULL){
    printf("\n[Error Opening file!]");
    getch();
    mngEquip();
  }

  printf("\nUpdate Equipments Page");
  printf("\n=======================================================================");
  printf("\nNo.   Name                      Status       Quantity      Availability\n");
  printf("=======================================================================\n");
  while (fread(&equipDelete, sizeof(struct form), 1, fptr))
    printf ("%-5d %-25s %-15s %-10d %-15s\n", equipDelete.rNum, equipDelete.firstName, equipDelete.status, equipDelete.qty, equipDelete.availability);

  fclose(fptr);

  printf("\nEnter Roll Number to Delete: ");
  fflush(stdin);
  scanf("%d", &rollNo);

  available = checkEquip(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    mngEquip();
  }else{
    fptr = fopen("equipments.txt", "r");
    ftemp = fopen("tempEquipment.txt", "w");

    while(fread(&equipDelete, sizeof(struct form), 1, fptr)){
      save = equipDelete.rNum;

      if(save != rollNo){
        fwrite(&equipDelete, sizeof(struct form), 1, ftemp);
      }
    }
    fclose(fptr);
    fclose(ftemp);

    remove("equipments.txt");
    rename("tempEquipment.txt", "equipments.txt");

    printf("\n\nDeleted Successfully!");
    getch();
  }
}

void editEquip(){
  int available, rollNo, save;

  struct form equipUpdate;

  FILE *fptr;
  FILE *ftemp;

  if((fptr = fopen("equipments.txt", "r")) == NULL){
    printf("\n[Error Opening file!]");
    mngEquip();
  }

  printf("\nUpdate Equipments Page");
  printf("\n=======================================================================");
  printf("\nNo.   Name                      Status       Quantity      Availability\n");
  printf("=======================================================================\n");
  while (fread(&equipUpdate, sizeof(struct form), 1, fptr))
    printf ("%-5d %-25s %-15s %-10d %-15s\n", equipUpdate.rNum, equipUpdate.firstName, equipUpdate.status, equipUpdate.qty, equipUpdate.availability);

  fclose(fptr);

  printf("\nEnter Roll Number to update: ");
  fflush(stdin);
  scanf("%d", &rollNo);

  available = checkEquip(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    mngEquip();
  }else{
    fptr = fopen("equipments.txt", "r");
    ftemp = fopen("tempEquipment.txt", "w");

    while(fread(&equipUpdate, sizeof(struct form), 1, fptr)){
      save = equipUpdate.rNum;

      if(save != rollNo){
        fwrite(&equipUpdate, sizeof(struct form), 1, ftemp);
      }else{
        printf("\nWhich to Update");
        printf("\n=========================\n");
        printf("[1] Roll Number\n");
        printf("[2] Name\n");
        printf("[3] Status\n");
        printf("[4] Quantity\n");
        printf("[5] Availability\n");
        printf("[6] Back\n");
        printf("=========================\n");

        printf("Enter Operation: ");
        scanf("%d", &choose);

        switch(choose){
          case 1:
            printf("\nRoll Number: \n");
            fflush(stdin);
            scanf("%d", &equipUpdate.rNum);
            break;
          case 2:
            printf("\nName: \n");
            fflush(stdin);
            gets(equipUpdate.firstName);
            break;
          case 3:
            printf("\nStatus: \n");
            fflush(stdin);
            gets(equipUpdate.status);
            break;
          case 4:
            printf("\nQuantity: \n");
            fflush(stdin);
            scanf("%d", &equipUpdate.qty);
            break;
          case 5:
            printf("\nAvailability: \n");
            fflush(stdin);
            gets(equipUpdate.availability);
            break;
          case 6:
            system("cls");
            mngEquip();
            break;
        }
        fwrite(&equipUpdate, sizeof(struct form), 1, ftemp);
      }
    }
    fclose(fptr);
    fclose(ftemp);
    fptr = fopen("equipments.txt", "w");
    ftemp = fopen("tempEquipment.txt", "r");

    while(fread(&equipUpdate, sizeof(struct form), 1, ftemp)){
      fwrite(&equipUpdate, sizeof(struct form), 1, fptr);
    }
    fclose(fptr);
    fclose(ftemp);
    printf("\n\nUpdate Success!");
    getch();

  }
}

void allEquip(){
  FILE *fptr;

  struct form equip;

  if((fptr = fopen("equipments.txt", "r")) == NULL){
    printf("\n[Error Opening file!]");
    mngEquip();
  }

  printf("\nNo.   Name                      Status       Quantity      Availability\n");
  printf("=======================================================================\n");
  while (fread(&equip, sizeof(struct form), 1, fptr))
    printf ("%-5d %-25s %-15s %-10d %-15s\n", equip.rNum, equip.firstName, equip.status, equip.qty, equip.availability);

  fclose(fptr);
  printf("\n\nPress any key to continue...");
  getch();
}


void addEquip(){
  struct form equip;

  FILE *fptr;

  if((fptr = fopen("equipments.txt", "a")) == NULL){
    printf("\n[Error Opening file!]");
    mngEquip();
  }

  printf("\nAdd Equipments");
  printf("\n==================\n");
  printf("Roll Number:\n");
  fflush(stdin);
  scanf("%d", &equip.rNum);
  printf("Equipement Name:\n");
  fflush(stdin);
  gets(equip.firstName);
  printf("Equipment Status:\n");
  fflush(stdin);
  gets(equip.status);
  printf("Equipment Quantity:\n");
  fflush(stdin);
  scanf("%d", &equip.qty);
  printf("Equipment Availability:\n");
  fflush(stdin);
  gets(equip.availability);

  fwrite(&equip, sizeof(struct form), 1, fptr);
  fclose(fptr);

  printf("\n\nAdded Successfully!");
  getch();
}

void mngEquip(){
  do{
    printf("\nManage Equipment\n");
    printf("===============================\n");
    printf("[21] List of all Equipments\n");
    printf("[22] Add New Equipment\n");
    printf("[23] Edit Equipment\n");
    printf("[24] Delete Equipment\n");
    printf("[25] Borrow Requests\n");
    printf("[26] Back\n");
    printf("\n===============================\n");

    printf("Enter Operation: ");
    scanf("%d", &choose);

    switch(choose){
      case 21:
        system("cls");
        allEquip();
        system("cls");
        break;
      case 22:
        system("cls");
        addEquip();
        system("cls");
        break;
      case 23:
        system("cls");
        editEquip();
        system("cls");
        break;
      case 24:
        system("cls");
        deleteEquip();
        system("cls");
        break;
      case 26:
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

//----------------------------------------------------
int checkAdmin(int rollNo){
  struct form rollNoCheck;
  
  FILE *fptr;

  if((fptr = fopen("adminAcc.txt", "r")) == NULL){
    fprintf(stderr, "\nError opening file!\n\n");
    adminPage();
  }


  while(!feof(fptr)){
    fread(&rollNoCheck, sizeof(struct form), 1, fptr);

    if(rollNo == rollNoCheck.rNum){
      fclose(fptr);
      return 1;
    }
  }
  fclose(fptr);
  return 0;
}

void adminPass(){
  char newPass[20];
  int rollNo = 1, available, save;

  struct form chngAdminPers;

  FILE *fptr;
  FILE *ftemp;

  available = checkAdmin(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    adminPage();
  }else{
    fptr = fopen("adminAcc.txt", "r");
    ftemp = fopen("tempAdmin.txt", "w");

    while(fread(&chngAdminPers, sizeof(struct form), 1, fptr)){
      save = chngAdminPers.rNum;

      if(save != rollNo){
        fwrite(&chngAdminPers, sizeof(struct form), 1 ,ftemp);
      }else{
        printf("\nEnter New Password:\n");
        fflush(stdin);
        gets(chngAdminPers.password);

        do{
          printf("\nRe-enter Password:\n");
          fflush(stdin);
          gets(newPass);

          if(strcmp(newPass, chngAdminPers.password) != 0){
            printf("\n========================");
            printf("\nPassword did not match!!");
            printf("\n========================");
          }
        }while(strcmp(newPass, chngAdminPers.password) != 0);
        fwrite(&chngAdminPers, sizeof(struct form), 1, ftemp);
      }
    }
    fclose(fptr);
    fclose(ftemp);

    fptr = fopen("adminAcc.txt", "w");
    ftemp = fopen("tempAdmin.txt", "r");

    while(fread(&chngAdminPers, sizeof(struct form), 1, ftemp)){
      fwrite(&chngAdminPers, sizeof(struct form), 1, fptr);
    }
    fclose(fptr);
    fclose(ftemp);
    printf("\n\nUpdate Success!");
    getch();
  }
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
        system("cls");
        break;
      case 3:
        system("cls");
        adminPass();
        system("cls");
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
void relogin(){
  char choose;

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

void loginPage(){
  char status[] = "Disable";
  char username[30], password[20];
  int result = 0;

  //char adminUser[] = "admin", adminPass[] = "admin";
  struct form login;

  FILE *admin;
  FILE *staff;

  printf("\nLogin Page");
  printf("\n================");
  printf("\nEnter Username: \n");
  fflush(stdin);
  gets(username);
  printf("Enter Password: \n");
  fflush(stdin);
  gets(password);
 
  admin = fopen("adminAcc.txt", "r");
  staff = fopen("ordinaryUsers.txt", "r");

  fread(&login, sizeof(struct form), 1 ,admin);
  // printf("\n%s", login.username);
  if(strcmp(username, login.username) == 0 && strcmp(password, login.password) == 0){
    system("cls");
    adminPage();
  }else{
    while(fread(&login, sizeof(struct form), 1, staff)){
      if(strcmp(status, login.status) == 0){
        printf("\nPlease wait for Admin to verify the account!");
        getch();
        system("cls");
        main();
      }else if(strcmp(username, login.username) == 0 && strcmp(password, login.password) == 0){
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
 fclose(admin);
 fclose(staff);
}

//------------------------------------------------------------

void registerPage(){
  char roles[] = {"OU"}, disOrdinary[] = {"Disable"};

  struct form regUser;

  FILE *fptr;

  if((fptr = fopen("ordinaryUsers.txt", "a")) == NULL){
    printf("\nError Opening File!");
    getch();
    main();
  }

  printf("\nRegister Page");
  printf("\n=============\n");
  printf("Roll Number:\n");
  fflush(stdin);
  scanf("%d", &regUser.rNum);
  printf("First Name:\n");
  fflush(stdin);
  gets(regUser.firstName);
  printf("Last Name:\n");
  fflush(stdin);
  gets(regUser.lastName);
  printf("Email:\n");
  fflush(stdin);
  gets(regUser.username);
  printf("Password:\n");
  fflush(stdin);
  gets(regUser.password);

  strcpy(regUser.status, disOrdinary);
  strcpy(regUser.roles, roles);

  fwrite(&regUser, sizeof(struct form), 1, fptr);
  fclose(fptr);

  printf("\n\nRegistered!");
  getch();
  
}

void initAdmin(){
  struct form adminAcc;

  if(access("adminAcc.txt", F_OK) == -1){
    FILE *fptr = fopen("adminAcc.txt", "w");
    adminAcc.rNum = 1;
    strcpy(adminAcc.username, "admin@gmail.com");
    strcpy(adminAcc.password, "admin");
    strcpy(adminAcc.firstName, "admin");
    strcpy(adminAcc.lastName, "admin");
    strcpy(adminAcc.roles, "Admin");

    fwrite(&adminAcc, sizeof(struct form), 1, fptr);
    fclose(fptr);
  }
}


//Frist Screen--------------------------------------------------

int main(){
  char choose;

  initAdmin();

  do{

    printf("\nDo you already have an account?\n");
    printf("=========================\n");
    printf("[Y] Login\n");
    printf("[N] Register");
    printf("\n=========================\n");

    printf("Enter Operation: ");
    fflush(stdin);
    scanf("%c", &choose);

    if(choose == 'Y' || choose == 'y'){
      system("cls");
      loginPage();
      system("cls");
    }else if( choose == 'N' || choose == 'n'){
      system("cls");
      registerPage();
      system("cls");
    }else{
      system("cls");
      printf("\nInvalid Operation!\n\nPress Enter to go back...");
      getch();
      system("cls");
      main();
    }
  }while(choose);
  return 0;
}