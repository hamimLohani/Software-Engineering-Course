#include <stdio.h>

#define MAX 100
int stack[MAX];
int top = -1;

void push(int temp) {
    if (top <= MAX - 1) {
        stack[++top] = temp;
        return;
    }
    printf("**Stack overflow**\n");
}

int pop() {
    if (top < 0) {
        printf("**Stack underflow**\n");
        return -1;
    }
    return stack[top--];
}
 
int main() {
    int num;
    printf("Enter number : ");
    scanf("%d", &num);

    while (num != 0) {
        push(num % 2);
        num /= 2;
    }
    while (top >= 0) printf("%d", pop());

    return 0;
}