#include <stdio.h>

int main()
{
     int a[3][3][3], i, j, k, x = 1;

     for (i = 0; i < 3; i++)
          for (j = 0; j < 3; j++)
               for (k = 0; k < 3; k++)
               {
                    a[i][j][k] = x;
                    x++;
                    printf("%6d", a[i][j][k]);
                    // %6d - 6space before int
               }

     return 0;
}
