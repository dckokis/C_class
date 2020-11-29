#include <stdio.h>
float cel_to_far() {
    float c;
    float f;

    scanf("%f", &c);

    f = ((c * 9)/5) + 32;

    printf("f = %f", f);
    return 0;

}

float far_to_cel() {
    float c;
    float f;

    scanf("%f", &f);

    c = ((f - 32)*5)/9;

    printf("c = %f", c);
    return 0;

}
int main() {
    int choise;
    printf("Input 1 for cel to far, or 0 for far to cel: \0 ");
    scanf("%d", &choise);
    if (choise == 1) {
        cel_to_far();
    } else if (choise == 0) {
        far_to_cel();
    } else {
        printf("\nWrong input! Please, try again.");
    }
}