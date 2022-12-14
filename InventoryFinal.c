#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void registerPage();
void loginPage();
void adminPage();
void adminPass();
void mngEquip();
void addEquip();
void allEquip();
void editEquip();
void deleteEquip();
int checkEquipReturn(int rNo);
int checkEquip(int rNo);
void mngAcc();
void mngOu();
void allOrdinary();
void editOrdinary();
void deleteOrdinary();
int checkOrdinary(int rNo);
void mngStaff();
void addStaff();
void allStaff();
void editStaff();
void deleteStaff();
int checkStaff(int rNo);
void OUsersPage();
void changePersPassOU();
void returnEquip();
void borrowEquip();

int choose = 0;

struct form{
    int rollNo, qty;
    char availability[20];
    char firstName[30];
    char lastName[30];
    char username[30];
    char password[20];
    char status[10];
    char roles[10];
};

int main(){
    char choose;

    do{
        printf("\nDo you already have an account?\n");
        printf("===============================\n");
        printf("[Y] Login\n");
        printf("[N] Register\n");
        printf("===============================\n");

        printf("\nEnter Operation: ");
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
                system("cls");
                break;
            default:
                system("cls");
                printf("\n\nInvalid Operation!");
                getch();
                system("cls");
                main();
                break;
        }
    }while(choose);
    return 0;
}

void registerPage(){
    char roles[] = "OU", stats[] = "Disable";

    struct form ordinary;

    FILE *fptr = fopen("ordinaryUsers.txt", "a");
    if(fptr == NULL){
        printf("\nError Opening File!");
        getch();
        main();
    }

    printf("\nRegister Page");
    printf("\n==============\n");
    printf("Roll Number: \n");
    fflush(stdin);
    scanf("%d", &ordinary.rollNo);
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

    strcpy(ordinary.roles, roles);
    strcpy(ordinary.status, stats);

    fwrite(&ordinary, sizeof(struct form), 1, fptr);
    fclose(fptr);

    printf("\n\nRegistered!");
    getch();
}

void loginPage(){
    char admins[] = "Christian", adminPass[] = "Admin", stats[] = "Disable";
    char choose, username[20], password[20];

    struct form login;

    FILE *regul;
    FILE *admin;

    printf("\nLogin Page");
    printf("\n==========\n");
    printf("Username: \n");
    fflush(stdin);
    gets(username);
    printf("Password: \n");
    fflush(stdin);
    gets(password);

    regul = fopen("ordinaryUsers.txt", "r");

    if(strcmp(username, admins) == 0 && strcmp(password, adminPass) == 0){
        system("cls");
        adminPage();
    }else{
        while(fread(&login, sizeof(struct form), 1, regul)){
            if(strcmp(login.status, stats) == 0){
                printf("\nWait for Admin to verify the account!");
                getch();
                system("cls");
                main();
            }else if(strcmp(username, login.username) == 0 && strcmp(password, login.password) == 0){
                system("cls");
                fclose(regul);
                OUsersPage();
            }else{
                system("cls");
                printf("\nIncorrect Password or Username!");
                printf("\n\nWant to try again?\n");
                printf("======================\n");
                printf("[Y] Re-Login\n");
                printf("[N] Main Menu\n");
                printf("======================\n");

                printf("\nEnter Operation: ");
                fflush(stdin);
                scanf("%c", &choose);

                switch(choose){
                    case 'Y':
                    case 'y':
                        system("cls");
                        loginPage();       
                        break;
                    case 'N':
                    case 'n':
                        system("cls");
                        main();
                        break;
                }

            }
        }
    }   
}


void adminPage(){
    do{
        printf("\nAdmin Main Page\n");
        printf("===============================\n");
        printf("[1] Manage Accounts\n");
        printf("[2] Manage Equipments\n");
        printf("[3] Change Personal Password\n");
        printf("[4] Exit");
        printf("\n===============================\n\n"); 

        printf("Enter Operation: ");
        fflush(stdin);
        scanf("%d", &choose);

        switch(choose){
            case 1:
                system("cls");
                mngAcc();
                system("cls");
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
                system("cls");
                break;
            default:
                system("cls");
                printf("\nInvalid Operation!");
                getch();
                system("cls");
                adminPage();
                break;
        }
    }while(choose);
}

