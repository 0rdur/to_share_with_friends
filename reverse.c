#include<stdio.h>
void recur_rev(int a[],int n,int i){
  if(i==n/2) return;//terminator
  int temp;
  temp=a[i];
  a[i]=a[n-1-i];//swaps
  a[n-i-1]=temp;
  recur(a,6,i+1);//recursive call
}

int main(){
  int a[]={1,2,3,4,5,6};
  for(int i=0;i<6;i++) printf("%d",a[i]);
  recur_rev(a,6,0);
  printf("\n");
  for(int i=0;i<6;i++) printf("%d",a[i]);
  return 0;
}
  
  

