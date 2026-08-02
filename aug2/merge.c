
#include <stdio.h>
#include<stdlib.h>
   void merge(int *a, int *left, int n1, int *right, int n2, int l) {
    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
     if (*(left + i) <= *(right + j)) {
            *(a + k) = *(left + i);
            i++;
        } 
     else {
            *(a+k) = *(right+j);
            j++;
        }
        k++;
    }
    while (i<n1) {
        *(a+k) = *(left+i);
        i++;
        k++;
    }
    while (j<n2) {
        *(a+k) = *(right+j);
        j++;
        k++;
    }
}
int main(){
  int  i,size;
  int n,m;
  printf("enter array1 size(malloc needs a size)\n");
  scanf("%d",&n);
  int *left=(int*)malloc(sizeof(int)*n); 
  printf("enter array1(pls enter a sorted one) \n");
  for(i=0;i<n;i++) scanf("%d",&*(left+i));

  printf("enter array2 size(malloc needs a size)\n");
  scanf("%d",&m);
  printf("enter array2(pls enter a sorted one) \n");
  int *right=(int*)malloc(sizeof(int)*m); 
  for(i=0;i<m;i++) scanf("%d",&*(right+i));
  
  
  int *r=(int*)malloc(sizeof(int)*(m+n));
  
  merge(r,left,n,right,m,0);
  printf("\n");
  for(i=0;i<n+m;i++) printf(" %d",*(r+i));
  printf("\n");
  free(r);
  free(left);
  free(right);
  return 0;
}
