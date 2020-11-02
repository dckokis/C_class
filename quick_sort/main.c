#include <stdio.h>
#include <stdlib.h>
#define N 1000
int int_cmp(void *x, void *y) {
    int x_value = *(int*)x;
    int y_value = *(int*)y;

    if (x_value == y_value) {
        return 0;
    } else if (x_value < y_value) {
        return -1;
    } else {
        return 1;
    }
}

int double_cmp(void *x, void *y) {
    double x_value = *(double*)x;
    double y_value = *(double*)y;

    if (x_value == y_value) {
        return 0;
    } else if (x_value < y_value) {
        return -1;
    } else {
        return 1;
    }
}

void swap(void* a, void* b, const size_t size) {
    for (size_t i = 0; i < size; i++){
        char *i1 = (char*)a + i;
        char *i2 = (char*)b + i;
        char tmp = *i1;
        *i1 = *i2;
        *i2 = tmp;
    }
}

// Функцию необходимо вызывать с соответствующей функцие сравнения для double/integer
// в зависимости от используемого типа данных в массиве
void quick_sort(void* arr, unsigned int len_arr,
                unsigned int size_elem, int (*cmp)(void*, void*)) {
    if(len_arr == 1){
        return;
    }
    unsigned int i = 0; // индексы левой половины
    unsigned int j = len_arr - 1; // индексы правой половины
    void *median = (char *)arr + (len_arr/ 2) * size_elem;
    void *left = (char *)arr;
    void *right = (char *)arr + (len_arr - 1) * size_elem;
    while (i < j && i < len_arr - 1 && j > 0) {
        if (cmp(median, left) == 1 && cmp(median, right) == -1) {
            i++;
            j--;
            continue;
        } else if (cmp(median, left) == -1 && cmp(median, right) == 1) {
            swap(left, right, size_elem);
            i++;
            j--;
        } else if (cmp(median, left) == cmp(median, right)) {
            if(cmp(left, right) == 1){
                j--;
                continue;
            }else if(cmp(left, right) == -1){
                i++;
                continue;
            }else if(cmp(left, right) == 0){
                if(cmp(median, left) == 1){
                    i++;
                    continue;
                }else if(cmp(median, left) == -1){
                    j--;
                    continue;
                }
            }
            continue;
        }
    }

    swap(median, right, size_elem);
    unsigned int size_left = len_arr / 2;
    unsigned int size_right = len_arr - size_left;
    quick_sort((char *)arr, size_left, size_elem, cmp);
    quick_sort((char *)arr + size_right * size_elem, size_right, size_elem, cmp);
}
int main() {
    double A[N] = {0};
    FILE *stream;
    stream = fopen ("C:\\C_class\\quick_sort\\cmake-build-debug\\CMakeFiles\\Input.txt", "r");
    if(stream == 0){
        printf("File is not found");
        exit(1);
    }
    int i;
    unsigned int length;
    fscanf_s(stream, "%d", &length);
    unsigned  int amount  = 0;
    for(i = 0; i < length; i++) {
        fscanf_s(stream, "%lf", &A[i]);
        printf("%g ", A[i]);
        amount ++;
    }
    if(amount != length){
        exit(1);
    }
    size_t size_elem = sizeof(double);
    quick_sort(A, length, size_elem, double_cmp);
    printf("Sorted array:");
    for(i = 0; i < length; i++){
        printf("%g ", A[i]);
    }
    return 0;
}