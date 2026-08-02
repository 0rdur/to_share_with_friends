#include<stdio.h>
int add(int arr[],int i, int n){
  if(i==n)
    return 0;
  return arr[i]+ add(arr,i+1,n);
}
int main(){
int sum_arr[3]={1,2,3};
int size=sizeof(sum_arr)/sizeof(sum_arr[0]);

  printf("\n %d \n",add(sum_arr,0,size));
  return 0;

}
//main
//add(0,3) 1+ add(1,3) return 5 + 1 > return 6(goes into the main)
//add(1,3) 2+ add(2,3)> return 2 + 3; > return 5;
//add(2,3) 3+ add(3,3) > return 3+0;
//add(3,3)return 0