void adminPass(){
    char newPass[20];

    struct form adminPassword;

    FILE *fptr;
    FILE *ftemp;

    // fptr = fopen("adminAcc.txt", "r");
    ftemp = fopen("tempAdmin.txt", "w");

    printf("\nChange Personal Password\n");
    printf("==========================");
    printf("\nNew Password: \n");
    fflush(stdin);
    gets(newPass);
    do{
        printf("\nRe-enter Password:\n");
        fflush(stdin);
        gets(newPass);

        if(strcmp(newPass, adminPassword.password) != 0){
        printf("\n========================");
        printf("\nPassword did not match!!");
        printf("\n========================");
        }
    }while(strcmp(newPass, adminPassword.password) != 0);
        fwrite(&adminPassword, sizeof(struct form), 1, ftemp);

    
    fclose(ftemp);
    fptr = fopen("adminAcc.txt", "w");
    ftemp = fopen("tempAdmin.txt", "r");

    while(fread(&adminPassword, sizeof(struct form), 1, ftemp)){
        fwrite(&adminPassword, sizeof(struct form), 1, fptr);
    }
    fclose(fptr);
    fclose(ftemp);
    printf("\n\nUpdate Success!");
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
        printf("[25] Back\n");
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
            case 25:
                system("cls");
                adminPage();
                system("cls");
                break;
            default:
                system("cls");
                printf("\nInvalid Operation!");
                getch();
                system("cls");
                mngEquip();
                break;
        }
    }while(choose);
}

void addEquip(){
    struct form equip;

    FILE *fptr = fopen("equipments.txt", "a");

    if(fptr == NULL){
        printf("\nError Opening file!");
        getch();
        mngEquip();
    }

    printf("\nAdd Equipments");
    printf("\n=================\n");
    printf("Roll Number:\n");
    fflush(stdin);
    scanf("%d", &equip.rollNo);
    printf("Equipment Name: \n");
    fflush(stdin);
    gets(equip.firstName);
    printf("Equipment Status: \n");
    fflush(stdin);
    gets(equip.status);
    printf("Equipment Quantity: \n");
    fflush(stdin);
    scanf("%d", &equip.qty);
    printf("Equipment Availability: \n");
    fflush(stdin);
    gets(equip.availability);

    fwrite(&equip, sizeof(struct form), 1, fptr);
    fclose(fptr);

    printf("\n\nAdded Succesfully!");
    getch();
}

void allEquip(){
    struct form display;

    FILE *fptr = fopen("equipments.txt", "r");
    if(fptr == NULL){
        printf("\nError Opening file!");
        getch();
        mngEquip();
    }

    printf("\nNo.   Name                      Status       Quantity      Availability\n");
    printf("=======================================================================\n");
    while (fread(&display, sizeof(struct form), 1, fptr))
        printf ("%-5d %-25s %-15s %-10d %-15s\n", display.rollNo, display.firstName, display.status, display.qty, display.availability);

    fclose(fptr);
    printf("\n\nPress any key to continue...");
    getch();
}

