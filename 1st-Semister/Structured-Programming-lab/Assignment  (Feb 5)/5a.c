#include <stdio.h>
#include <string.h>

int main() {

    FILE *fp;
    char str[20];
    char f_str[100];
    printf("Enter file name : ");
    scanf("%s", str);
    printf("Enter text : ");
    fgets(f_str, sizeof(f_str), stdin);
    strcat(str, ".txt");

    fp = fopen(str, "w");
    fprintf(fp, "%s", f_str);
    fclose(fp);
}