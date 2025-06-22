#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *b = *a;
    *a = temp;
}

int main() {
    int a = 2, b = 3;
    swap(&a, &b);

    printf("a = %d b = %d",a, b);
}