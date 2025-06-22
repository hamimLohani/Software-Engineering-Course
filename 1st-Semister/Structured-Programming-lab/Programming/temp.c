#include <stdio.h>

int main()
{
  int a, b;
  printf("Enter the row : ");
  scanf("%d", &a);

  printf("Enter the colomn : ");
  scanf("%d", &b);

  int arr[a][b];
  for (int i = 0; i < a; i++)
    for (int j = 0; j < b; j++)
    {
      arr[i][j] = i;
    }

  
  int n, x, y;
  scanf("%d", &n);

  x = n % a;
  y = n / a;

  printf("Row : %d\nColomn : %d\n", x - 1, y);
}