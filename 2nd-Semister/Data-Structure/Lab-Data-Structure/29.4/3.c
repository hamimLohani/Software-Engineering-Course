#include <stdio.h>

int top = 0;

void push(char element, char arr[], int size) {
    if(top >= size) {
        printf("**Stack overflow**\n");
        return;
    }
    arr[top++] = element; 
}
char pop(int size, char arr[]) {
    if (top <= size && top > 0){
        top--;
        return arr[top];
    } if (top == 0)
        printf("**Stack underflow**\n");
}
int main() {
    int size;
    printf("Enter size of stack : ");
    scanf("%d", &size);
    char arr[size];

    printf("Enter element size : ");
    int l;
    scanf("%d", &l);
    getchar();

    for (int i = 0; i < l; i++) {
        char temp;
        printf("Element : ");
        scanf("%c", &temp);
        push(temp, arr, size);
        getchar();
    }

    int mid = top / 2;
    for (int i = 0; i < mid; i++) {
        if (arr[i] != pop(size, arr)) {
            printf("False\n");
            return 0;
        }
    }
    printf("True\n");
}