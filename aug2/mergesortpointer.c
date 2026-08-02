#include <stdio.h>
#include <stdlib.h>
void merge(int *a,int l,int m,int r)
{
    int n1 = m-l+1;
    int n2 = r-m;
    int L[n1];
    int *left=L;
    int R[n2];
    int *right=R;



    for(int i=0;i<n1;i++)
        *(left+i) = *(a+l+ i);

    for(int j=0;j < n2;j++)
    *(right+j)= *(a+m+1+j);

    int i = 0;
    int j = 0;
    int k = l;

    while(i<n1 && j<n2)
    {
        if(*(left+i) <= *(right+j))
        {
            *(a+k)=*(left+i);
          i++;
        }
        else
        {
         *(a+k)=*(right+j);
            j++;
        }
            k++;
    }

    while(i<n1)
    {
      *(a+k)=*(left+i);
        i++;
        k++;
    }

  while(j<n2)
    {
        *(a+k)=*(right+j);
        j++;
        k++;

    }
}

void mergesort(int* a,int l,int r)
{
    if(l<r)
    {
      int m = l + (r-l)/2;

        mergesort(a,l,m);
        mergesort(a,m+1,r);

        merge(a,l,m,r);
    }
}

int main(){
  int  i,size;
  int n;
  printf("enter array size(malloc needs a size)\n");
  scanf("%d",&n);
  int *p=(int*)malloc(sizeof(int)*n); 
  printf("enter array \n");
  for(i=0;i<n;i++) scanf("%d",&*(p+i));

  printf("Before the sort \n");
  for(i=0;i<n;i++) printf("%d",*(p+i));
    
  printf("\n");
  mergesort(p,0,n-1);

  printf("After the sort \n");
  for(i=0;i<n;i++) printf("%d",*(p+i));

    printf("\n");
    free(p);
    return 0;
    
}
