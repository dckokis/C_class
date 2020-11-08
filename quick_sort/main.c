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
    if (len_arr == 1) {
        return;
    }
    unsigned int i = 0; // индексы левой половины
    unsigned int j = len_arr - 1; // индексы правой половины
    void *median = (char *) arr + (char) (len_arr / 2) * size_elem;
    do {
        while (cmp((char *) arr + j * size_elem, median) > 0) { //right > median
            --j;
        }
        while (cmp((char *) arr + i * size_elem, median) < 0) { //left < median
            i++;
        }
        if (i <= j) {  // after while i <= j thereat we must swap left and right
            swap((char *) arr + i * size_elem, (char *) arr + j * size_elem, size_elem);
            i++;
            --j;
        }
    }
    while (i <= j);
    // recursion
        if (len_arr > i) quick_sort((char *) arr + i * size_elem, len_arr - i, size_elem, cmp);
        if (j > 0) quick_sort((char *) arr, j + 1, size_elem, cmp);
}
int main() {
    double A[N] = {0};
    FILE *stream;
    stream = fopen ("C:\\C_class\\quick_sort\\cmake-build-debug\\CMakeFiles\\Input.txt", "r");
    if (stream == 0){
        printf("File is not found");
        exit(1);
    }
    int i;
    unsigned int length;
    fscanf_s(stream, "%d", &length); // read length of array from file
    unsigned  int amount  = 0;
    for (i = 0; i < length; i++) { // read array from file
        fscanf_s(stream, "%lf", &A[i]);
        printf("%g ", A[i]);
        amount ++;
    }
    printf("\n"); // print array
    if (amount != length){
        exit(1);
    }
    size_t size_elem = sizeof(double);
    quick_sort(A, length, size_elem, double_cmp); // sorting array
    printf("Sorted array: ");
    for (i = 0; i < length; i++){ // printing sorted array
        printf("%g ", A[i]);
    }
    return 0;
}