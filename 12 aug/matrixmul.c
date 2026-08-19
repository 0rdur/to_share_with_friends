#include <stdio.h>
#include <stdlib.h>

int main(){

    int row1,row2,col1,col2;

    printf("Enter row and column of matrix 1:\n");
    scanf("%d %d", &row1, &col1);

    printf("Enter row and column of matrix 2:\n");
    scanf("%d %d", &row2, &col2);

    if (col1!=row2){
        printf("Column of matrix1 must be equal to row of matrix2,begin again pls\n");
        return 0;
    }

    int **mat1;
    int **mat2;

    mat1=malloc(row1*sizeof(int*));// array of pointers banalam

    for(int i=0;i<row1;i++){
        *(mat1+i)=malloc(col1*sizeof(int));//er protita pointer e clumn er poriman space dilam. so, 1d array create hoye gelo
    }

    mat2=malloc(row2*sizeof(int*));

    for(int i=0;i<row2;i++){
        *(mat2+i)=malloc(col2*sizeof(int));
    }

    printf("Enter the first matrix:(first  row,then 2nd row....in that order)\n");

    for (int i=0;i<row1;i++){
        int *temp=*(mat1+i);//temp namer adress e oije initialise kora pointer er adress rakhlam

        for (int j=0;j<col1;j++){
            scanf("%d",temp+j);//full row nilam,jeta ashole oi initialized tate gese
        }
    }

    printf("Enter second matrix:(same as the last one)\n");

    for (int i=0;i<row2;i++){
        int *temp =*(mat2+i);
        for (int j=0;j<col2;j++){
            scanf("%d",temp+j);
        }
    }

    printf("the end result of the matrix multiplcation is:\n");

    for (int i=0;i<row1;i++){
        for (int j=0;j<col2;j++){
            int sum=0;
            for (int k=0;k<col1;k++){
                sum += (*(*(mat1+i)+k)) * (*(*(mat2+k)+j));//i means row of 1st,k maintains the col of first,j changes the col of 2nd,
            }

            printf("%d ",sum);
        }
        printf("\n");
    }

    for (int i=0;i<row1;i++) free(*(mat1+i));
    

    free(mat1);

    for (int i=0;i<row2;i++) free(*(mat2+i));
  

    free(mat2);

    return 0;
}
