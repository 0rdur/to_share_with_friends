#include <stdio.h>
void reverse(int arr[],int i,int size){
  int x=0;
  if(i==size/2) return ;
  x=arr[i];
  arr[i]=arr[size-i-1];
  arr[size-i-1]=x;
  
  reverse(arr,i+1,size);
}
int main(){
  int  i,size;
  int arr[]={1,2,3,4,5};
  size= sizeof(arr)/sizeof(arr[0]);
  for(i=0;i<size;i++){
    printf("%d ",arr[i]);
    
  }
  printf("\nultano array;\n");
  reverse(arr,0,size);
for(i=0;i<size;i++){
    printf("%d ",arr[i]);
    
  }
  printf("\n");

  return 0;

}
