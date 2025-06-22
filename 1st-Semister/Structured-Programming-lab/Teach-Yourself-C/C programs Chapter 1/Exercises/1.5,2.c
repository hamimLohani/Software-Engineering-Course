#include <stdio.h>
void main(void)
{
    unsigned long long int seconds;
    seconds = 365 * 24 * 60 * 60;
    printf("The result is %llu", &seconds);
}
