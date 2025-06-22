#include <stdio.h>
int main()
{
    char ch;

    printf("Enter a character between A To Z or a to z:");
    ch = getch();
    printf("\n Its ASCII code is %d", ch);

    return 0;
}
