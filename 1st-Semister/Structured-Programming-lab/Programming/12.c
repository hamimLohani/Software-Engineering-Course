#include <stdio.h>

int main()
{

  int n, s;
  printf("Enter element of array : ");
  scanf("%d", &n);
  int arr[n + 1];
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
  for (int i = 0; i < (n - 1) / 2 + 1; i++)
  {
    printf("%d %d ", arr[i], arr[n - i - 1]);
  }
  if (n % 2 == 1)
  {
    printf("\b\b");
  }
}