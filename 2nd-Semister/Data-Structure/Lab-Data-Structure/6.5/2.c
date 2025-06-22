#include <stdio.h>
#include <string.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top < MAX - 1)
        stack[++top] = c;
    else 
        printf("**Stack overflow**\n");
}

char pop() {
    if (top >= 0)
        return stack[top--];
    else 
        printf("**Stack underflow**\n");
    return '\0';
}

void strrev(char str[]) {
    int r = strlen(str) - 1, l = 0;
    while (l < r) {
        char ch = str[r];
        str[r] = str[l];
        str[l] = ch;
        l++;
        r--;
    }
}

void reverseWords(char str[]) {
    for (int i = 0; str[i]; i++) push(str[i]);
    str[0] = '\0';
    while (top >= 0) {
        char temp[20];
        int i = 0;
        while (stack[top] != ' ' && top >= 0)
            temp[i++] = pop();

        temp[i] = '\0';
        strrev(temp);
        strcat(str, temp);
        strcat(str, " ");
        if (top >= 0) pop();
    }
    printf("%s\n", str);
}

int main() {
    char str[MAX];

    printf("Enter a string: ");
    fgets(str, MAX, stdin);

    int len = strlen(str);
    if (str[len - 1] == '\n') str[len - 1] = '\0';

    reverseWords(str);

    return 0;
}