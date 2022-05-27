#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 * Library Managment System *

 - Make a data for book         ^^^
 - Make a series of books
 - Print the list of books      ^^^
 - Store it ( in a file )
 - Read the data from the file
 - Make a remove function       ^^^
 - Check if you add a book that already  exist
 - Make a search:
    - by name
    - by autor
    - by year (Maybe)
    - by genre
    - by favorite
    - etc.
 - Try to make a UI?
                            */


typedef struct TBook
{
    char name[30];
    char autor[20];
    int year;
    char genre[20];
} Book;

// Function declaration
Book mkBook();
void insertBook(Book** books, int *size);
void removeBook(Book books[], int *size);
void printBooks(Book books[], int size);
void Writing(Book* books, int count);

#define NL printf("\n")

int main(void)
{
    Book *pB = NULL;
    int size = 0;
    char choice[10];

    while(1)
    {
       printf("Choose to Insert, Remove, Search, Print, Write or END: ");
       scanf(" %[^\n]s", &choice);

       if(!strcmp(choice, "END")) break;

       if(!strcmp(choice, "Insert")) insertBook(&pB, &size);
       if(!strcmp(choice, "Remove")) removeBook(pB, &size);
       if(!strcmp(choice, "Print")) printBooks(pB, size);
       if(!strcmp(choice, "Write")) Writing(pB, size);
    }

    free(pB);
    return 0;
}

// Insert the book to the list
void insertBook(Book** books, int *size)
{
    int i;

    // Choose what book to insert
    Book book = mkBook();
    /*
    for(i=0; i<*size; i++)
        if(!strcmp(book.name,books[i]->name)) return; */

    // Inserting the book
    //if(!(*size)) *books = (Book *)malloc(++(*size) * sizeof(Book));
     *books = (Book *)realloc(*books, ++(*size) * sizeof(Book));
    if(*books == NULL) exit(1);

   (*books)[*size - 1] = book;
}

// data of a book
Book mkBook()
{
    Book book;

    printf("name: ");
    scanf(" %[^\n]s", &book.name);
    printf("autor: ");
    scanf(" %[^\n]s", &book.autor);
    //printf("genre: ");
    //scanf(" %[^\n]s", &book.genre);
    printf("year: ");
    scanf("%d", &book.year);
    NL;

    return book;
}

// remove a book by name
void removeBook(Book books[], int *size)
{
    char name[30];
    printf("Write the name of the book you want to remove: ");
    scanf(" %[^\n]s", &name);
    NL;

    int i,j;
    for(i=0; i<*size; i++)
        if(!strcmp(books[i].name, name))
        {
           for(j=i+1; j<*size; j++)
                books[j-1] = books[j];
            // make if size comes to 0
            if(!(*size - 1)) {--(*size); return books;}
           books = (Book *)realloc(books, --(*size) * sizeof(Book));
           if(books == NULL) exit(1);
           return;
        }
}

// print the list of books
void printBooks(Book books[], int size)
{
    int i;

    for(i=0; i<size; i++)
    {
        printf("\nname: %s\n", books[i].name);
        printf("autor: %s\n", books[i].autor);
        // printf("genre: %s\n", books[i].genre);
        printf("year: %d\n\n", books[i].year);
    }
}

// write to txt file
void Writing(Book * books, int count)
{
    FILE * fp = fopen("data.bin", "wb");
    if(fp == NULL) exit(1);

    int i;
    int lenName, lenAutor;
    //int lenGenre;
    for(i=0; i<count; i++)
    {
        lenName = strlen(books[i].name);
        lenAutor= strlen(books[i].autor);

        if(fwrite(books[i].name, sizeof(char) * lenName, 1, fp) != 1) exit(1);
        if(fwrite(books[i].autor, sizeof(char) * lenAutor, 1, fp) != 1) exit(1);
        if(fwrite(books[i].year, sizeof(int), 1, fp) != 1) exit(1);
        //if(fwrite(books[i].genre, sizeof(int) * lenGenre, 1, fp) != 1) exit(1);
    }

    fclose(fp);
}
