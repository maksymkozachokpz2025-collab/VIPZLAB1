#include <stdio.h>
#include <stdlib.h>
#include "newfunc.h"

int main()
{
    Book *books = NULL;
    int choice = -1;
    char newAuthor[50];
    char newTitle[50];
    int newYear;
    int newPages;
    float newCost;
    float avgCost;

    loadFromFile("books.txt", &books);

    while (choice != 0)
    {
        printf("\nВиберіть що робити:\n");
        printf("0. Закінчити роботу\n");
        printf("1. Показати список книг (відсортований за вартістю)\n");
        printf("2. Додати нову книгу\n");
        printf("3. Видалити книги, дешевші за середнє\n");
        printf("4. Знайти книги авторів на букву 'А'\n");
        printf("Введіть ваш вибір: ");
        
        if (scanf("%d", &choice) != 1) {
            // Очищення буфера при некоректному вводі
            while(getchar() != '\n'); 
            continue;
        }

        if (choice == 1)
        {
            if (books == NULL)
                printf("\nСписок порожній.\n");
            else
                printBooks(books);
        }
        else if (choice == 2)
        {
            printf("\nВпишіть дані нової книги (без пробілів у тексті)\n");
            printf("Автор: ");
            scanf("%49s", newAuthor);
            printf("Назва: ");
            scanf("%49s", newTitle);
            printf("Рік: ");
            scanf("%d", &newYear);
            printf("Сторінки: ");
            scanf("%d", &newPages);
            printf("Ціна: ");
            scanf("%f", &newCost);

            insertNewBook(&books, newAuthor, newTitle, newYear, newPages, newCost);
            printf("\nКнигу успішно додано!\n");
        }
        else if (choice == 3)
        {
            if (books == NULL)
            {
                printf("\nСписок порожній.\n");
            }
            else
            {
                avgCost = calculateAvg(books);
                printf("\nСередня ціна книги зі списку: %.2f\n", avgCost);

                delCheaperThanAvg(&books, avgCost);
                printf("Книги, дешевші за %.2f, були видалені.\n", avgCost);
            }
        }
        else if (choice == 4)
        {
            if (books == NULL)
                printf("\nСписок порожній.\n");
            else
                printBooksByAuthorA(books);
        }
    }
    
    freeList(books);
    return 0;
}
