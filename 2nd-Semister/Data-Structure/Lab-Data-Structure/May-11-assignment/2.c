#include <stdio.h>

#define MAX 100
int stack[MAX];
int stack_[MAX];
int top_ = -1, top = -1;

void push(int temp) {
    if (top < MAX - 1) {
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
    return stack[top++];
}

void push_(int temp) {
    if (top_ < MAX - 1) {
        stack_[++top_] = temp;
        return;
    }
    printf("**Stack overflow**\n");
}

int pop_() {
    if (top_ < 0) {
        printf("**Stack underflow**\n");
        return -1;
    }
    return stack_[top_++];
}

int main() {
    int arr[] = {1,2,3,4,5,6,7,8,9,0};
    
    while (1) {
        printf("\n\t===== Menu =====\n");
        printf("\t1. Push 1st stack\n");
        printf("\t2. Push 2nd stack\n");
        printf("\t3. Pop 1st stack\n");
        printf("\t4. Pop 2nd stack\n");
        printf("\t5. Show 1st stack\n");
        printf("\t6. Show 2nd stack\n");
        printf("\t7. Exit\n");

        int choice, index;
        printf("Enter choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Index : ");
            scanf("%d", &index);
            push(arr[index]);
            break;
        case 2:
            printf("Index : ");
            scanf("%d", &index);
            push_(arr[index]);
            break;
        case 3:
            pop();
            break;
        case 4:
            pop_();
            break;
        case 5:
            printf("Stack-1 : ");
            for (int i = 0; i <= top; i++) printf("%d ", stack[i]);
            break;
        case 6:
            printf("Stack-2 : ");
            for (int i = 0; i <= top_; i++) printf("%d ", stack_[i]);
            break;
        case 7:
                return 0;
            break;
        
        default:
            continue;
        }
    }
    return 0;
}