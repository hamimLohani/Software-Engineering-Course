#include <stdio.h>

int sum(int a, int b);
int sub(int a, int b);
int mul(int a, int b);
float div(int a, int b);

int main()
{
  char op;
  int a, b;
  printf("Enter two integer : ");
  scanf("%d %d", &a, &b);
  printf("Enter the operator(+,-,*,/) : ");
  scanf("%c", &op);

  if (op == '+')
    printf("Summation = %d\n", sum(a, b));
  if (op == '-')
    printf("subtraction = %d\n", sub(a, b));
  if (op == '*')
    printf("Multiplication = %d\n", mul(a, b));
  if (op == '/')
    printf("Division = %f\n", div(a, b));
  return 0;
}

int sum(int a, int b)
{
  return a + b;
}
int sub(int a, int b)
{
  return a - b;
}
int mul(int a, int b)
{
  return a * b;
}
float div(int a, int b)
{

  return (float)a / b;
}