#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


// Global variables 
const int stringSize = 20;
const int libraryCapacity = 100; 

typedef struct 
{
    char name[stringSize];
    char authorName[stringSize];
    int year;
} Book; 

typedef struct 
{
    Book bookCollection[libraryCapacity]; 
    int bookQuantity; 
} Library;

// Fundamental functions
void runLibrary(Library *Library);
void loadInformation();
void saveInformation();

// Library manipulation funcitons
void displayBookCollection(Library *library);
void appendNewBook(Library *library, char bookName[], char authorName[], int year);
void removingBook(Library *library, char bookName[]);

// Additional functions
void addingBookMenu(Library *library);
void watchingBookCollectionMenu(Library *library);
void removingBookMenu(Library *library); 

int main()
{
    //Declare and Initialize library
    Library myLibrary;
    myLibrary.bookQuantity = 0;

    // load information from the text file 
    loadInformation();

    runLibrary(&myLibrary);  // running the library 

    saveInformation(); // after library closes, function saves new information

    return 0; 
}

void runLibrary(Library *library)
{
    bool isOpen = true; 
    char choice; 

    while(isOpen)
    {   
        system("clear"); 
        printf("\n\n\t\tSee Book Collection--A\n\t\tBring new Book--B\n\t\tQuit--C\n\n");
        scanf(" %c", &choice);
        int c;
        while((c = getchar()) != '\n') {}  // clearing input buffer to avoid any issues with future fgets funct

        if(tolower(choice) == 'c') {isOpen = false;}
        else if(tolower(choice) == 'b')
        {
            addingBookMenu(library);
        }
        else if(tolower(choice) == 'a')
        {
            watchingBookCollectionMenu(library);
        }
        else {printf("Enter valid input please!!!");}
    }
    printf("\t\tHave a good day!!!");
}

void displayBookCollection(Library *library)
{
    for(int i = 0; i<library->bookQuantity; i++)
    {
        Book currentBook = library->bookCollection[i];
        //system("clear");
        printf( "%d)Book Name: %s. Author Name: %s. Year: %d\n", i+1, currentBook.name, currentBook.authorName, currentBook.year );
    }
}

void appendNewBook(Library *library, char bookName[], char authorName[], int year)
{
    Book newBook;
    strcpy(newBook.name, bookName);
    strcpy(newBook.authorName, authorName);
    newBook.year = year; 

    library->bookCollection[library->bookQuantity] = newBook;
    library->bookQuantity += 1;
}

void removingBook(Library *library, char bookName[])
{

}

void addingBookMenu(Library *library)
{
    char name[stringSize];
    char authorName[stringSize];
    int year;

    char choice; 

    printf("Enter book name: ");
    fgets(name, stringSize, stdin);

    // clearing trailing new line 
    int length = strlen(name);
    name[length-1] = '\0';

    printf("Enter author's name: ");
    fgets(authorName, stringSize, stdin);

    // clearing trailing new line 
    length = strlen(authorName);
    authorName[length-1] = '\0';

    printf("Enter publication year of the book: ");
    scanf("%d", &year);

    appendNewBook(library, name, authorName, year); 

    printf("Your book has been successfuly uploaded to the library!!!\n");
    printf("In order to return to the main menu type -M-\n");
    printf("To quit the library type -Q-\n");

    // Clearing input buffer 
    int c;
    while((c = getchar()) != '\n') {}

    // getting input
    scanf("%c", &choice);
    if(tolower(choice) == 'm') {}
    else {exit(0);}

    sleep(1); // make transition between menues smooth 
}

void watchingBookCollectionMenu(Library *library)
{
    char choice; 

    printf("Here is our book collection: \n");
    displayBookCollection(library);

    printf("In order to return to the main menu type -M-\n");
    printf("To quit the library type -Q-\n");

    scanf("%c", &choice);
    if(tolower(choice) == 'm') {}
    else {exit(0);}

    sleep(1);
}

void removingBookMenu(Library *library)
{

}

void loadInformation()
{

}

void saveInformation()
{

}
