#include <stdio.h>
int main(){
  int id[10]={111,222,333,444,555,666,777,888,999,000};
  char guest [10][100];
  int room[]={1,1,1,2,2,2,2,3,3,3,3};
  //1 means single,2 double and 3 suite
char date[10][20];
int rent[10]={500,500,500,1000,1000,1000,1000,1500,1500,1500};
int occu[10]={0};
char menu,check,proceed;
int no;
do{
    printf("press a,b,c,d,e,f respectively to add new reservants,\n seaarch for reservations by the id,\n display all reservations by date, \nto add new reservations,\n to display vacant rooms,and \nto calculate yearly reveneu");
    printf("press q to end the process");
    scanf("%c",&menu);
    if(menu=='c'){
      printf("what type of room would you like?");
     printf("press s for single,d for double and p for suite");
      scanf("%c",&check);
      if(check=='a'){
        for(int i=0;i<3;i++){
          if(occu[i]==0){
            printf("the room no %d is free");
          else{
            printf("the room no %d is occupied");
            }
      }
      }
      }
      if(check=='b'){
        for(int i=3;i<7;i++){
          if(occu[i]==0){
            printf("the room no %d is free");
          else{
            printf("the room no %d is occupied");
            }
      if(check=='b'){
        for(int i=7;i<10;i++){
          if(occu[i]==0){
            printf("the room no %d is free",i);
          else{
            printf("the room no %d is occupied",i);
            }
          printf("enter the room no you would like \n");
            scanf("%d",&no);
            printf("your rent will be %d",rent[no]);
                  printf("prooceed? enter Y to yes anything else to no");
              scanf("%c",&proceed);
                  if([proceed=='Y']){
            printf("you have chosen the room %d \n your id is %d ",no,id[no]);
                  occu[no]=1;}
                  else break;

            }
          }
          }
          }
        }

      }
    }
  }
  }while(50);
  return 0;
}
