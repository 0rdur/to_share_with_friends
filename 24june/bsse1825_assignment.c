#include<stdio.h>

// sakib sir just taught us about the basics of array. sizeof was not a part of the lesson
int main ()
{
  int n;

  printf("press 1 for min max,2 for swapping,3 for removing duplicates ");
    int prob;
  scanf("%d",&prob);


//minmax
  if(prob==1){
     printf("\n size of array is: ");
     scanf("%d",&n);
      int F[n];
      int i;
      for (i=0;i<n;i++){
      printf("\ninput the %d th element: ",i);
       scanf("%d",&F[i]);
      }
    printf("the array is :");
      for (i=0;i<n;i++){
         printf("%d ",F[i]);
      }
      int min=F[0];
      int max=F[0];
    for (i=0;i<n;i++){
      if(F[i]>max){
         max=F[i];
        }
      if(F[i]<min){
         min=F[i];
      }
  }

  printf("\nmin is %d \nand max is %d\n",min,max);
         printf("\n");
  }



//swap
  else if(prob==2){
    int F[n];
     int n,i;
    
     printf("\n size of array is: ");
     scanf("%d",&n);
      
      
      for (i=0;i<n;i++){
       printf("\ninput the %d th element: ",i);
       scanf("%d",&F[i]);
      }
    printf("the array is :");
      for (i=0;i<n;i++){
         printf("%d ",F[i]);
      }
    int x,y;
    int h,j;
    printf("\npick 2 elements of the array to swap\n");
    scanf(" %d %d",&x,&y);
    printf("\nthe swapped array is :");
    for (i=0;i<n;i++){
      if (F[i]==x)
         h=i;
      if (F[i]==y)
         j=i;
    }
    F[h]=y;
    F[j]=x;
    for (i=0;i<n;i++){
      printf("%d ",F[i]);
    }
         printf("\n");
  }
  //duplicate removal
    //duplicate removal
else if(prob==3){
    int n,i,j;

   printf("\ninput the array full of duplicates\n");
    printf("size of array is: ");
  scanf("%d",&n);

    int G[n];

    for(i=0;i<n;i++){
        printf("\ninput the %d th element: ",i);
        scanf("%d",&G[i]);
    }

    printf("the array full of duplicate is: ");
    for(i=0;i<n;i++){
        printf("%d ",G[i]);
    }
    printf("\n");

    for(i=0;i<n;i++){
      for(j=i+1;j<n;j++){
        if(G[i]==G[j]){
          int k;
          for(k=j;k<n-1;k++){
                    G[k]=G[k+1];
          }

          n=n-1;
          j=j-1;
        }
      }
    }

    printf("the araay without any duplicate is : ");

    for(i=0;i<n;i++){
        printf("%d ",G[i]);
    }

    printf("\n");
}
 return 0;
}
