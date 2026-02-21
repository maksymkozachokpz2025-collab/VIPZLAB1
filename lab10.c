#include <stdio.h>
#include <stdlib.h>
#include "func.h"

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
        printf("Виберіть що робити:\n");
        printf("0 щоб закінчити\n");
        printf("1 щоб показати список книг\n");
        printf("2 щоб додати нову книгу\n");
        printf("3 щоб видалити книги дешевші за середнє\n");
        printf("Введіть що потрібно робити: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (books == NULL)
                printf("\n Список порожній.\n");
            else
                printBooks(books);
        }
        else if (choice == 2)
        {
            printf("\nВпишіть дані нової книги\n");
            printf("Автор: ");
            scanf("%s", newAuthor);
            printf("Назва: ");
            scanf("%s", newTitle);
            printf("Рік: ");
            scanf("%d", &newYear);
            printf("Сторінки: ");
            scanf("%d", &newPages);
            printf("Ціна: ");
            scanf("%f", &newCost);

            insertNewBook(&books, newAuthor, newTitle, newYear, newPages, newCost);
        }
        else if (choice == 3)
        {
            if (books == NULL)
            {
                printf("\n Список порожній.\n");
            }
            else
            {
                avgCost = calculateAvg(books);
                printf("\nСередня ціна книги з списку: %.2f\n", avgCost);

                delCheaperThanAvg(&books, avgCost);
                printf("\nКниги видалені\n");
            }
        }
    }
    freeList(books);

    return 0;
}