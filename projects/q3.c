#include<stdio.h>
int main(){
  int n;
  int i;
  int j;
  scanf("%d",&n);
  int arr[n];
for(int i=0;i<n;i++)
  scanf("%d",&arr[i]);
 int temp;
for(int i=0;i<n;i++){
  for(int j=i;j<n;j++){
      if(arr[i]>=arr[j]){
        temp=arr[i];
        arr[i]=arr[j];
        arr[j]=temp;
      }

  }
}
int duplicate[n];
int counter[n];
  i=0;
  j=0;
  int k=0;
  int h=0;
  for(i=0;i<n;i++){
   if(arr[i]==arr[j]){
      duplicate[k]++;
      j++;
    }
    else{ 
        i=j;
        counter[k]=arr[i];
        k++;

      }
       
   }

for (i=0;i<n;i++) printf("%d ",duplicate[i]);
for (i=0;i<k;i++) printf("%d ",counter[i]);

return 0;
}
 
