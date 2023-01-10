void allStaff(){
  FILE *fptr;

  fptr = fopen("staffList.txt", "r");
  if(fptr == NULL){
    printf("\nError Opening File!");
    mngStaff();
  }

  char line[100];

  while(fgets(line, sizeof(line), fptr)){
    char *token;

    token = strtok(line, ",");

    while(token != NULL){
      printf("%-12s", token);
      token = strtok(NULL, ",");
    }
    printf("\n");
  }
  fclose(fptr);
  getch();
}



void addStaff(){
  char csv[100];
  char repass[20];
  int value, count, i;

  struct form staffLists;

  FILE *fptr;

  if((fptr = fopen("staffList.txt", "a")) == NULL){
    printf("\n[Error Opening file!]");
    addStaff();
  }

  printf("\nAdd Staff");
  printf("\n------------------");
  printf("\nFirst Name: \n");
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
  

    do{
        printf("Re-enter password: \n");
        fflush(stdin);
        gets(repass);
   
        value = strcmp(repass , staffLists.password);//when comparing strings
    
        count++;
        if(value == 0 || count == 3){
            printf("\n\nToo many attempts! try again later...");
            break;
        }else{
            printf("[Password Incorrect!]\n");
        }
    }while(value != 0);

  
  strcpy(csv,"");
  strcat(csv, staffLists.firstName);
  strcat(csv, ",");
  strcat(csv, staffLists.lastName);
  strcat(csv, ",");
  strcat(csv, staffLists.username);
  strcat(csv, ",");
  strcat(csv, staffLists.password);
  strcat(csv, "\n");

  puts(csv);
  fputs(csv, fptr);
  fclose(fptr);
  
}

//LOGIN OPERATION----------------------------------
// if(choose == 'Y' || choose == 'y'){
    //   system("cls");
    //   loginPage();
    //   getch();
    
    // }
    // if(choose == 'N' || choose == 'n'){
    //   system("cls");
    //   registerPage();
    //   getch();

    // }else{
    //     system("cls");
    //     printf("\nInvalid Operation!\n\nPress Enter to go back...");
    //     getch();
    //     system("cls");
    //     main();
    //     break;
    // }
//--------------------------------------------------


while(fread(&update, sizeof(struct form), 1, fptr)){
      save = update.rNum;

      if(save != rollNo){
        fwrite(&update, sizeof(struct form), 1, ftemp);
      }else{
        printf("\nEnter First Name: \n");
        fflush(stdin);
        gets(update.firstName);
        printf("Enter Last Name: \n");
        fflush(stdin);
        gets(update.firstName);
        printf("Enter Email: \n");
        fflush(stdin);
        gets(update.firstName);
        printf("Enter Password: \n");
        fflush(stdin);
        gets(update.firstName);

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

    printf("\nUpdate Succeful!");
    getch();
  }

  //returnEquipment---------------
  int available, rollNo, saveRoll, countVal;
  char save[100];

  struct form retEq;

  FILE *fptr;
  FILE *ftemp;

  countVal = borrowEquip();

  fptr = fopen("equipments.txt", "r");
  ftemp = fopen("tempEquipment.txt", "w");

  while(fread(&retEq, sizeof(struct form), 1, fptr)){
    retEq.qty = countVal;
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
    printf ("%-5d %-25s %-15s %-10d %-15s\n", retEq.rNum, retEq.firstName, retEq.status, retEq.qty, retEq.availability);

  fclose(ftemp);

  printf("\nEnter Roll Number to return: ");
  fflush(stdin);
  scanf("%d", &rollNo);

  available = checkEquipReturn(rollNo);

  if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    OUsersPage();
  }else{
    fptr = fopen("tempEquipment.txt", "r");
    ftemp = fopen("tempReturnEquip.txt", "w");

    while(fread(&retEq, sizeof(struct form), 1, fptr)){
      saveRoll = retEq.rNum;

      if(saveRoll != rollNo){
        fwrite(&retEq, sizeof(struct form), 1, ftemp);
      }else{
        countVal--;
        if(countVal == 0){
          strcpy(retEq.availability, "available");
          retEq.qty = countVal;
        }
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
    system("cls");
  }

  //-----------------------------------------------------------------

  //borrow function qty counter---------------------
   if(available == 0){
    printf("\nRoll No. [%d] unavailable!", rollNo);
    getch();
    system("cls");
    OUsersPage();
  }else if(strcmp(avlblty, equipborrow.availability) == 0){
    printf("\nEquipment currently borrowed!");
    getch();
    system("cls");
    OUsersPage();
  }else if(equipborrow.qty == 0){
    printf("\nEquipment currently borrowed!");
    getch();
    system("cls");
    OUsersPage();
  }else if(strcmp(equipborrow.status, prodStat) == 0){
    printf("\nEquipment currently broken!");
    getch();
    system("cls");
    OUsersPage();
  }else{
    fptr = fopen("equipments.txt", "r");
    ftemp = fopen("tempEquipment.txt", "w");
    //------------------------------------------

//LOGIN Page-------------------------------------------------

    while(fread(&OU, sizeof(struct form), 1, log) > 0){
    if(strcmp(OU.status, "Disable") == 0){
      printf("\nPlease wait for Admin to verify the account!");
      getch();
      system("cls");
      main();
    }else if(strcmp(username, OU.username) == 0 && strcmp(password, OU.password) == 0){
      system("cls");
      OUsersPage();
    }else{
      relogin();
    }
  }
  fclose(log);

  while(fread(&ADMN, sizeof(struct form), 1, admin) > 0){
    if(strcmp(username, ADMN.username) == 0 && strcmp(password, ADMN.password) == 0){
      system("cls");
      adminPage();
    }else{
      relogin();
    }
  }
  fclose(admin);

  //-----------------------------------------------------------

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