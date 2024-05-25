/*
 * Library Management System
 * 
 * Coded by Plan Ghimire
 * 
 * Description:
 * This program is a comprehensive Library Management System designed to help manage a library's
 * inventory and user transactions. It supports functionalities such as adding new books, deleting books,
 * searching for books, issuing books to users, and returning books. The system maintains records of all
 * transactions and ensures data consistency throughout various operations. It is an essential tool for
 * efficiently handling library operations and providing a seamless experience for librarians only.
 * 
 * Features:
 * - Add new books to the library database
 * - Delete books from the library database
 * - Search for books by title, author, or ISBN
 * - Issue books to library members
 * - Return books and update inventory
 * - Display the list of all available books
 * 
 * This program utilizes file handling to store and retrieve data, ensuring persistence across sessions.
 * The user interface is console-based, providing simple text-based interactions.
 * 
 * Version: 1.0
 * Date: May 2, 2024
 */

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define NO_OF_BOOKS 255
#define NO_OF_USERS 255

int n = NO_OF_BOOKS, un = NO_OF_USERS;
typedef struct
{
    char name[200];
    int quantity;
    int id;
    char author[200];

} book;

book books[NO_OF_BOOKS], emptyBook;

struct users
{
    char fname[200];
    char lname[200];
    int id, rc;
    char phoneNo[10];
    book rentedBook[10];

} users[255];

struct login
{
    char fname[30];
    char lname[30];
    char username[30];
    char password[20];
};

char buffer[100], line[100];
char temp[200];
char *token;

void buffi(int *);
void buffs(char[]);
void nbuffs(char[]);
void readBooks();
void readUsers();
void saveBooks();
void saveUsers();
void bookMenu();
void userMenu();
void rentBooks();
void modifyBooks();
const char *simplify(char[]);
void displayBooks(int);
void searchBooks();
void registration()
{
    FILE *log;
    struct login l;

    log = fopen("login.txt", "w");

    printf("\nRegister yourself into the system.\n\n");
    printf("Enter First Name: ");
    buffs(l.fname);
    printf("Enter Surname: ");
    buffs(l.lname);

    printf("\nNow choose a username and password for system login:\n");
    printf("Username (max 30 characters): ");
    buffs(l.username);
    printf("Password (at least 8 characters): ");
    buffs(l.password);

    fprintf(log, "%s %s %s %s", l.fname, l.lname, l.username, l.password);
    fclose(log);

    printf("\nRegistration Successful! Welcome, %s!\n", l.fname);
}

void logIn()
{
    FILE *log;
    struct login l;
    char username[30], password[20], info[250];

    log = fopen("login.txt", "r");

    printf("\nPlease Enter your login credentials below\n");
    while (1)
    {
        printf("Username: ");
        fgets(username, 30, stdin);
        username[strcspn(username, "\n")] = '\0';
        printf("Password: ");
        fgets(password, 20, stdin);
        password[strcspn(password, "\n")] = '\0';
        fgets(info, 250, log);
        sscanf(info, "%s%s%s%s", l.fname, l.lname, l.username, l.password);
        if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0)
        {
            printf("\nSuccessfully Logged In\n");
            break;
        }
        else
        {
            printf("\nIncorrect Login Details. Please enter the correct credentials.\n");
        }
    }

    fclose(log);
}
void displayUsers();

int i, c = 0, uc = 0, d, flag = 1;
FILE *lp, *up;

int main()
{
    int option;

    printf("Press '1' to Register\nPress '2' to Login\n\n");
    buffi(&option);

    if (option == 1)
    {
        registration();
    }
    else if (option == 2)
    {
        logIn();
    }

    emptyBook = (book){"", 0, -1, ""};
    int r;
    readBooks();
    readUsers();
    while (flag)
    {
        printf("Enter 1 for Book Menu, 2 for User Menu, 3 to exit: ");
        buffi(&r);
        switch (r)
        {
        case 1:
            bookMenu();
            break;
        case 2:
            userMenu();
            break;
        case 3:
            flag = 0;
            break;
        default:
            printf("Invalid Input");
        }
    }
}

