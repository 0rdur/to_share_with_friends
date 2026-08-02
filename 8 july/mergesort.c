#include <stdio.h>
// note; it was done with the help of geek for geeks

void merge(int a[],int l,int m,int r)
{
    int n1 = m-l+1;
    int n2 = r-m;

    int L[n1];
    int R[n2];

    for(int i=0;i<n1;i++)
        L[i] = a[l + i];

      for(int j=0;j < n2;j++)
    R[j] = a[m+1+j];

    int i = 0;
    int j = 0;
    int k = l;

    while(i<n1 && j<n2)
    {
        if(L[i] <= R[j])
        {
            a[k]=L[i];
          i++;
        }
        else
        {
         a[k]=R[j];
            j++;
        }
            k++;
    }

    while(i<n1)
    {
      a[k]=L[i];
        i++;
        k++;
    }

  while(j<n2)
    {
        a[k]=R[j];
        j++;
        k++;
    }
}

void mergesort(int a[],int l,int r)
{
    if(l<r)
    {
      int m = l + (r-l)/2;

        mergesort(a,l,m);
        mergesort(a,m+1,r);

        merge(a,l,m,r);
    }
}

int main()
{
    int array[10]={10,9,6,4,3,5,1,2,8,7};

    int size=sizeof(array)/sizeof(array[0]);
    printf("Before the sort \n");

    for(int i=0;i<size;i++)
     printf("%d ",array[i]);

       printf("\n");

      mergesort(array,0,size-1);

    printf("After the sort \n");

    for(int i=0; i<size;i++)
    {
       printf("%d ",array[i]);
     }
    

    printf("\n");

    return 0;
}
