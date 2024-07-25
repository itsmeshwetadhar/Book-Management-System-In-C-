#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

class Book {
public:
    std::string title;
    std::string author;
    double price;
    int quantity;

    Book(const std::string& title, const std::string& author, double price, int quantity)
        : title(title), author(author), price(price), quantity(quantity) {}

    void display() const {
        std::cout << std::setw(20) << std::left << title
                  << std::setw(20) << std::left << author
                  << std::setw(10) << std::left << price
                  << std::setw(5) << std::left << quantity << std::endl;
    }
};

class Bookshop {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        std::cout << "Book added successfully!\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            std::cout << "No books available.\n";
            return;
        }

        std::cout << std::setw(20) << std::left << "Title"
                  << std::setw(20) << std::left << "Author"
                  << std::setw(10) << std::left << "Price"
                  << std::setw(5) << std::left << "Quantity" << std::endl;
        std::cout << "---------------------------------------------\n";

        for (const auto& book : books) {
            book.display();
        }
    }

    void searchBook(const std::string& title) const {
        auto it = std::find_if(books.begin(), books.end(),
                               [&title](const Book& book) { return book.title == title; });

        if (it != books.end()) {
            std::cout << "Book found!\n";
            it->display();
        } else {
            std::cout << "Book not found.\n";
        }
    }
};

int main() {
    Bookshop bookshop;

    char choice;
    do {
        std::cout << "1. Add Book\n";
        std::cout << "2. Display Books\n";
        std::cout << "3. Search Book\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1': {
                std::string title, author;
                double price;
                int quantity;

                std::cout << "Enter book title: ";
                std::cin.ignore();
                std::getline(std::cin, title);

                std::cout << "Enter author name: ";
                std::getline(std::cin, author);

                std::cout << "Enter price: ";
                std::cin >> price;

                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                Book newBook(title, author, price, quantity);
                bookshop.addBook(newBook);
                break;
            }
            case '2':
                bookshop.displayBooks();
                break;
            case '3': {
                std::string searchTitle;
                std::cout << "Enter book title to search: ";
                std::cin.ignore();
                std::getline(std::cin, searchTitle);
                bookshop.searchBook(searchTitle);
                break;
            }
            case '4':
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '4');

    return 0;
}
