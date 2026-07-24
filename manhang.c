#include <stdio.h>
#include <stdlib.h>
#include  <time.h>
#include <string.h>
int i,j,k,sum=0,r,flag,size,attempt;
  char g='\0';
  int vk=0;
  int v=0;
  char rules;
  char check[15];
  char guess[15];
  char a[20][15]={"apple",
  "ball",
  "cat",
  "dog",
  "earth",
  "flat",
  "fuadsir",
  "habit",
  "sakibsir",
  "infinite",
  "zerinamam",
  "jackfruit",
  "jungle",
  "kill",
  "laugh",
  "life",
  "lavender",
  "lavish",
  "yolk",
  "work"
  };
void match_check(){  
  guess[vk++]=g;
    for(j=0;j<size;j++){
    if(a[r][j]==g){
        flag=1;
        if(a[r][j]==g && check[j]=='_'){
          flag=1;
          check[j]=g;
          sum++;
        }
      }
  }
}
void prev_guess(){
v=0;
printf("\n your guesses are; ");
    while(guess[v]!='\0'){
       printf("%c ",guess[v]);
       v++;
        }

}
void current_state(){
  printf("\n\n the state of the word is\n       ");
    for(j=0;j<size;j++){
        printf("%c",check[j]);
      }
}
int menu(){    
    g='\0';
    vk=0;
    attempt=6;
    printf("\n press q to quit anything else to play ");
    scanf(" %c",&g);
  if(g=='q'){return 1;}
  else{
 printf("\n press r to view the rules. press anything else to skip");
    scanf(" %c",&rules);
    if(rules=='r'){
    printf("\nYou have made the choice to play the game\nthe rules are simple\n-You will be given a hidden word to guess\n");
    printf("-you will guess one letter at a time\n-each time you guess the correct letter, every single position that letter exists in the word will be revealed.\n");
    printf("-you will also be able to see the past guesses.\n ***BUT BE CAREFULL!***\n each time you guess wrong you will lose a life.\n-In the beginning you start with 6 lives.\n-Every single wrong guess takes away one of them.\n-If you manage to guess the word before the lives run out,you win\n-BUT IF THE LIVES RUN OUT FIRST......YOU WILL BE HANGED\n");
    printf("the correct total word will be shown after the game ends.\n\n             goodluck\n\n");
    }
    else{printf("\n looks like you have played this game before!\n");}
    for(int b=0;b<15;b++){
      check[b]='_';
    }
    for(j=0;j<15;j++){
        guess[j]='\0';
      }
    sum=0;
    v=0;
    r= rand()%20;
    size=strlen(a[r]);
    printf("\nthe hidden state of the word is\n    ");
    for(int x=0;x<size;x++){printf("%c",check[x]);}
    return 0;
  }
}
void hangman(int x){
if(x==6)
printf("\n\n +---+\n\n |   |\n\n     |\n\n     |\n\n     |\n\n     |\n\n");
if(x==5)
printf("\n\n +---+\n\n |   |\n\n o   |\n\n     |\n\n     |\n\n     |\n\n");
if(x==4)
printf("\n\n +---+\n\n |   |\n\n o   |\n\n/    |\n\n     |\n\n     |\n\n");
if(x==3)
printf("\n\n +---+\n\n |   |\n\n o   |\n\n/|   |\n\n     |\n\n     |\n\n");
if(x==2)
printf("\n\n +---+\n\n |   |\n\n o   |\n\n/|\\  |\n\n     |\n\n     |\n\n");
if(x==1)
printf("\n\n +---+\n\n |   |\n\n o   |\n\n/|\\  |\n\n/    |\n\n     |\n\n");
if(x==0)
printf("\n\n +---+\n\n |   |\n\n o   |\n\n/|\\  |\n\n/ \\  |\n\n     |\n\n");

printf("=========\n\n");

printf(" YOU HAVE ONLY %d ATTEMPTS LEFT\n",x);
return ;
}

int main(){
  srand(time(NULL));
  printf("\n==========WELCOME!=========\n the game was made by Mohammad Arshadul Bashar,roll 18,BSSE 18th batch\n");
    while(1){
      if(menu()==1)break;
        while(attempt!=0){
           flag=0;
           printf("\n enter the letter you guessed:\n (if you enter 2 letters only first one will be counted)\n");
           scanf(" %c",&g);
          if(g>='A'&& g<='Z'){
              g=g+32;
           }
          if(!(g>='a'&& g<='z')){
            printf("\n invalid input enter again: ");
            continue;
          }
        
           match_check();
           prev_guess();
           current_state();


           if(flag==0){attempt--;  printf("\n\n BUZZZZ! WRONG GUESS! YOU WILL LOSE 1 LIFE!\n");}
           hangman(attempt);
           printf("\n");
           if(sum==size){
            printf("\n YOU HAVE MANAGED TO GUESS THE CORRECT WORD!\n YOU HAVE ESCAPED THE HANGING!\n");
            break;
           }

          if(attempt==0){printf("\n YOU HAVE FAILED TO GUESS THE WORD AND WERE HANGED");};
        }
     printf("\n           the correct word is :\n                 %s \n",a[r]);
    }
  
   return 0;
}