void bookMenu()
{
    while (1)
    {
        char keyword[200];
        int check = 0, i, id;
        system("CLS");
        fflush(stdin);
        buffer[strspn(buffer, "\n\r")] = '\0';
        printf("\nEnter \n>1 to enter book \n>2 to modify book\n>3 to delete book\n>4 to search book by name\n>5 to search book by id\n>6 to display all books\n>7 to manage rented books\n>8 to save\n>9 to save and exit\n>10 to return to previous menu\n ");
        buffi(&i);
        switch (i)
        {
        case 1:
            printf("\nEnter the name of book ");
            buffs(books[c].name);
            printf("\nEnter the author of book ");
            buffs(books[c].author);
            printf("\nEnter the quantity of books ");
            buffi(&books[c].quantity);
            printf("\nEnter the id of books ");
            while (check == 0)
            {
                buffi(&books[c].id);
                for (i = 0; i < n; i++)
                {
                    if ((books[i].id == books[c].id) && i != c)
                    {
                        printf("\nId already exists. Enter again. ");
                        check = 0;
                        break;
                    }
                    else
                    {
                        check = 1;
                    }
                }
            }

            c++;
            break;
        case 2:
            modifyBooks();
            break;

        case 3:
            displayBooks(-1);
            printf("\nEnter the number of book ");
            buffi(&d);
            for (i = 0; i < n; i++)
            {
                if (i >= d - 1)
                {
                    books[i] = books[i + 1];
                }
            }
            c--;
            break;
        case 4:
            printf("Enter book name ");
            buffs(keyword);
            searchBooks(keyword);
            break;
        case 5:
            printf("Enter ID of book ");
            buffi(&id);
            displayBooks(id);
            break;
        case 6:
            displayBooks(-1);
            break;

        case 8:
            saveBooks();
            saveUsers();
            printf("\nok");
            break;

        case 9:
            saveBooks();
            saveUsers();
            flag = 0;
            return;
            break;
        case 10:
            return;
        case 7:
            rentBooks();
            break;
        default:
            printf("Enter a valid case ");
        }
        Sleep(4000);
    }
}

void modifyBooks()
{
    int _id;
    printf("Enter the id of book to modify ");
    buffi(&_id);
    for (int i = 0; i < c; i++)
    {
        if (books[i].id == _id)
        {
            int flag, changedVar_i;
            char changedVar_s[200];
            printf("Enter what to change?\n> 1 for Name\n> 2 for Author\n> 3 for Quantity \n>4 for id");
            buffi(&flag);
            switch (flag)
            {
            case 1:
                printf("Enter the new name ");
                buffs(changedVar_s);
                strcpy(books[i].name, changedVar_s);
                break;
            case 2:
                printf("Enter the new Author ");
                buffs(changedVar_s);
                strcpy(books[i].author, changedVar_s);
                break;
            case 3:
                printf("Enter the new Quantity ");
                buffi(&changedVar_i);
                books[i].quantity = changedVar_i;
                break;
            case 4:
                printf("Enter the new ID ");
                buffi(&changedVar_i);
                books[i].id = changedVar_i;
                break;
            default:
                printf("Input a valid number ");
            }
        }
    }
    if (i == n)
    {
        printf("Invalid ID");
    }
}

void readBooks()
{

    for (i = 0; i < n; i++)
    {
        books[i] = emptyBook;
    }

    if ((lp = fopen("library.txt", "r")) != NULL)
    {
        for (i = 0; i < n; i++)
        {
            if (fgets(line, sizeof line, lp) != NULL)
            {
                sscanf(line, " %[^;];%[^;];%d;%d\n", books[i].name, books[i].author, &books[i].quantity, &books[i].id);
                strcpy(line, "");
                c++;
            }
            fflush(stdin);
        }
        fclose(lp);
    }
    for (i = c; i < n; i++)
    {
        books[i] = emptyBook;
    }
}

