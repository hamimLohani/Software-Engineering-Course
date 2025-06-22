#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void my_scanf(char* format, void* location)
{
    char buf[1000];

    fgets(buf, 1000, stdin);

    if(!strcmp(format, "%s"))
    {
        strcpy(location, buf);
        return;
    }
    if(!strcmp(format, "%d"))
    {
        *((int *)location) = atoi(buf);
        return;
    }
        

    return;
}


int main(int argc, char** argv)
{
    char buf[100] = {0};
    int a;
    FILE* fptr = fopen("hello.txt", "w");
    my_scanf("%s", (void*)buf);
    my_scanf("%d", &a);
    printf(buf);
    printf("%d\n", a);
}