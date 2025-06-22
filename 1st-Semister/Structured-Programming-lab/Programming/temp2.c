#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **mat1, **mat2;
    int row, col;

    printf("Enter row : ");
    scanf("%d", &row);
    printf("Enter col : ");
    scanf("%d", &col);

    // memory allocating
    mat1 = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
        mat1[i] = (int *)malloc(col * sizeof(int));
    // initializing
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            mat1[i][j] = rand() % 10;
    // memory allocating
    mat2 = (int **)malloc(col * sizeof(int *));
    for (int i = 0; i < col; i++)
        mat2[i] = (int *)malloc(row * sizeof(int));
    // initializing
    for (int i = 0; i < col; i++)
        for (int j = 0; j < row; j++)
            mat2[i][j] = rand() % 10;

    printf("Matrix 1 \n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d\t", mat1[i][j]);
        }
        printf("\n");
    }
    printf("Matrix 2 \n");
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            printf("%d\t", mat2[i][j]);
        }
        printf("\n");
    }
    int sum = 0;
    int **mat3;

    mat3 = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
        mat3[i] = (int *)malloc(row * sizeof(int));

    printf("multiplication : \n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < row; j++)
        {
            for (int k = 0; k < col; k++) // col
            {
                sum = sum + mat1[i][k] * mat2[k][j]; // row x col
            }
            mat3[i][j] = sum;
            printf("%d\t", mat3[i][j]);
            sum = 0;
        }
        printf("\n");
    }

    return 0;
}
