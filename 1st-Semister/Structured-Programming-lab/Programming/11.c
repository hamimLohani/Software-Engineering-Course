#include <stdio.h>
int main()
{
  int a, b, small, larg;
  printf("Enter length of array-1 : ");
  scanf("%d", &a);
  int arr1[a];
  printf("Enter elements of array 1 : ");
  for (int i = 0; i < a; i++)
    scanf("%d", &arr1[i]);

  printf("Enter length of array-2 : ");
  scanf("%d", &b);
  int  arr2[b], arr3[a + b];
  printf("Enter elements of array 2 : ");
  for (int i = 0; i < b; i++)
    scanf("%d", &arr2[i]);

  for (int i = 0; i < a; i++)
    arr3[i] = arr1[i];
  
  for (int i = a; i < a + b; i++)
    arr3[i] = arr2[i];
  
  int temp, n = a + b;

  for (int i = 0; i < n; i++)
    printf("%d ", arr3[i]);

  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if ((arr3[j] > arr3[j + 1]))
      {
        temp = arr3[j];
        arr3[j] = arr3[j + 1];
        arr3[j + 1] = temp;
      }
    }
  }

  for (int i = 0; i < n; i++)
    printf("%d ", arr3[i]);

}