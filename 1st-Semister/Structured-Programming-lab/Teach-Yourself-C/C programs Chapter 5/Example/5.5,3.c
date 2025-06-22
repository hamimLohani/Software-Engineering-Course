#include <stdio.h>

int main(void)
{
    char *text[] = {
        "When", "in", "the",
        "course", "of", "human",
        "events", NULL};

    int i, j;

    // now display them
    for (i = 0; text[i]; i++)
    {
        for (j = 0; text[i][j]; j++)
        {
            printf("%c", text[i][j]);
        }
        printf(" ");
    }

    return 0;
}
