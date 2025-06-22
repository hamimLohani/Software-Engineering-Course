#include <stdio.h>

int main (void)
{
    short int i;
    unsigned short int u;
    
    u = 33000;
    i = u;
    
    printf("%hd %hu", i, u);
    

  return 0;
}