void readUsers()
{
    int temp_id;
    for (i = 0; i < 255; i++)
    {
        strcpy(users[i].fname, "");
        users[i].id = 0;
        strcpy(users[i].phoneNo, "");
        strcpy(users[i].lname, "");
        for (int j = 0; j < 10; j++)
        {
            users[i].rentedBook[j] = emptyBook;
        }
        users[i].rc = 0;
    }

    if ((up = fopen("users.txt", "r")) != NULL)
    {
        for (i = 0; i < n; i++)
        {
            if (fgets(line, sizeof line, up) != NULL)
            {
                sscanf(line, " %[^;];%[^;];%d;%[^;];", users[i].fname, users[i].lname, &users[i].id, users[i].phoneNo);
                strcpy(line, "");
                if (fgets(line, sizeof line, up) != NULL)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        sscanf(line, "%d", &temp_id);
                        for (int k = 0; k < c; k++)
                        {
                            if (books[k].id == temp_id)
                            {
                                users[i].rentedBook[j] = books[k];
                                users[i].rc++;
                            }
                        }
                        int l = strcspn(line, " ");
                        for (int k = 0; k <= 100; k++)
                        {
                            line[k] = line[k + l + 1];
                        }
                    }
                }
                strcpy(line, "");
                uc++;
            }
            fflush(stdin);
        }
        fclose(up);
    }

    for (i = uc; i < 255; i++)
    {
        strcpy(users[i].fname, "");
        users[i].id = 0;
        strcpy(users[i].phoneNo, "");
        strcpy(users[i].lname, "");
        for (int j = users[i].rc; j < 10; j++)
        {
            users[i].rentedBook[j] = emptyBook;
        }
    }
}

void searchBooks(char word[200])
{
    char keyword[200], temp[200];
    int i;
    strcpy(keyword, simplify(word));

    {for (i = 0; i < c; i++)
    {
        strcpy(temp, simplify(books[i].name));
        strcpy(temp, simplify(strcat(temp, books[i].author)));
        if (strstr(temp, keyword) != NULL)
        {
            displayBooks(books[i].id);
        }
    }}
}

const char *simplify(char word[200])
{
    strcpy(temp, word);
    for (i = 0; i < strlen(temp); i++)
    {
        temp[i] = tolower(temp[i]);
    }
    int l=500;
    for (i = 0; i < strlen(temp) - 1; i++)
    {
        for (int j = i+1; j < strlen(temp); j++)
        {
            if (temp[i] == ' ')
            {
                l = i;
            }
            if(i>=l && j == i+1){
                temp[i]=temp[j];
            }
            if(i==strlen(temp)-2 && i>l){
                temp[i+1] = '\0';
            }
        }
    }
    return temp;
}

void userMenu()
{
    int r;
    while (1)
    {
        int check = 1;
        printf("\nEnter 1 to add user, 2 to delete user, 3 to display users, 4 to save and exit, 5 to return to previous menu ");
        buffi(&r);
        switch (r)
        {
        case 1:
            while (1)
            {
                check = 1;
                printf("\nEnter the first name of user ");
                nbuffs(users[uc].fname);
                printf("\nEnter the last name of user ");
                nbuffs(users[uc].lname);
                printf("\nEnter the id ");
                buffi(&users[uc].id);
                for (i = 0; i < un; i++)
                {
                    if ((users[i].id == users[uc].id) && i != uc)
                    {
                        printf("\nId already exists. Enter again. ");
                        printf("%d", users[i].id);
                        check = 0;
                        break;
                    }
                }
                if (check == 0)
                {
                    continue;
                }
                for (i = 0; i < un; i++)
                {
                    if ((users[i].id == users[uc].id) && i != uc)
                    {
                        printf("\nId already exists. Enter again. ");
                        printf("%d", users[i].id);
                        check = 0;
                        break;
                    }
                }
                printf("\nEnter the Phone Number ");
                nbuffs(users[uc].phoneNo);
                break;
            }
            uc++;
            break;
        case 2:
            check = -1;
            displayUsers();
            printf("\nEnter the id of user ");
            buffi(&d);
            for (i = 0; i < un; i++)
            {
                if (users[i].id == d)
                {
                    check = i;
                }
                if (i >= check && check != -1)
                {
                    users[i] = users[i + 1];
                }
            }
            if (check >= 0)
            {
                uc--;
            }
            else
            {
                printf("\nNo id found");
            }
            break;
        case 3:
            displayUsers();
            break;

        case 4:
            saveUsers();
            saveBooks();
            flag = 0;
            return;
            break;
        case 5:
            return;

        default:
            printf("Enter a valid number");
        }
    }
}

