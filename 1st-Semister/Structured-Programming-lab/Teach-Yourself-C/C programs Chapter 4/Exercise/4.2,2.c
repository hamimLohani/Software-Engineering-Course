#include <stdio.h>

float soundspeed();

int main()
{
    float s;

    s = soundspeed();

    printf("your time is %f second ", s);

    return 0;
}

float soundspeed()
{
    printf("Input distence in feet : ");
    float a, b;
    scanf("%F", &a);

    b = a / 1129;

    return b;
}