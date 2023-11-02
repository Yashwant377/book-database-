#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

class Book {
public:
    std::string title;
    std::string author;
    std::string ISBN;
    bool isAvailable;

    Book(const std::string& title, const std::string& author, const std::string& ISBN)
        : title(title), author(author), ISBN(ISBN), isAvailable(true) {}
};

class Borrower {
public:
    std::string name;
    std::vector<std::string> borrowedBooks;

    Borrower(const std::string& name) : name(name) {}
};

class Library {
private:
    std::vector<Book> bookDatabase;
    std::vector<Borrower> borrowers;

public:
    void addBook(const std::string& title, const std::string& author, const std::string& ISBN) {
        bookDatabase.push_back(Book(title, author, ISBN));
    }

    void addBorrower(const std::string& name) {
        borrowers.push_back(Borrower(name));
    }

    void displayBorrowedBooks(const std::string& borrowerName) {
        for (auto& borrower : borrowers) {
            if (borrower.name == borrowerName) {
                std::cout << "Books borrowed by " << borrowerName << ":\n";
                for (const std::string& title : borrower.borrowedBooks) {
                    std::cout << title << std::endl;
                }
                return;
            }
        }
        std::cout << "Borrower not found.\n";
    }

    void searchBook(const std::string& query) {
        std::cout << "Search Results for " << query << ":\n";
        for (auto& book : bookDatabase) {
            if (book.title == query || book.author == query || book.ISBN == query) {
                std::cout << book.title << " | " << book.author << " | " << book.ISBN << " | " << (book.isAvailable ? "Available" : "Not Available") << "\n";
            }
        }
    }

    void checkOutBook(const std::string& title, const std::string& borrowerName) {
        for (auto& book : bookDatabase) {
            if (book.title == title && book.isAvailable) {
                book.isAvailable = false;
                std::cout << "Book checked out successfully.\n";
                addBorrowerBook(borrowerName, title);
                return;
            }
        }
        std::cout << "Book not found or not available.\n";
    }

    void returnBook(const std::string& title, const std::string& borrowerName) {
        for (auto& book : bookDatabase) {
            if (book.title == title) {
                book.isAvailable = true;
                removeBorrowerBook(borrowerName, title);
                std::cout << "Book returned successfully.\n";
                return;
            }
        }
        std::cout << "Book not found.\n";
    }

    void addBorrowerBook(const std::string& borrowerName, const std::string& title) {
        for (auto& borrower : borrowers) {
            if (borrower.name == borrowerName) {
                borrower.borrowedBooks.push_back(title);
                return;
            }
        }
        std::cout << "Borrower not found.\n";
    }

    void removeBorrowerBook(const std::string& borrowerName, const std::string& title) {
        for (auto& borrower : borrowers) {
            if (borrower.name == borrowerName) {
                auto it = std::find(borrower.borrowedBooks.begin(), borrower.borrowedBooks.end(), title);
                if (it != borrower.borrowedBooks.end()) {
                    borrower.borrowedBooks.erase(it);
                }
                return;
            }
        }
        std::cout << "Borrower not found.\n";
    }
};

int main() {
    Library library;

    library.addBook("Book 1", "Author 1", "ISBN-1");
    library.addBook("Book 2", "Author 2", "ISBN-2");
    library.addBorrower("Borrower A");
    library.addBorrower("Borrower B");

    library.checkOutBook("Book 1", "Borrower A");
    library.checkOutBook("Book 2", "Borrower B");

    library.displayBorrowedBooks("Borrower A");
    library.displayBorrowedBooks("Borrower B");

    library.returnBook("Book 1", "Borrower A");
    library.returnBook("Book 2", "Borrower B");

    library.displayBorrowedBooks("Borrower A");
    library.displayBorrowedBooks("Borrower B");

    return 0;
}
