#include<stdio.h>

#define SIZE 100

int stack[SIZE];
int top = -1;

void swap(int *a,int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[],int low,int high){
    int pivot = arr[high];
    int i = low-1;
    for(int j = low;j<high;j++){
        if(arr[j]<pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    i++;
    swap(&arr[i],&arr[high]);
    return i;
    
}
void quick_sort(int arr[],int n){
    
    stack[++top]=0;
    stack[++top]=n-1;
    while(top>=0){
        int high = stack[top--];
        int low = stack[top--];

        int p = partition(arr,low,high);
        if(p-1>low){
            stack[++top]=low;
            stack[++top]=p-1;

        }if(p+1<high){
            stack[++top]=p-1;
            stack[++top]=high;
        }
    }
}

int main(){
    int arr[]={12,34,23,434,545};
    quick_sort(arr,5);
    for (int i = 0; i < 5; i++)
        printf("%d ", arr[i]);
    
    return 0;
}