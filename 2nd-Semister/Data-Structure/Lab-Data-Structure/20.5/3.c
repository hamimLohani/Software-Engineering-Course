/*
 *sort according to the alphanumeric value of first letter of each word
 *do not consider the upper case
*/

#include <stdio.h>
#include <string.h>

void merge(char str[][10], int st, int mid, int en) {
    int n1 = mid - st + 1, n2 = en - mid;

    char a[n1][10], b[n2][10];
    for (int i = 0; i < n1; i++)
        strcpy(a[i], str[st + i]);
    
    for (int i = 0; i < n2; i++) 
        strcpy(b[i], str[mid + 1 + i]);
    
    int i = 0, j = 0, k = st;
    while (i < n1 && j < n2) {
        if ((a[i][0] < 'a' && a[i][0] + 32 <= b[j][0]) || (b[j][0] < 'a' && a[i][0] <= b[j][0] + 32) || (b[j][0] < 'a' && a[i][0] < 'a' && a[i][0] <= b[j][0]) || (a[i][0] <= b[j][0]))
            strcpy(str[k++], a[i++]);
        else 
            strcpy(str[k++], b[j++]);
    }
    while (i < n1) 
        strcpy(str[k++], a[i++]);
    
    while (j < n2)
        strcpy(str[k++], b[j++]);
    
}

void mergeSort(char str[][10], int st, int en) {
    if (st < en) {
        int mid = st + (en - st) / 2;
        mergeSort(str, st, mid);
        mergeSort(str, mid + 1, en);
        merge(str, st, mid, en);
    }
}

int main() {
    char str[][10] = {"abc", "bcd", "acde", "def"};
    int n = sizeof(str) / sizeof(str[0]);
    mergeSort(str, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%s\n", str[i]);
    }
}