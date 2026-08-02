
#include <stdio.h>
#include<stdlib.h>
void reverse(int *p,int i,int size){
  int x=0;
  if(i==size/2) return ;
  x=*(p+i);
  *(p+i)=*(p+size-i-1);
  *(p+size-i-1)=x;
  
  reverse(p,i+1,size);
}
int main(){
  int  i,size;
  int n;
  printf("enter array size(malloc needs a size)\n");
  scanf("%d",&n);
  int *p=(int*)malloc(sizeof(int)*n); 
  printf("enter array \n");
  for(i=0;i<n;i++) scanf("%d",&*(p+i));
  for(i=0;i<n;i++) printf(" %d",*(p+i));
  printf("\nultano array;\n");
  reverse(p,0,n);
for(i=0;i<n;i++){
    printf(" %d ",*(p+i));
    
  }
  printf("\n");
  free(p);
  return 0;
}
