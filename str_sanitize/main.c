#include <stdio.h>
#include <ctype.h>
#define N 1000
// пунктуацию дабавить, новое предложение с большой буквы, убирать пробелы
// в начале и в конце строки
void str_sanitize(char *string){
    int r, w;
    int space = 0;
    int point = 0;

    for (r = w = 0; string[r] != '\0'; r++) {
        if (isspace(string[r]) == 0){
            if (ispunct(string[r]) != 0) {
                if (string[r] == ".") {
                    point = 1;
                    if (space == 1) {
                        string[w] = string[r];
                    }
                    
                } else
            }
            string[w++] = string[r];
            space = 0;
        } else{
            if (space == 0 && w != 0){
                string[w++] = string[r];
            }
            if (w == 0){}
            space = 1;
        }
    }
    if (isspace(string[w - 1]) != 0){
        string[w - 1] = '\0';
    } else {
        string[w] = '\0';
    }
}

int main()
{
    char str[N];
    printf("Input string:\n");
    gets_s(str, N);
    str_sanitize(str);
    printf("\n%s", str);
    return 0;
}
