#include "func.h"

int main() {
    Book *list = NULL;
    const char *dbFile = "books.txt";

    // 1. Завантаження
    loadFromFile(dbFile, &list);
    
    printf("Початковий список (з файлу, відсортований за ціною):");
    printBooks(list);

    // 2. Пошук авторів на 'A'
    findAuthorsByLetter(list, 'A');

    // 3. Видалення дешевих
    delCheaperThanAvg(&list);
    
    printf("\nСписок після видалення:");
    printBooks(list);

    // 4. Збереження результату
    saveToFile("result.txt", list);
    printf("\nРезультат збережено у 'result.txt'\n");

    freeList(list);
    return 0;
}
