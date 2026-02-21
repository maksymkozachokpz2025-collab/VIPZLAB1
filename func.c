#include "newfunc.h"

void printHeader()
{
    printf("---------------------------------------------------------------------------------------\n");
    printf("| %-15s\t| %-15s\t| %-6s\t| %-8s | %-8s |\n", "Author", "Title", "Year", "Pages", "Cost");
    printf("---------------------------------------------------------------------------------------\n");
}

void printBooks(Book *head)
{
    Book *current = head;
    printHeader();
    while (current != NULL)
    {
        printf("| %-15s\t| %-15s\t| %-6d\t| %-8d | %-8.2f |\n",
               current->author, current->title, current->year, current->pages, current->cost);
        current = current->next;
    }
    printf("---------------------------------------------------------------------------------------\n");
}

// Нова функція для пошуку авторів на букву А
void printBooksByAuthorA(Book *head)
{
    Book *current = head;
    int found = 0;
    
    printf("\nКниги авторів, чиє прізвище починається на 'А':\n");
    printHeader();
    
    while (current != NULL)
    {
        // Перевірка на латинську 'A'/'a' та кириличну 'А' (UTF-8 зазвичай займає 2 байти)
        if (current->author[0] == 'A' || current->author[0] == 'a' || 
            strncmp(current->author, "А", 2) == 0 || strncmp(current->author, "а", 2) == 0)
        {
            printf("| %-15s\t| %-15s\t| %-6d\t| %-8d | %-8.2f |\n",
                   current->author, current->title, current->year, current->pages, current->cost);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("| %-83s |\n", "Книг таких авторів не знайдено.");
    }
    printf("---------------------------------------------------------------------------------------\n");
}

void loadFromFile(const char *filename, Book **head)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Неможливо відкрити файл '%s'.\n", filename);
        return;
    }

    char author[50], title[50];
    int year, pages;
    float cost;

    // Перевіряємо, чи зчитано рівно 5 елементів для безпеки
    while (fscanf(file, "%49s %49s %d %d %f", author, title, &year, &pages, &cost) == 5)
    {
        insertNewBook(head, author, title, year, pages, cost);
    }
    fclose(file);
}

void insertNewBook(Book **head, char *author, char *title, int year, int pages, float cost)
{
    Book *newBook = (Book *)malloc(sizeof(Book));
    strcpy(newBook->author, author);
    strcpy(newBook->title, title);
    newBook->year = year;
    newBook->pages = pages;
    newBook->cost = cost;
    newBook->next = NULL;

    // Вставка на початок, якщо список пустий або нова ціна найменша
    if (*head == NULL || (*head)->cost >= newBook->cost)
    {
        newBook->next = *head;
        *head = newBook;
        return;
    }

    Book *current = *head;
    // Пошук правильної позиції (сортування за зростанням вартості)
    while (current->next != NULL && current->next->cost < newBook->cost)
    {
        current = current->next;
    }

    newBook->next = current->next;
    current->next = newBook;
}

float calculateAvg(Book *head)
{
    if (head == NULL) return 0.0f;
    
    float sum = 0.0f; // Виправлено: тепер сума є float
    int count = 0;
    Book *current = head;
    
    while (current != NULL)
    {
        sum += current->cost;
        count++;
        current = current->next;
    }
    return (sum / count); // Тепер ділення буде дійсним (float / int)
}

void delCheaperThanAvg(Book **head, float avgCost)
{
    Book *current = *head;
    Book *prev = NULL;

    while (current != NULL)
    {
        if (current->cost < avgCost)
        {
            Book *DelBook = current;
            if (prev == NULL)
            {
                *head = current->next;
                current = *head;
            }
            else
            {
                prev->next = current->next;
                current = current->next;
            }
            free(DelBook);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

void freeList(Book *head)
{
    Book *current = head;
    while (current != NULL)
    {
        Book *temp = current;
        current = current->next;
        free(temp);
    }
}
