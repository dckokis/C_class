#include <stdio.h>
#define N 100
double power(double x, long n) {
    double a = 1;
    while (n) {
        if(n%2) {
            a *= x;
            n --;
        }
        else{
            x *= x;
            n /= 2;
        }
    }
    return  a;
}

double polValue(double array[], double x, int amount){
    double res = 0;
    int j;
    for(j=0; j < amount; j++) {
        res = res + array[j] * power(x, j);
    }
    printf("\nPolynomial value: %lf", res);
    return res;
}

int main() {
    double A[N] = {0};
    double x;
    int amount;
    int i;
    printf("Input x: \n");
    scanf_s("%lf", &x);
    printf("Input integer amount of coefficients: \n");
    scanf_s("%d", &amount);
    for (i = 0; i < amount; i++) {
        printf("Input coefficients: \n ");
        scanf_s("%lf", &A[i]);
    }
    polValue(A, x, amount);
    return 0;
}