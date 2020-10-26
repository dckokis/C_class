#include <stdio.h>

int main() {
    printf("Guess the number from 1 to 100\n");
    int high = 100;
    int low  = 0;
    int middle = (high+low) / 2;
    char answer;
    while (middle >= 1 && middle <= 100 && low <= high) {
        printf("Is the guessed number higher, less or equal  then %d? h/l/e\n", middle);
        scanf_s("%c", &answer);
        getchar();
        if (answer == 'h') {
            low = middle;
        } else if (answer == 'l') {
            high = middle;
        } else if (answer == 'e') {
            break;
        } else {
            printf ("You choose something strange! (%c)\n", answer);

        }
        middle = (high+low) / 2;
    }
    printf("Your number is - %d \nWant to play again?:-)", middle);
    return 0;
}
