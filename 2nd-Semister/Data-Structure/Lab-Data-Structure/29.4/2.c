// push a value in the last of the stack
// delete the last value from the stack
#include <stdio.h>

int top = 0;

void push(int element, int arr[], int size) {
    if(top >= size) {
        printf("**Stack overflow**\n");
        return;
    }
    arr[top++] = element; 
}
void pop(int size) {
    if (top <= size && top > 0)
        top--;
    if (top == 0)
        printf("**Stack underflow**\n");
}
int main() {
    int size;
    printf("Enter Stack size : ");
    scanf("%d", &size);
    int arr[size];
    int  opt;
    while (1) {
        printf("\n ===== Menu =====\n");
        printf("\t1. Push\n");
        printf("\t2. Pop\n");
        printf("\t3. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &opt);
        switch (opt)
        {
        case 1:
            printf("How many element : ");
            int size_stack;
            int temp;
            scanf("%d", &size_stack);
            while (size_stack--) {
                printf("Element (%d) : ", top + 1);
                scanf("%d", &temp);
                push(temp, arr, size);
            }
            break;
        case 2:
            pop(size);
            break;
        case 3:
            return 0;
        default:
            continue;
        }
        printf("Your stack : ");
        for (int i = 0; i < top; i++)
            printf("\t%d", arr[i]);
    }
}