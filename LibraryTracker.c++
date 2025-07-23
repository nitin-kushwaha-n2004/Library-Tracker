#include <iostream>
#include <string>
#include <limits>

class Book {
public:
    std::string title;
    std::string author;
    std::string isbn;
    bool isBorrowed;
    Book* next;

    Book(std::string t, std::string a, std::string i) : title(t), author(a), isbn(i), isBorrowed(false), next(nullptr) {}
};

class Library {
private:
    Book* head;

public:
    Library() : head(nullptr) {}

    ~Library() {
        Book* current = head;
        while (current != nullptr) {
            Book* nextBook = current->next;
            delete current;
            current = nextBook;
        }
    }

    void addBook(std::string title, std::string author, std::string isbn) {
        Book* newBook = new Book(title, author, isbn);
        if (head == nullptr) {
            head = newBook;
        } else {
            Book* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newBook;
        }
        std::cout << "Book added successfully.\n";
    }

    void displayAllBooks() {
        if (head == nullptr) {
            std::cout << "No books in the library.\n";
            return;
        }
        Book* current = head;
        int count = 1;
        while (current != nullptr) {
            std::cout << "\nBook " << count++ << ":\n";
            std::cout << "  Title: " << current->title << "\n";
            std::cout << "  Author: " << current->author << "\n";
            std::cout << "  ISBN: " << current->isbn << "\n";
            std::cout << "  Status: " << (current->isBorrowed ? "Borrowed" : "Available") << "\n";
            current = current->next;
        }
    }

    Book* searchBookByISBN(std::string isbn) {
        Book* current = head;
        while (current != nullptr) {
            if (current->isbn == isbn) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void borrowBook(std::string isbn) {
        Book* book = searchBookByISBN(isbn);
        if (book != nullptr) {
            if (!book->isBorrowed) {
                book->isBorrowed = true;
                std::cout << "Book '" << book->title << "' borrowed successfully.\n";
            } else {
                std::cout << "Book '" << book->title << "' is already borrowed.\n";
            }
        } else {
            std::cout << "Book with ISBN '" << isbn << "' not found.\n";
        }
    }

    void returnBook(std::string isbn) {
        Book* book = searchBookByISBN(isbn);
        if (book != nullptr) {
            if (book->isBorrowed) {
                book->isBorrowed = false;
                std::cout << "Book '" << book->title << "' returned successfully.\n";
            } else {
                std::cout << "Book '" << book->title << "' was not borrowed.\n";
            }
        } else {
            std::cout << "Book with ISBN '" << isbn << "' not found.\n";
        }
    }

    void deleteBook(std::string isbn) {
        if (head == nullptr) {
            std::cout << "Library is empty, cannot delete.\n";
            return;
        }

        if (head->isbn == isbn) {
            Book* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Book deleted successfully.\n";
            return;
        }

        Book* current = head;
        Book* prev = nullptr;
        while (current != nullptr && current->isbn != isbn) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "Book with ISBN '" << isbn << "' not found.\n";
            return;
        }

        prev->next = current->next;
        delete current;
        std::cout << "Book deleted successfully.\n";
    }
};

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printMenu() {
    std::cout << "\n--- Library Tracker ---\n";
    std::cout << "1. Add New Book\n";
    std::cout << "2. Display All Books\n";
    std::cout << "3. Search Book by ISBN\n";
    std::cout << "4. Borrow Book\n";
    std::cout << "5. Return Book\n";
    std::cout << "6. Delete Book\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Library myLibrary;
    int choice;
    std::string title, author, isbn;

    do {
        printMenu();
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1:
                std::cout << "Enter Title: ";
                std::getline(std::cin, title);
                std::cout << "Enter Author: ";
                std::getline(std::cin, author);
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                myLibrary.addBook(title, author, isbn);
                break;
            case 2:
                myLibrary.displayAllBooks();
                break;
            case 3:
                std::cout << "Enter ISBN to search: ";
                std::getline(std::cin, isbn);
                {
                    Book* foundBook = myLibrary.searchBookByISBN(isbn);
                    if (foundBook != nullptr) {
                        std::cout << "\nBook Found:\n";
                        std::cout << "  Title: " << foundBook->title << "\n";
                        std::cout << "  Author: " << foundBook->author << "\n";
                        std::cout << "  ISBN: " << foundBook->isbn << "\n";
                        std::cout << "  Status: " << (foundBook->isBorrowed ? "Borrowed" : "Available") << "\n";
                    } else {
                        std::cout << "Book with ISBN '" << isbn << "' not found.\n";
                    }
                }
                break;
            case 4:
                std::cout << "Enter ISBN of book to borrow: ";
                std::getline(std::cin, isbn);
                myLibrary.borrowBook(isbn);
                break;
            case 5:
                std::cout << "Enter ISBN of book to return: ";
                std::getline(std::cin, isbn);
                myLibrary.returnBook(isbn);
                break;
            case 6:
                std::cout << "Enter ISBN of book to delete: ";
                std::getline(std::cin, isbn);
                myLibrary.deleteBook(isbn);
                break;
            case 7:
                std::cout << "Exiting Library Tracker. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}

