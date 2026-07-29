#include<stdio.h>
#include<stdlib.h>

int main()
{
   int a[6]={1,1,2,2,3,3,5};
  int b[6];
    int i;
    int j;
    int k;
    for(i=0;i<6;i++){
    if(i==11){
         if(a[i]==a[i-1]) b[k]++;
         else { 
         k++;
         b[k]++;
         }
    }
    if(a[i]==a[i+1])
        b[k]++;
      if(a[i]!=a[i+1]){
      b[k]++;
      k++;
      }}
      for(j=0;j<6;j++){
      if(j==0)
      printf("%d. ",a[j]);
      else if(a[j+1]!=a[j]) printf("%d. ",a[j]);
      else if(j==6-1)printf("%d. ",a[j]);
      else if(a[j]==a[j+1]) continue;
      k=0;
      for(i=0;i<=b[k];i++){
       printf("* ");}
       k++;
       
      printf("\n");
        
}
return 0;
}