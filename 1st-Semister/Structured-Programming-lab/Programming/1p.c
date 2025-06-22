#include <stdio.h>

double* sum(double* a, double* b) {
    double *c;
    *c = *a + *b;
    
    printf("Address = %p\n", c);
    printf("sum = %lf\n", *c);
    return c;
}

int main() {
    double a, b;
    scanf("%lf %lf", &a, &b);

    double* _sum = sum(&a, &b);
    printf("sum = %lf\n", *_sum);
    printf("Address = %p\n", _sum);
}