void saveBooks()
{
    lp = fopen("library.txt", "w");
    for (i = 0; i < n; i++)
    {
        if (strcmp(books[i].name, ""))
        {
            fprintf(lp, "%s;%s;%d;%d\n", books[i].name, books[i].author, books[i].quantity, books[i].id);
        }
    }
    fclose(lp);
}

void saveUsers()
{
    up = fopen("users.txt", "w");
    for (i = 0; i < un; i++)
    {
        if (strcmp(users[i].fname, ""))
        {
            fprintf(up, "%s;%s;%d;%s;\n", users[i].fname, users[i].lname, users[i].id, users[i].phoneNo);
            if (strcmp(users[i].fname, ""))
            {
                for (int j = 0; j < 10; j++)
                {
                    fprintf(up, "%d ", users[i].rentedBook[j].id);
                }
                fprintf(up, "\n");
            }
        }
    }
    fclose(up);
}

void displayBooks(int flag)
{
    for (i = 0; i < n; i++)
    {
        if (strcmp(books[i].name, ""))
        {
            if (flag == -1)
            {
                printf("\n%d. %s by %s. Quantity in library: %d", i + 1, books[i].name, books[i].author, books[i].quantity);
            }
            else
            {
                if (books[i].id == flag)
                {
                    printf("%s by %s. Quantity in library: %d ID: %d\n", books[i].name, books[i].author, books[i].quantity, books[i].id);
                }
            }
        }
    }
}

void rentBooks()
{
    char _book[200];
    int id, bid, rc = 0;
    book rentedBook;
    printf("Enter the id of the user who wants to rent the book: ");
    buffi(&id);
    printf("Enter book's name: ");
    buffs(_book);
    searchBooks(_book);
    printf("\nSelect a book using the book id: ");
    buffi(&bid);
    for (int i = 0; i < c; i++)
    {
        if (bid == books[i].id)
        {
            rentedBook = books[i];
        }
    }
    for (int i = 0; i < uc; i++)
    {
        if (id == users[i].id)
        {
            printf("Renting %s for the user %s... ", rentedBook.name, users[i].fname);
            users[i].rentedBook[users[i].rc] = rentedBook;
            users[i].rc++;
        }
    }
    for (int i = 0; i < c; i++)
    {
        if (bid == books[i].id)
        {
            books[i].quantity--;
        }
    }
}

void displayUsers()
{

    for (int i = 0; i < uc; i++)
    {
        printf("\n%d. Name: %s %s ID: %d Phone No.: %s ", i + 1, users[i].fname, users[i].lname, users[i].id, users[i].phoneNo);
        printf("\nBooks rented by the user: \n");
        for (int j = 0; j < 10; j++)
        {
            if (users[i].rentedBook[j].id != -1)
            {
                displayBooks(users[i].rentedBook[j].id);
            }
        }
    }
}

void buffi(int *i)
{
    fflush(stdin);
    strcpy(buffer, "");

    fgets(buffer, sizeof buffer, stdin);
    sscanf(buffer, "%d", i);
}

void buffs(char c[100])
{
    fgets(c, 100, stdin);
    // removes newline when being stored
    c[strcspn(c, "\n\r")] = '\0';
}
void nbuffs(char c[100])
{
    char buff[100];
    fgets(buff, 100, stdin);
    sscanf(buff, "%s", c);
}
