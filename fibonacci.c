#include<stdio.h>
int fibo(int n){
  if(n<1) return 0;
  if(n==1) return 1;
  return fibo(n-1) + fibo(n-2);
}
int main(){
  int n;
   printf("enter the fibonacci you want to know\n");
  scanf("%d",&n);
  printf("%d",fibo(n));
  printf("\n");
  return 0;

}
