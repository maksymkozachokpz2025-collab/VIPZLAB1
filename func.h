#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Book {
    char author[50];
    char title[50];
    int year;
    int pages;
    float cost;
    struct Book *next;
} Book;

// Прототипи функцій
void loadFromFile(const char *filename, Book **head);
void saveToFile(const char *filename, Book *head);
void printBooks(Book *head);
void findAuthorsByLetter(Book *head, char letter);
void delCheaperThanAvg(Book **head);
void freeList(Book *head);
void insertSorted(Book **head, Book newBookData);

#endif
