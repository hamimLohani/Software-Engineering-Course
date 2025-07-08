// erase the middle value
// insert a new value in that position
#include <stdio.h>
# define SIZE 10
int arr[SIZE];
int main() {
    int mid = SIZE / 2;
    printf("Enter array element : ");
    for (int i = 0; i < SIZE; i++)
        scanf("%d", &arr[i]);
    
    for (int i = mid; i < SIZE; i++)
        arr[i] = arr[i + 1];
    
    for (int i = 0; i < SIZE - 1; i++)
        printf("%d\t", arr[i]);
    
    for (int i = SIZE - 1; i >= mid; i--)
        arr[i] = arr[i - 1];

    printf("\nEnter an element : ");
    scanf("%d", &arr[mid]);

    for (int i = 0; i < SIZE; i++)
        printf("%d\t", arr[i]);
    
    
}