void editEquip(){
    int available, rNo, save;

    struct form update;

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
    while (fread(&update, sizeof(struct form), 1, fptr))
        printf ("%-5d %-25s %-15s %-10d %-15s\n", update.rollNo, update.firstName, update.status, update.qty, update.availability);

    fclose(fptr);
    printf("\nEnter Roll Number to update: ");
    fflush(stdin);
    scanf("%d", &rNo);

    available = checkEquip(rNo);

    if(available == 0){
        printf("\nRoll number does not exist!");
        getch();
        system("cls");
        mngEquip();
    }else{
        fptr = fopen("equipments.txt", "r");
        ftemp = fopen("tempEquipment.txt", "w");

        while(fread(&update, sizeof(struct form), 1, fptr)){
            save = update.rollNo;

            if(save != rNo){
                fwrite(&update, sizeof(struct form), 1, ftemp);
            }else{
                printf("Which to Update?");
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
                        scanf("%d", &update.rollNo);
                        break;
                    case 2:
                        printf("\nName: \n");
                        fflush(stdin);
                        gets(update.firstName);
                    case 3:
                        printf("\nStatus:\n");
                        fflush(stdin);
                        gets(update.status);
                        break;
                    case 4:
                        printf("\nQuantity:\n");
                        fflush(stdin);
                        scanf("%d", &update.qty);
                        break;
                    case 5:
                        printf("\nAvailability:\n");
                        fflush(stdin);
                        gets(update.availability);
                        break;
                    case 6:
                        system("cls");
                        mngEquip();
                        break;
                }
                fwrite(&update, sizeof(struct form), 1, fptr);
            }
        }
        fclose(fptr);
        fclose(ftemp);

        fptr = fopen("equipments.txt", "w");
        ftemp = fopen("tempEquipment.txt", "r");

        while(fread(&update, sizeof(struct form), 1, ftemp)){
            fwrite(&update, sizeof(struct form), 1, fptr);
        }
        fclose(fptr);
        fclose(ftemp);

        printf("\n\nUpdate Success!");
        getch();
    }
}

