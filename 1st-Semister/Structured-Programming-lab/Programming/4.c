#include <stdio.h>

int main()
{
  float a;
  scanf("%f", &a);
  if (a < 1000 && a >= 500)
    printf("%f", a - .02 * a);
  if (a >= 1000 && a < 10000)
    printf("%f", a - .05 * a);
  if (a >= 10000)
    printf("%f", a - .2 * a);
  if (a < 500)
    printf("%f", a);
  return 0;
}
