#include <stdio.h>
#include <string.h>
#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top >= MAX - 1)
        printf("Stack Overflow\n");
    else
        stack[++top] = c;
}

char pop() {
    if (top == -1)
        return '\0';
    else
        return stack[top--];
}
void strrev(char str[]) {
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void reverseString(char str[]) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i++)
    {
        push(str[i]);
    }
    int p = len - 1;
    while (p < len - 1) {
        char temp[20];
        int i = 0;
        while (stack[p--] != ' ') temp[i++] = pop();
        strrev(temp);
        printf("%s", temp);
        printf("%c", pop());
        p--;
    }
    

    printf("%s\n", stack);
    int start = top;
    

    printf("Reversed string: %s\n", str);
}

int main() {
    char str[MAX];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    reverseString(str);

    

    return 0;
}