void deleteEquip(){
    int available, rNo, save;

    struct form delete;

    FILE *fptr;
    FILE *ftemp;

    if((fptr = fopen("equipments.txt", "r")) == NULL){
        printf("\n[Error Opening file!]");
        mngEquip();
    }

    printf("\nDelete Equipments Page");
    printf("\n=======================================================================");
    printf("\nNo.   Name                      Status       Quantity      Availability\n");
    printf("=======================================================================\n");
    while (fread(&delete, sizeof(struct form), 1, fptr))
        printf ("%-5d %-25s %-15s %-10d %-15s\n", delete.rollNo, delete.firstName, delete.status, delete.qty, delete.availability);

    fclose(fptr);
    printf("\nEnter Roll Number to Delete: ");
    fflush(stdin);
    scanf("%d", &rNo);

    available = checkEquip(rNo);

    if(available == 0){
        printf("\nRoll number does not exist!");
        getch();
        system("cls");
        mngEquip();
    }else{
        fptr = fopen("equipments.txt", "r");
        ftemp = fopen("tempEquipment.txt", "w");

        while(fread(&delete, sizeof(struct form), 1, fptr)){
            save = delete.rollNo;
            
            if(save != rNo){
                fwrite(&delete, sizeof(struct form), 1, ftemp);
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

int checkEquipReturn(int rNo){
    struct form rollNumCheck;

    FILE *fptr;

    if((fptr = fopen("tempEquipment.txt", "r")) == NULL){
        printf("\nError Opening file!");
        mngEquip();
    }

    while(!feof(fptr)){
        fread(&rollNumCheck, sizeof(struct form), 1, fptr);

        if(rNo == rollNumCheck.rollNo){
        fclose(fptr);
        return 1;
        }
    }
    fclose(fptr);
    return 0;
}

int checkEquip(int rNo){
    struct form rollNumCheck;

    FILE *fptr;

    if((fptr = fopen("equipments.txt", "r")) == NULL){
        printf("\nError Opening file!");
        mngEquip();
    }

    while(!feof(fptr)){
        fread(&rollNumCheck, sizeof(struct form), 1, fptr);

        if(rNo == rollNumCheck.rollNo){
        fclose(fptr);
        return 1;
        }
    }
    fclose(fptr);
  return 0;
}

void mngAcc(){
    do{
        printf("\nAccount Management\n");
        printf("===============================\n");
        printf("[11] Manage Staff\n");
        printf("[12] Manage Ordinary User\n");
        printf("[13] Back");
        printf("\n===============================\n");

        printf("Enter Operation: ");
        fflush(stdin);
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
                printf("\nInvalid Operation!");
                getch();
                system("cls");
                mngAcc();
                break;
        }
    }while(choose);
}

void mngOu(){
    do{
        printf("\nManage Ordinary User Page\n");
        printf("===============================\n");
        printf("[121] List all Ordinary User\n");
        printf("[122] Edit Ordinary User Details\n");
        printf("[123] Delete Ordinary User\n");
        printf("[124] Back");
        printf("\n===============================\n\n");

        printf("Enter operation: ");
        fflush(stdin);
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

void allOrdinary(){
    struct form display;

    FILE *fptr = fopen("ordinaryUsers.txt", "r");
    if(fptr == NULL){
        printf("\nError Opening file!");
        getch();
        mngOu();
    }

    printf("\nNo.   First Name      Last Name       Email                  Roles           Password        Status\n");
    printf("=====================================================================================================\n");
    while (fread(&display, sizeof(struct form), 1, fptr))
        printf ("%-5d %-15s %-15s %-22s %-15s %-15s %-15s\n", display.rollNo, display.firstName, display.lastName, display.username, display.roles, display.password, display.status);
    
    fclose(fptr);
    printf("\n\nPress any key to continue...");
    getch();
}

void editOrdinary(){
    int available, rNo, save;

    struct form update;

    FILE *fptr;
    FILE *ftemp;

    if((fptr = fopen("ordinaryUsers.txt", "r")) == NULL){
        fprintf(stderr, "\nError opening file!");
        getch();
        mngOu();
    }

    printf("\nUpdate Ordinary User Page\n");
    printf("=====================================================================================================");
    printf("\nNo.   First Name      Last Name       Email                  Roles           Password        Status\n");
    printf("=====================================================================================================\n");
    while (fread(&update, sizeof(struct form), 1, fptr))
        printf ("%-5d %-15s %-15s %-22s %-15s %-15s %-15s\n", update.rollNo, update.firstName, update.lastName, update.username, update.roles, update.password, update.status);
    
    fclose(fptr);
    printf("\nEnter Roll Number to update: ");
    fflush(stdin);
    scanf("%d", &rNo);

    available = checkOrdinary(rNo);

    if(available == 0){
        printf("\nRoll number does not exist!");
        getch();
        system("cls");
        mngOu();
    }else{
        fptr = fopen("ordinaryUsers.txt", "r");
        ftemp = fopen("tempOrdinaryUser.txt", "w");

        while(fread(&update, sizeof(struct form), 1, fptr)){
            save = update.rollNo;

            if(save != rNo){
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
                fflush(stdin);
                scanf("%d", &choose);

                switch(choose){
                    case 1:
                        printf("\nRoll Number: \n");
                        fflush(stdin);
                        scanf("%d", &update.rollNo);
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

void deleteOrdinary(){
    int available, rNo, save;

    struct form delete;

    FILE *fptr;
    FILE *ftemp;

    fptr = fopen("ordinaryUsers.txt", "r");
    if(fptr == NULL){
        printf("\nError Opening file!");
        getch();
        mngOu();
    }

    printf("\nDelete Ordinary User Page\n");
    printf("=====================================================================================================");
    printf("\nNo.   First Name      Last Name       Email                  Roles           Password        Status\n");
    printf("=====================================================================================================\n");
    while (fread(&delete, sizeof(struct form), 1, fptr))
        printf ("%-5d %-15s %-15s %-22s %-15s %-15s %-15s\n", delete.rollNo, delete.firstName, delete.lastName, delete.username, delete.roles, delete.password, delete.status);
    
    fclose(fptr);
    printf("\nEnter Roll Number to Delete: ");
    fflush(stdin);
    scanf("%d", &rNo);

    available = checkOrdinary(rNo);

    if(available == 0){
        printf("\nRoll number does not exist!");
        getch();
        system("cls");
        mngOu();
    }else{
        fptr = fopen("ordinaryUsers.txt", "r");
        ftemp = fopen("tempOrdinaryUser.txt", "w");

        while(fread(&delete, sizeof(struct form), 1 ,fptr)){
            save = delete.rollNo;

            if(save != rNo){
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

int checkOrdinary(int rNo){
    struct form rollNumCheck;
  
    FILE *fptr;

    if((fptr = fopen("ordinaryUsers.txt", "r")) == NULL){
        printf("\nError Opening file!");
        mngOu();
    }

    while(!feof(fptr)){
        fread(&rollNumCheck, sizeof(struct form), 1, fptr);

        if(rNo == rollNumCheck.rollNo){
        fclose(fptr);
        return 1;
        }
    }
    fclose(fptr);
    return 0;
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
        fflush(stdin);
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
                printf("\nInvalid Operation!");
                getch();
                system("cls");
                mngStaff();
                break;
            }
    }while(choose);
}

void addStaff(){
    char role[] = "Staff";

    struct form allStaff;

    FILE *fptr = fopen("staffList.txt", "a");
    if(fptr == NULL){
        printf("\nError Opening file!");
        getch();
        mngStaff();
    }

    printf("\nAdd Staff");
    printf("\n===========");
    printf("\nRoll Number:\n");
    fflush(stdin);
    scanf("%d", &allStaff.rollNo);
    printf("First Name: \n");
    fflush(stdin);
    gets(allStaff.firstName);
    printf("Last Name: \n");
    fflush(stdin);
    gets(allStaff.lastName);
    printf("Email: \n");
    fflush(stdin);
    gets(allStaff.username);
    strcpy(allStaff.roles, role);
    printf("Password: \n");
    fflush(stdin);
    gets(allStaff.password);

    fwrite(&allStaff, sizeof(struct form), 1, fptr);
    fclose(fptr);

    printf("\n\nAdded Successfully!");
    getch();
}

void allStaff(){
    struct form display;

    FILE *fptr = fopen("staffList.txt", "r");
    if(fptr == NULL){
        printf("\nError Opening file!");
        getch();
        mngStaff();
    }

    printf("\nNo.   First Name      Last Name       Email                     Role            Password\n");
    printf("==========================================================================================\n");
    while (fread(&display, sizeof(struct form), 1, fptr))
        printf ("%-5d %-15s %-15s %-25s %-15s %-15s\n", display.rollNo, display.firstName, display.lastName, display.username, display.roles, display.password);

    fclose(fptr);
    printf("\n\nPress any key to continue...");
    getch();
}

void editStaff(){
    int available, rNo, save;

    struct form update;

    FILE *fptr;
    FILE *ftemp;

    if((fptr = fopen("staffList.txt", "r")) == NULL){
    printf("\nError Opening file!");
    getch();
    mngStaff();
  }
    printf("\nUpdate Staff Page\n");
    printf("==========================================================================================");
    printf("\nNo.   First Name      Last Name       Email                     Role            Password\n");
    printf("==========================================================================================\n");
    while (fread(&update, sizeof(struct form), 1, fptr))
        printf ("%-5d %-15s %-15s %-25s %-15s %-15s\n", update.rollNo, update.firstName, update.lastName, update.username, update.roles, update.password);

    fclose(fptr);
    printf("\nEnter Roll Number to update: ");
    fflush(stdin);
    scanf("%d", &rNo);

    available = checkStaff(rNo);

    if(available == 0){
        printf("\nRoll number does not exist!");
        getch();
        system("cls");
        mngStaff();
    }else{
        fptr = fopen("staffList.txt", "r");
        ftemp = fopen("tempFile.txt", "w");

        while(fread(&update, sizeof(struct form), 1, fptr)){
            save = update.rollNo;

            if(save != rNo){
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
                fflush(stdin);
                scanf("%d", &choose);

                switch(choose){
                    case 1:
                        printf("\nRoll Number: \n");
                        fflush(stdin);
                        scanf("%d", &update.rollNo);
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

void deleteStaff(){
    int available, rNo, save;

    struct form delete;

    FILE *fptr;
    FILE *ftemp;

    if((fptr = fopen("staffList.txt", "r")) == NULL){
    printf("\nError Opening File!");
    getch();
    mngStaff();
  }

    printf("\nUpdate Staff Page\n");
    printf("==========================================================================================");
    printf("\nNo.   First Name      Last Name       Email                     Role            Password\n");
    printf("==========================================================================================\n");
    while (fread(&delete, sizeof(struct form), 1, fptr))
        printf ("%-5d %-15s %-15s %-25s %-15s %-15s\n", delete.rollNo, delete.firstName, delete.lastName, delete.username, delete.roles, delete.password);
    
    fclose(fptr);
    printf("\nEnter Roll Number to Delete: ");
    fflush(stdin);
    scanf("%d", &rNo);

    available = checkStaff(rNo);

    if(available == 0){
        printf("\nRoll number does not exist!");
        getch();
        system("cls");
        mngStaff();
    }else{
        fptr = fopen("staffList.txt", "r");
        ftemp = fopen("tempFile.txt", "w");

        while(fread(&delete, sizeof(struct form), 1, fptr)){
            save = delete.rollNo;

            if(save != rNo){
                fwrite(&delete, sizeof(struct form), 1, ftemp);
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

int checkStaff(int rNo){
    struct form rollNumCheck;
    
    FILE *fptr;

    if((fptr = fopen("staffList.txt", "r")) == NULL){
        fprintf(stderr, "\nError opening file!\n\n");
        mngStaff();
    }

    while(!feof(fptr)){
        fread(&rollNumCheck, sizeof(struct form), 1, fptr);

        if(rNo == rollNumCheck.rollNo){
        fclose(fptr);
        return 1;
        }
    }
  
    fclose(fptr);
    return 0;
}


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
        fflush(stdin);
        scanf("%d", &choose);

        switch(choose) {
            case 1:
                system("cls");
                borrowEquip();
                system("cls");
                break;
            case 2:
                system("cls");
                returnEquip();
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
                printf("\nInvalid Operation!");
                getch();
                system("cls");
                OUsersPage();
                break;

            }
    }while(choose);
}

void changePersPassOU(){
    char newPass[20];
    int rNo, available, save, value = 0;

    struct form change;

    FILE *fptr;
    FILE *ftemp;

    printf("\nChange Personal Password");
    printf("\n========================");
    printf("\nEnter your Roll Number: ");
    scanf("%d", &rNo);

    available = checkOrdinary(rNo);

    if(available == 0){
        printf("\nRoll number does not exist!");
        getch();
        system("cls");
        OUsersPage();
    }else{
        fptr = fopen("ordinaryUsers.txt", "r");
        ftemp = fopen("tempOrdinaryUser.txt", "w");

        while(fread(&change, sizeof(struct form), 1, fptr)){
            save = change.rollNo;

            if(save != rNo){
                fwrite(&change, sizeof(struct form), 1, ftemp);
            }else{
                printf("\nEnter New Password:\n");
                fflush(stdin);
                gets(change.password);

                do{
                    printf("\nRe-enter Password:\n");
                    fflush(stdin);
                    gets(newPass);

                    if(strcmp(newPass, change.password) != 0){
                        printf("\n========================");
                        printf("\nPassword did not match!!");
                        printf("\n========================");
                    }
                }while(strcmp(newPass, change.password) != 0);
                fwrite(&change, sizeof(struct form), 1, ftemp);
            }
        }
        fclose(fptr);
        fclose(ftemp);
        fptr = fopen("ordinaryUsers.txt", "w");
        ftemp = fopen("tempOrdinaryUser.txt", "r");

        while(fread(&change, sizeof(struct form), 1, ftemp)){
            fwrite(&change, sizeof(struct form), 1, fptr);
        }
        fclose(fptr);
        fclose(ftemp);

        printf("\n\nUpdate Success!");
        getch();
    }
}

void returnEquip(){
    int available, rNo, saveRoll;
    char save[100], avlblty[] = "available";

    struct form retEq;

    FILE *fptr;
    FILE *ftemp;

    fptr = fopen("equipments.txt", "r");
    ftemp = fopen("tempEquipment.txt", "w");

    while(fread(&retEq, sizeof(struct form), 1, fptr)){
        strcpy(save, retEq.availability);

        if(strcmp(save, "borrowed") == 0){
        fwrite(&retEq, sizeof(struct form), 1, ftemp);
        }
    }
    fclose(fptr);
    fclose(ftemp);

    if((ftemp = fopen("tempEquipment.txt", "r")) == NULL){
        printf("\n[Error Opening file!]");
        OUsersPage();
    }

    printf("\nReturn Equipments Page");
    printf("\n=======================================================================");
    printf("\nNo.   Name                      Status       Quantity      Availability\n");
    printf("=======================================================================\n");
    while (fread(&retEq, sizeof(struct form), 1, fptr))
        printf ("%-5d %-25s %-15s %-10d %-15s\n", retEq.rollNo, retEq.firstName, retEq.status, retEq.qty, retEq.availability);

    fclose(ftemp);
    printf("\nEnter Roll Number to return: ");
    fflush(stdin);
    scanf("%d", &rNo);

    available = checkEquipReturn(rNo);

    if(available == 0){
        printf("\nRoll number does not exist!");
        getch();
        system("cls");
        OUsersPage();
    }else{
        fptr = fopen("equipments.txt", "r");
        ftemp = fopen("tempReturnEquip.txt", "w");

        while(fread(&retEq, sizeof(struct form), 1, fptr)){
            saveRoll = retEq.rollNo;

            if(saveRoll != rNo){
                fwrite(&retEq, sizeof(struct form), 1, ftemp);
            }else{
                strcpy(retEq.availability, avlblty);

                fwrite(&retEq, sizeof(struct form), 1, ftemp);
            }
        }
        fclose(fptr);
        fclose(ftemp);

        fptr = fopen("equipments.txt", "w");
        ftemp = fopen("tempReturnEquip.txt", "r");

        while(fread(&retEq, sizeof(struct form), 1, ftemp)){
            fwrite(&retEq, sizeof(struct form), 1, fptr);
        }
        fclose(fptr);
        fclose(ftemp);

        printf("\n\nEquipment Returned Successfully!");
        getch();
    }
}   

void borrowEquip(){
    int available, rNo, save;

    char avlblty[] = "borrowed";

    struct form equipborrow;

    FILE *fptr;
    FILE *ftemp;

    if((fptr = fopen("equipments.txt", "r")) == NULL){
        printf("\nError Opening file!");
        mngEquip();
    }

    printf("\nList of Equipments Page");
    printf("\n=======================================================================");
    printf("\nNo.   Name                      Status       Quantity      Availability\n");
    printf("=======================================================================\n");
    while (fread(&equipborrow, sizeof(struct form), 1, fptr))
        printf ("%-5d %-25s %-15s %-10d %-15s\n", equipborrow.rollNo, equipborrow.firstName, equipborrow.status, equipborrow.qty, equipborrow.availability);

    fclose(fptr);
    printf("\nEnter Roll Number to update: ");
    fflush(stdin);
    scanf("%d", &rNo);

    available = checkEquip(rNo);

    if(available == 0){
        printf("\nRoll number does not exist!");
        getch();
        system("cls");
        OUsersPage();
    }else if(strcmp(avlblty, equipborrow.availability) == 0){
        printf("\nEquipment currently borrowed!");
        getch();
        system("cls");
        OUsersPage();
    }else{
        fptr = fopen("equipments.txt", "r");
        ftemp = fopen("tempEquipment.txt", "w");

        while(fread(&equipborrow, sizeof(struct form), 1, fptr)){
            save = equipborrow.rollNo;

            if(save != rNo){
                fwrite(&equipborrow, sizeof(struct form), 1, ftemp);
            }else{
                strcpy(equipborrow.availability, avlblty);
                
                fwrite(&equipborrow, sizeof(struct form), 1, ftemp);
            }
        }
        fclose(fptr);
        fclose(ftemp);
        fptr = fopen("equipments.txt", "w");
        ftemp = fopen("tempEquipment.txt", "r");

        while(fread(&equipborrow, sizeof(struct form), 1, ftemp)){
            fwrite(&equipborrow, sizeof(struct form), 1, fptr);
        }
        fclose(fptr);
        fclose(ftemp);
        printf("\n\nBorrow Success!");
        getch();
    }
}