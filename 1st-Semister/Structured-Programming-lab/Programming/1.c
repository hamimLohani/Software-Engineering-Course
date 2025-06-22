#include<stdio.h>
#include <stdlib.h>

// int main(int argc, char const *argv[])
// {
//   char ch;
  
//   int a,b,c;
//   scanf("%d %d",&a,&b);
// scanf("%c",&ch);
//   c=a;
//   a=b;
//   b=c;
//   printf("%c %d",ch,ch);
//   return 0;
// }
int main(int argc, char const *argv[])
{
  int i;
  double d;
  long l;
  i = atoi(argv[1]);
  d = atod(argv[2]);
  l = atoi(argv[3]);
  printf(" i = %d l = %ld d = %lf", i, l, d);
  return 0;
}
