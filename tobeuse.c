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