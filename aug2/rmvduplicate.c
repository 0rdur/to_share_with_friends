#include <stdio.h>
#include<stdlib.h>
int main(){
  int  i,size;
  int n,j;
  printf("enter array size(malloc needs a size)\n");
  scanf("%d",&n);
  int *p=(int*)malloc(sizeof(int)*n); 
  printf("enter array full of duplicates \n");
  for(i=0;i<n;i++) scanf("%d",&*(p+i));
  for(i=0;i<n;i++) printf("%d",*(p+i));
      for(i=0;i<n;i++){
      for(j=i+1;j<n;j++){
        if(*(p+i)==*(p+j)){
          int k;
          for(k=j;k<n-1;k++){
                    *(p+k)=*(p+k+1);
          }

          n=n-1;
          j=j-1;
        }
      }
    }
    
  printf("\nthe araay without any duplicate is : ");

  for(i=0;i<n;i++) printf("%d ",*(p+i));
  printf("\n");
   
    free(p);
    return 0;
 }

