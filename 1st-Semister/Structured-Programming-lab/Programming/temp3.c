
//vertex and degree related problem of a directed graph
#include <stdio.h>
#include <stdlib.h>

int test()
{
    char ch;
    int x;
    printf("Want to test (y/n) : ");
    fflush(stdin);
    scanf("%c", &ch);
    if (ch == 'y')
        x = 1;
    else if (ch == 'n')
        x = 0;
    else
        test();
    return x;
}

int main()
{
    int vertex;
    printf("Number of vertex : ");
    scanf("%d", &vertex);
    int **p = (int **)malloc(vertex * sizeof(int *));
    int degree[vertex];
    for (int i = 0; i < vertex; i++)
    {
        printf("Number of out degree V(%d) : ", i);
        scanf("%d", &degree[i]);

        p[i] = (int *)malloc(degree[i] * sizeof(int));
        if (degree[i] != 0)
            printf("The vertex connected from V(%d) : ", i);
        for (int j = 0; j < degree[i]; j++)
        {
            scanf("%d", &p[i][j]);
        }
    }

    while (test())
    {
        int x, y, flag = 0;
        printf("Vertex (from) : ");
        scanf("%d", &x);
        printf("Vertex (to) : ");
        scanf("%d", &y);
        getchar();
        for (int j = 0; j < degree[x]; j++)
            if (p[x][j] == y)
                flag = 1;

        if (flag)
            printf("Yes.\n");
        else
            printf("No\n");
    }
}