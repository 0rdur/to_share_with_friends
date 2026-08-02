
#include <stdio.h>
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
   int x,y;
    int h,j;
    printf("\npick the element to swap, followed by the one you would like to replace it with\n");
    scanf(" %d %d",&x,&y);
    printf("\nthe swapped array is :");
    for (i=0;i<n;i++){
      if (*(p+i)==x) *(p+i)=y;
    }     
    for (i=0;i<n;i++){
      printf("%d ",*(p+i));
    }
    free(p);
 return 0;
 }
