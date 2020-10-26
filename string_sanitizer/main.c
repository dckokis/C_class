#include <stdio.h>
#include <ctype.h>
#define N 1000
// пунктуацию дабавить, новое предложение с большой буквы, убирать пробелы
// в начале и в конце строки, передавать размер строки в функцию
void str_sanitize(char *string, size_t size)
{
    int r, w;
    int space = 0;
    for (r = w = 0; string[r] != '\0'; r++) {
        if (isspace(string[r]) == 0){
            string[w++] = string[r];
            space = 0;
        } else{
            if(space == 0){
                string[w++] = string[r];
            }
            space = 1;
        }
    }
    string[w] = '\0';
}

int main()
{
    char str[N];
    printf("Input string:\n");
    gets_s(str, N);
    size_t size = sizeof(str);
    str_sanitize(str, size);
    printf("\n%s", str);
    return 0;
}
