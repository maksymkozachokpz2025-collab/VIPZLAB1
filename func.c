#include "func.h"

void insertSorted(Book **head, Book data) {
    Book *newBtn = (Book *)malloc(sizeof(Book));
    if (!newBtn) return;
    
    *newBtn = data; // Копіюємо дані
    newBtn->next = NULL;

    // Сортування за вартістю (зростання)
    if (*head == NULL || (*head)->cost >= newBtn->cost) {
        newBtn->next = *head;
        *head = newBtn;
    } else {
        Book *current = *head;
        while (current->next != NULL && current->next->cost < newBtn->cost) {
            current = current->next;
        }
        newBtn->next = current->next;
        current->next = newBtn;
    }
}

void loadFromFile(const char *filename, Book **head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Помилка відкриття файлу для читання");
        return;
    }

    Book temp;
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        // Парсинг рядка: Автор;Назва;Рік;Сторінки;Ціна
        if (sscanf(line, "%[^;];%[^;];%d;%d;%f", 
            temp.author, temp.title, &temp.year, &temp.pages, &temp.cost) == 5) {
            insertSorted(head, temp);
        }
    }
    fclose(file);
}

void saveToFile(const char *filename, Book *head) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Помилка відкриття файлу для запису");
        return;
    }

    Book *curr = head;
    while (curr) {
        fprintf(file, "%s;%s;%d;%d;%.2f\n", 
                curr->author, curr->title, curr->year, curr->pages, curr->cost);
        curr = curr->next;
    }
    fclose(file);
}

void findAuthorsByLetter(Book *head, char letter) {
    printf("\n--- Автори на букву '%c' ---\n", letter);
    int found = 0;
    for (Book *curr = head; curr; curr = curr->next) {
        if (toupper(curr->author[0]) == toupper(letter)) {
            printf("%s (Книга: %s)\n", curr->author, curr->title);
            found = 1;
        }
    }
    if (!found) printf("Нікого не знайдено.\n");
}

void delCheaperThanAvg(Book **head) {
    if (!*head) return;

    float sum = 0;
    int count = 0;
    for (Book *curr = *head; curr; curr = curr->next) {
        sum += curr->cost;
        count++;
    }
    float avg = sum / count;
    printf("\nСередня ціна: %.2f. Видаляємо дешевші книги...\n", avg);

    Book *curr = *head, *prev = NULL;
    while (curr) {
        if (curr->cost < avg) {
            Book *temp = curr;
            if (prev == NULL) *head = curr->next;
            else prev->next = curr->next;
            
            curr = curr->next;
            free(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void printBooks(Book *head) {
    printf("\n%-15s | %-15s | %-5s | %-5s | %-7s\n", "Автор", "Назва", "Рік", "Стор.", "Ціна");
    printf("------------------------------------------------------------------\n");
    for (Book *curr = head; curr; curr = curr->next) {
        printf("%-15s | %-15s | %-5d | %-5d | %-7.2f\n", 
               curr->author, curr->title, curr->year, curr->pages, curr->cost);
    }
}

void freeList(Book *head) {
    while (head) {
        Book *temp = head;
        head = head->next;
        free(temp);
    }
}
