#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


// Global variables 
const int stringSize = 1024;
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
void runLibrary(Library *library);
void loadInformation(Library *library);
void saveInformation(Library *library);

// Library manipulation funcitons
void displayBookCollection(Library *library);
void appendNewBook(Library *library, char bookName[], char authorName[], int year);
void removeBook(Library *library, char bookName[]);

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
    loadInformation(&myLibrary);

    runLibrary(&myLibrary);  // running the library 

    saveInformation(&myLibrary); // after library closes, function saves new information

    return 0; 
}

void runLibrary(Library *library)
{
    bool isOpen = true; 
    char choice; 

    while(isOpen)
    {   
        system("clear"); 
        printf("\n\n\t\tSee Book Collection--A\n\t\tBring new Book--B\n\t\tRemove book--C\n\t\tQuit--D\n\n");
        scanf(" %c", &choice);
        int c;
        while((c = getchar()) != '\n') {}  // clearing input buffer to avoid any issues with future fgets funct

        if(tolower(choice) == 'd') {isOpen = false;}
        else if(tolower(choice) == 'b') { addingBookMenu(library); }
        else if(tolower(choice) == 'a') { watchingBookCollectionMenu(library); }
        else if(tolower(choice) == 'c') { removingBookMenu(library); }
        else { printf("Enter valid input please!!!"); sleep(1); }
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

void removeBook(Library *library, char bookName[])
{
    Book currentBook;
    int bookIndex = -1; 
    for(int i = 0; i < library->bookQuantity; i++)
    {
        currentBook = library->bookCollection[i];

        if(strcmp(currentBook.name, bookName) == 0)
        {
            bookIndex = i; 
            break;
        }
    }

    if(bookIndex != -1)
    {
        for(int i = bookIndex; i < libraryCapacity - 1; i++)
        {
            library->bookCollection[i] = library->bookCollection[i+1];
        }
        library->bookQuantity -= 1; 
    }
    else if(bookIndex == -1)
    {
        printf("We could not find that book!!!");
        sleep(1);
    }
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
    else {saveInformation(library); exit(0);}

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
    else {saveInformation(library); exit(0);}

    sleep(1);
}

void removingBookMenu(Library *library)
{
    char bookName[stringSize]; 
    char choice; 
    printf("Enter book's name: ");
    fgets(bookName, stringSize, stdin);

    // clearing the trailling new line symbol
    int length = strlen(bookName);
    bookName[length-1] = '\0';

    removeBook(library, bookName);

    printf("In order to return to the main menu type -M-\n");
    printf("To quit the library type -Q-\n");

    scanf("%c", &choice);
    if(tolower(choice) == 'm') {}
    else {saveInformation(library); exit(0);}

    sleep(1);
}

void loadInformation(Library *library)
{
    FILE *file; 
    int bookQuantity = 0; 
    char currentLine[256]; 

    // Reading file with the number of books in the library 
    file = fopen("/Users/vadim/Documents/Programming/C Program/Library/Data/bookquantity.txt", "r");
    if(file == NULL)
    {
        perror("File was not found.\n");
        return; 
    }
    fscanf(file, "%d", &bookQuantity);
    library->bookQuantity = bookQuantity; // loading data into library variable
    fclose(file); // closing file stream

    // Reading books information from the saved file 
    file = fopen("/Users/vadim/Documents/Programming/C Program/Library/Data/info.txt", "r");
    if(file == NULL)
    {   
        perror("File was not found.\n");
        return;
    }
    // reading through the file 
    for(int i = 0; i < library->bookQuantity; i++)
    {
        int j = 0; 
        while(j < 4 && fgets(currentLine, sizeof(currentLine), file) != NULL)
        {
            // removing \n from the end of the current line 
            int length; 
            length = strlen(currentLine);
            currentLine[length - 1] = '\0';
            
            if(j == 0) 
            {
                strcpy(library->bookCollection[i].name, currentLine);
            }
            else if(j == 1) 
            {
                strcpy(library->bookCollection[i].authorName, currentLine);
            }
            else if(j == 2) 
            {
                library->bookCollection[i].year = atoi(currentLine); 
            }
            else {}
            j++; 
        }
    }
    fclose(file); // closing file stream
}

void saveInformation(Library *library)
{
    FILE *file_output; 
    // Saving the number of books stored in the library
    file_output = fopen("/Users/vadim/Documents/Programming/C Program/Library/Data/bookquantity.txt", "w");
    // Checking if the file is opened 
    if(file_output == NULL)
    {
        perror("Error opening numberBooks.txt");
        return; 
    }
    fprintf(file_output, "%d\n", library->bookQuantity); // Saving quantity of books 
    fclose(file_output); // closing file stream 
    
    // Saving books information 
    file_output = fopen("/Users/vadim/Documents/Programming/C Program/Library/Data/info.txt", "w");
    // Checking if the file is opened 
    if(file_output == NULL)
    {
        perror("Error opening info.txt");
        return; 
    }
    // Saving books to the file 
    for(int i = 0; i < library->bookQuantity; i++)
    {
        fprintf(file_output, "%s\n", library->bookCollection[i].name);
        fprintf(file_output, "%s\n", library->bookCollection[i].authorName);
        fprintf(file_output, "%d\n", library->bookCollection[i].year);
        fputs("\n", file_output);
    }
    fclose(file_output); // closing file stream 
}