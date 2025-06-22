#include <stdio.h>
#include <string.h>

int main()
{
    double mark[5];
    char name[5][30];
    for (int i = 0; i < 5; i++)
    {
        printf("Enter %d(th) name : ", i + 1);
        scanf("%s", name[i]);
        getchar();
        printf("CGPA : ");
        scanf("%lf", &mark[i]);
        getchar();
    }
    int n = 0;
    printf("\nThoes who get A+ :");
    for (int i = 0; i < 5; i++)
    {
        if (mark[i] == 4)
        {
            n++;
            printf(" %s ", name[i]);
        }
    }
    printf("\nTotal number of A+ = %d\n", n);

    char temp[30];
    printf("\nEnter name to see GPA : ");
    scanf("%s", temp);

    for (int i = 0; i < 5; i++)
    {
        if (!strcmp(temp, name[i]))
            printf("CGPA of %s is %.2lf\n", name[i], mark[i]);
    }

    return 0;
}