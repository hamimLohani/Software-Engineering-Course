#include <stdio.h>

int main()
{
    char mess[80];
    int i;

    printf("Enter message (less than 80 characters) \n");
    for (i = 0; i < 80; i++)
    {
        mess[i] = getch();
        if (mess[i] == '\r')
            break;
    }
    printf("\n");

    for (i = 0; mess[i] != '\r'; i++)
        printf("%c", mess[i] + 1);

    return 0;
}
