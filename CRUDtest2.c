#include<stdio.h>
#include<conio.h>
char selection()  ////This were I use the function wherein I display a top screen label for the user///////
{
 printf("BOOK'S\n 1) ENGLISH  2) MATH  3) FIL1  4) EPP  5) PE  6) SOCIAL  7) BOB'ong\n--------------------------------------------\n");
 return 0;
}
main() ////This is the main program where the processing of book in the library happens//////
{
char sno[10],name[25],dateb[20],actual_name[100];
int nbook,x,bcode[100],bday[100],y;
int limit=7; 
 system("cls");
  selection();
  printf("STUDENT NUMBER : ");
  scanf("%s",&sno);
  printf("\nSTUDENT NAME : ");
  scanf("%s",&name);
  printf("\nDATE BARROWED : ");
  scanf("%s",&dateb);
 system("cls");
  selection();
a:
  printf("HOW MANY BOOOK'S : ");
  scanf("%d",&nbook);
  if(nbook>limit){  //////// if the user input was higher than the number of book in the library the user will re-input the number of books that he/she want to borrow.
   printf("INVALID INPUT! the maximum is %d\n",limit);
   goto a;
  }
 system("cls");
  selection();
  for(x=1; x<=nbook; x++)
  {
   printf("%d) ENTER BOOK CODE : ",x);
   scanf("%d",&bcode[x]);

   printf("\t\t\tNUMBER OF DAY(S) : ");
   scanf("%d",&bday[x]);
  }
 system("cls");
  selection();

  printf("STUDENT NUMBER\t:\t%s",sno);
  printf("\nSTUDENT NAME\t:\t%s",name);

  printf("\n\nCOUNT\tBCODE\t\tDAYS\n");
  for(y=1; y<=nbook; y++)
  {
  printf("%d\t",y); ///////I use if else because the Lvalue required error was always popping, and I use if else to transfer the book code into the actual name of the book./////
   if(bcode[y]==1)
   {
printf("ENGLISH");
   }else if(bcode[y]==2){
    printf("MATH");
   }else if(bcode[y]==3){
    printf("FIL1");
   }else if(bcode[y]==4){
    printf("EPP");
   }else if(bcode[y]==5){
    printf("PE");
   }else if(bcode[y]==6){
    printf("SOCIAL");
   }else if(bcode[y]==7){
    printf("BOB'ong");
   }

   else{
    printf("INVALID");
   }
  printf("\t\t%d\n",bday[y]);
  }
getch();
}