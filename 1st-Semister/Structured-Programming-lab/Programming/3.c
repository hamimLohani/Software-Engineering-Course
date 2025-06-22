#include <stdio.h>

int main()
{
  char op;

  printf("Enter a character : ");
  scanf("%c", &op);

  if (op < 48)
    printf("Special Character\n");
  if (op < 58 && op > 47)
    printf("Number\n");
  if (op < 65 && op > 57)
    printf("Special Character\n");
  if (op < 91 && op > 64)
    printf("Capital Letter\n");
  if (op < 97 && op > 90)
    printf("Special Character\n");
  if (op < 123 && op > 96)
    printf("Small Letter\n");
  if (op > 122)
    printf("Special Character\n");

  return 0;
}