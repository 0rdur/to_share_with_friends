
#include<stdio.h>
#include<stdlib.h>
int main(){
  int  i,size;
  int n;
  printf("enter array size(malloc needs a size)\n");
  scanf("%d",&n);
  int *p=(int*)malloc(sizeof(int)*n); 
  printf("enter array \n");
  for(i=0;i<n;i++) scanf("%d",&*(p+i));
  for(i=0;i<n;i++) printf(" %d",*(p+i));
  int min=*p;
  int max=*p;
    for(i=0;i<n;i++){
      if(*(p+i)>max) max=*(p+i);
        
      if(*(p+i)<min) min=*(p+i);
      
  }

  printf("\nmin is %d \nand max is %d\n",min,max);
         printf("\n");
	 free(p);
	 return 0;
  }	
