#include <stdio.h>
#include <string.h>
#include "quick_sort.h"
#define N 5
// написать свой memcpy и вызывать его в swap. Корректно обрабатывать ситуацию когда одна часть памяти нахлестывается на другую
// ситуации когда dest раньше source и наоборот
// создать структуру с множеством полей и сортировать ее по конкретному полю(написать разные компараторы int/double лексикографический), читать данные из файла в структуру
// сделать функцию которая из FILE * прочитает структуру
typedef struct book {
    char *name; //name of the book
    char *author; //name of the author
    char *genre; //genre of the book
    char *country; //country where the book was written
    int year; //year when the book was written
};

int author_cmp(struct book a,struct book b) {
    return strcmp(a.author, b.author);
}

int main(){
    struct book book_shelf[N];
    // War and peace
    book_shelf[0].name = "War and peace";
    book_shelf[0].author = "Leo Tolstoy";
    book_shelf[0].genre = "Historical novel";
    book_shelf[0].country = "Russia";
    book_shelf[0].year = 1869;
    // Pride and Prejudice
    book_shelf[1].name = "Pride and Prejudice";
    book_shelf[1].author = "Jane Austin";
    book_shelf[1].genre = "Romance novel";
    book_shelf[1].country = "United kingdom";
    book_shelf[1].year = 1813;
    // One Flew Over the Cuckoo's Nest
    book_shelf[2].name = "One Flew Over the Cuckoo's Nest";
    book_shelf[2].author = "Ken Kesey";
    book_shelf[2].genre = "Novel";
    book_shelf[2].country = "United States";
    book_shelf[2].year = 1962;
    // We
    book_shelf[3].name = "We";
    book_shelf[3].author = "Yevgeny Zamyatin";
    book_shelf[3].genre = "Dystopian novel";
    book_shelf[3].country = "Soviet Union";
    book_shelf[3].year = 1988;
    // Fahrenheit 451
    book_shelf[4].name = "Fahrenheit 451";
    book_shelf[4].author = "Ray Bradbury";
    book_shelf[4].genre = "Dystopian novel";
    book_shelf[4].country = "United States";
    book_shelf[4].year = 1953;

    quick_sort(book_shelf, 5, sizeof(struct book), (int (*)(void *, void *)) author_cmp);
    for(int i = 0; i < 5; i++){
        printf("Name:%s\tAuthor:%s\tGenre:%s\tCountry:%s\tYear:%d\n", book_shelf[i].name, book_shelf[i].author,
               book_shelf[i].genre, book_shelf[i].country, book_shelf[i].year);
    }
    return 0;
}