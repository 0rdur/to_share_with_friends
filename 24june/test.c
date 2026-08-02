
#include<stdio.h>

// sakib sir just taught us about the basics of array. sizeof was not a part of the lesson
int main ()
{
  int n;
  printf("size of array is: ");
  scanf("%d",&n);
int F[n];
 int i;
  for (i=0;i<n;i++){
   scanf("%d",&F[i]);
  }
for (i=0;i<n;i++){
   printf("%d ",F[i]);
  }
return 0;
}
