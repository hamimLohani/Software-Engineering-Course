#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
  int n;
  scanf("%d", &n);
  int bi, dec = 0, sum = 0;
  for (int i = n; i > 0; i--)
  {
    bi = rand() % 2;
    sum= sum*10+bi;
  }
  
  
  
}
