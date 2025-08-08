#include <stdio.h>
#include <string.h>
//reverse a string using string

#define MAX 100
char stack[MAX];
int top = -1;

void push(char c) {
    if (top >= MAX) {
        printf("**Stack overload**\n");
        return ;
    }
    stack[++top] = c;
}
char pop() {
    if (top <= -1) {
        printf("**Stack underflow**\n");
        return '\0';
    }
    return stack[top--];
}

int main() {
    printf("Enter equation : ");
    char infix[MAX];
    scanf("%s", infix);
    int len = strlen(infix);
    for (int i = 0; i < len; i++)
        push(infix[i]);

    for (int i = 0; i < len; i++)
        infix[i] = pop();
    
    printf("%s", infix);

    return 0;
}