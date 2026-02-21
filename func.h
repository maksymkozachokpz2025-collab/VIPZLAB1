#ifndef NEWFUNC_H
#define NEWFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book
{
    char author[50];
    char title[50];
    int year;
    int pages;
    float cost;
    struct Book *next;
} Book;

void printHeader();
void printBooks(Book *head);
void loadFromFile(const char *filename, Book **head);
float calculateAvg(Book *head);
void delCheaperThanAvg(Book **head, float averageCost);
void freeList(Book *head);
void insertNewBook(Book **head, char *author, char *title, int year, int pages, float cost);
void printBooksByAuthorA(Book *head); // Нова функція

#endif
