#include<stdio.h>
int recur(int y){
  if(y/10==0){return y;}
  int remainder=y%10;
return remainder + recur(y/10);
}
int main(){
int y;
  scanf("%d",&y);
  printf("%d\n",recur(recur(y)));
return 0;
}
