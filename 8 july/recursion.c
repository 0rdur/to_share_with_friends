#include<stdio.h>
int fact(int n){
  if (n=0) 
    return 0;
  else
  return fact(n)*fact(n-1);

}
int pint(int n)
{printf("%d",n);
  if(n==0) return 0; //base case. makes sure the func is not runnningg infinietley and stack overflowing
  else 
    pint(n-1);//recursive call. stacks the functions that are being called. when a function is retured
  //and the func is removed  from the stcak. goes one until main fucn is finished
}
int main(){
  int n=5;
  pint(5);
  printf("fact of %d is %d",4,fact(4));
}
