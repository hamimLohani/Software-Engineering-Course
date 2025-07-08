#include <stdio.h>
#define MAX 100

int stack[MAX], top = -1;
int tempStack[MAX], tempTop = -1;

void push(int val) {
    if (top >= MAX - 1)
        printf("Stack overflow!\n");
    else
        stack[++top] = val;
}

int pop() {
    if (top == -1) {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack[top--];
}

void pushTemp(int val) {
    tempStack[++tempTop] = val;
}

int popTemp() {
    return tempStack[tempTop--];
}

int peekTemp() {
    return tempStack[tempTop];
}

void sort() {
    while (top != -1) {
        int temp = pop();

        while (tempTop != -1 && peekTemp() > temp) {
            push(popTemp());
        }

        pushTemp(temp);
    }

    while (tempTop != -1) {
        push(popTemp());
    }
}

void printStack() {
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
}

int main() {
    int arr[] = {1,12,3,4,6,5,7};
    
    for (int i = 0; i < 7; i++) push(arr[i]);

    printf("Original Stack: ");
    printStack();

    sort();

    printf("\nSorted Stack: ");
    printStack();

    return 0;
}