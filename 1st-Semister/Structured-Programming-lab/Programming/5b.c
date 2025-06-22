#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    FILE *fp;
    char str[20];
    char search_line[][100] = {0};
    int s_line[100];
    printf("Enter search word : ");
    scanf("%s", str);
    char f_str[200];
    int count = 0, line = 0, flag;
    int f_line = 0;

    fp = fopen("abc.txt", "r");
    if (fp == NULL) printf("File does not exist.\n");
    else {
        while ((fgets(f_str, sizeof(f_str), fp)) != NULL) {  
            f_line++;  
            int x = count;
            for (int i = 0; f_str[i]; i++) {
                if (str[0] == f_str[i]) {
                    flag = 1;
                    for (int j = i; j - i < strlen(str); j++) {
                        if (str[j - i] != f_str[j]) {
                            flag = 0;
                            break;
                        }
                    }
                    if (flag) count++;
                }
            }
            if (x != count) {  
                s_line[line] = f_line;
                strcpy(search_line[line++], f_str);
            }
        }
        fclose(fp);
        printf("\nTotal match : %d\n", count);
        for (int i = 0; i < line; i++) 
            printf("Line %d : %s", s_line[i], search_line[i]);
           

    }
    return 0;
}