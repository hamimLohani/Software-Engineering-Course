#include <stdio.h>

#define MAX 100
int stackInput[MAX];
int stackOutput[MAX];
int top = -1, top1 = -1;

void push(int temp) {
    if (top < MAX - 1) {
        stackInput[++top] = temp;
        return ;
    }
    printf("**Stack overflow**\n");
}

int pop() {
    if (top < 0) {
        printf("**Stack underflow**\n");
        return -1;
    }
    return stackInput[top--];
}

void push1(int temp) {
    if (top1 < MAX - 1) {
        stackOutput[++top1] = temp;
        return ;
    }
    printf("**Stack overflow**\n");
}

int pop1() {
    if (top1 < 0) {
        printf("**Stack underflow**\n");
        return -1;
    }
    return stackOutput[top1--];
}

int main() {
    int arr[10] = {1,2,3,4,-5,6,7,0,8,-1};
    for (int i = 0; i < 10; i++) push(arr[i]);
    int min = pop();
    int i = 1;
    while (top >= 0) {
        int temp = pop();
        if (min < temp) push1(temp);
        else {
            push1(min);
            min = temp;
        }
    }
    while (top1 >= 0) printf("%d ", pop1());

    return 0;
}