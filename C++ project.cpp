#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Book {
public:
    string title;
    string author;
    bool available;
    time_t dueDate;

    Book(string title, string author) {
        this->title = title;
        this->author = author;
        this->available = true;
        this->dueDate = 0;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(string title, string author) {
        books.push_back(Book(title, author));
        cout << "The book '" << title << "' by " << author << " has been added to the library." << endl;
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books in the library." << endl;
        } else {
            cout << "Books in the library:" << endl;
            for (size_t i = 0; i < books.size(); ++i) {
                cout << "- " << books[i].title << " by " << books[i].author;
                if (books[i].available) {
                    cout << " (Available)";
                } else {
                    cout << " (Not Available)";
                }
                if (!books[i].available && books[i].dueDate > 0) {
                    tm* timeInfo = localtime(&books[i].dueDate);
                    char buffer[80];
                    strftime(buffer, sizeof(buffer), " (Due on %d-%m-%Y)", timeInfo);
                    cout << buffer;
                }
                cout << endl;
            }
        }
    }

    Book* findBook(string title) {
        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].title == title) {
                return &books[i];
            }
        }
        return NULL;
    }

    void reserveBook(string title) {
        Book* book = findBook(title);
        if (book != NULL) {
            if (book->available) {
                book->available = false;
                time_t now = time(NULL);
                book->dueDate = now + 7 * 24 * 60 * 60;  // Due date set to 7 days from now
                cout << "You have successfully reserved the book '" << book->title << "'."
                     << " Please return it by " << ctime(&book->dueDate) << endl;
            } else {
                cout << "Sorry, the book '" << book->title << "' is not available for reservation." << endl;
            }
        } else {
            cout << "Sorry, the book '" << title << "' is not in the library." << endl;
        }
    }

    void borrowBook(string title) {
        Book* book = findBook(title);
        if (book != NULL) {
            if (book->available) {
                book->available = false;
                time_t now = time(NULL);
                book->dueDate = now + 14 * 24 * 60 * 60;  // Due date set to 14 days from now
                cout << "You have successfully borrowed the book '" << book->title << "'."
                     << " Please return it by " << ctime(&book->dueDate) << endl;
            } else {
                cout << "Sorry, the book '" << book->title << "' is not available for borrowing." << endl;
            }
        } else {
            cout << "Sorry, the book '" << title << "' is not in the library." << endl;
        }
    }

    void renewBook(string title) {
        Book* book = findBook(title);
        if (book != NULL) {
            if (!book->available) {
                time_t now = time(NULL);
                if (book->dueDate > now) {
                    book->dueDate += 7 * 24 * 60 * 60;  // Extend due date by 7 days
                    cout << "You have successfully renewed the book '" << book->title << "'."
                         << " The new due date is " << ctime(&book->dueDate) << endl;
                } else {
                    cout << "Sorry, the book '" << book->title << "' has already passed its due date."
                         << " Please return it before renewing." << endl;
                }
            } else {
                cout << "Sorry, the book '" << book->title << "' is not available for renewal." << endl;
            }
        } else {
            cout << "Sorry, the book '" << title << "' is not in the library." << endl;
        }
    }

    void lendBook(string title) {
        Book* book = findBook(title);
        if (book != NULL) {
            if (!book->available) {
                book->available = true;
                book->dueDate = 0;
                cout << "You have successfully marked the book '" << book->title << "' as returned." << endl;
            } else {
                cout << "The book '" << book->title << "' is already available in the library." << endl;
            }
        } else {
            cout << "Sorry, the book '" << title << "' is not in the library." << endl;
        }
    }
};

int main() {
    Library library;

    // Add some books to the library
    library.addBook("The Great Gatsby", "F. Scott Fitzgerald");
    library.addBook("To Kill a Mockingbird", "Harper Lee");
    library.addBook("1984", "George Orwell");

    // Display all books in the library
    library.displayBooks();

    // Allow the user to perform library operations
    while (true) {
        cout << "\nWhat would you like to do?" << endl;
        cout << "1. Reserve a book" << endl;
        cout << "2. Borrow a book" << endl;
        cout << "3. Renew a book" << endl;
        cout << "4. Lend a book" << endl;
        cout << "5. Display all books" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter the title of the book you want to reserve: ";
            string title;
            cin.ignore();
            getline(cin, title);
            library.reserveBook(title);
        } else if (choice == 2) {
            cout << "Enter the title of the book you want to borrow: ";
            string title;
            cin.ignore();
            getline(cin, title);
            library.borrowBook(title);
        } else if (choice == 3) {
            cout << "Enter the title of the book you want to renew: ";
            string title;
            cin.ignore();
            getline(cin, title);
            library.renewBook(title);
        } else if (choice == 4) {
            cout << "Enter the title of the book you want to lend: ";
            string title;
            cin.ignore();
            getline(cin, title);
            library.lendBook(title);
        } else if (choice == 5) {
            library.displayBooks();
        } else if (choice == 6) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

