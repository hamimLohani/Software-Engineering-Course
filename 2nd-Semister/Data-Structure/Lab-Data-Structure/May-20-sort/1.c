
/*
 *merge sort according to alphanumeric value
*/
#include <stdio.h>
#include <string.h>

void merge(char str[], int st, int mid, int en) {
    int n1 = mid - st + 1, n2 = en - mid;
    char l[n1], r[n2];

    for (int i = 0; i < n1; i++)
        l[i] = str[st + i];

    for (int i = 0; i < n2; i++)
        r[i] = str[mid + i + 1];
    
    int i =0, j = 0, k = st;
    while (i < n1 && j < n2) {
        if (l[i] <= r[j])
            str[k++] = l[i++];
        else 
            str[k++] = r[j++];
    }
    while (i < n1)
        str[k++] = l[i++];
    
    while (j < n2)
        str[k++] = r[j++];    
}

void mergeSort(char arr[], int st, int en) {
    if (st < en) {
        int mid = st + (en - st) / 2;
        mergeSort(arr, st, mid);
        mergeSort(arr, mid + 1, en);
        merge(arr, st, mid, en);
    }
}

int main() {
    char str[] = "hello";
    mergeSort(str, 0, strlen(str) - 1);
    printf("%s", str);
}