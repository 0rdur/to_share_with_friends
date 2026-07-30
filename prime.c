#include<stdio.h>
void prime(int n){
  int f;

  if(n==1){return;}
    prime(n-1);
  f=1;
  for(int i=2;i<n;i++){
    if(n%i==0){
      f=0;
      break;}
  }
    if(f==1) printf("%d ",n);

  }

int main(){
  printf("\n");
  prime(100);
  printf("\n");
 return 0;
}
