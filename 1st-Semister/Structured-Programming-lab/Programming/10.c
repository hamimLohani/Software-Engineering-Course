
// sort an array odd then even
#include <stdio.h>

int main()
{
  int n;
  printf("Enter the number of element : ");
  scanf("%d", &n);

  int arr[n];
  printf("Enter element of array : ");
  for (int i = 0; i < n; i++)
    scanf("%d", &arr[i]);

  int temp;
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if ((arr[j] > arr[j + 1]))
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (arr[i] % 2)
      printf("%d ", arr[i]);
  }
  for (int i = 0; i < n; i++)
  {
    if (arr[i] % 2 == 0)
      printf("%d ", arr[i]);
  }
}