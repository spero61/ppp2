// Add operators for the Book class.
// Have the == operator check whether the ISBN numbers are the same for two books.
// Have != also compare the ISBN numbers.
// Have a << print out the title, author, and ISBN on separate lines.

#include "std_lib_facilities.h"

class Invalid_isbn {
};

class Book {
   public:
    Book(string isbn, string title, string author, string copyright_date);

    bool check_out() { return is_checked_out = true; }
    bool check_in() { return is_checked_out = false; }

    string get_isbn() const { return isbn; }
    string get_title() const { return title; }
    string get_author() const { return author; }
    string get_copyright_date() const { return copyright_date; }
    bool get_is_checked_out() const { return is_checked_out; }

   private:
    string isbn;
    string title;
    string author;
    string copyright_date;
    bool is_checked_out;
};

// would be easy if we are allowed to use 'regex' instead
bool is_valid_isbn(const string& isbn) {
    int number_of_hyphen{0};

    bool is_previous_char_hyphen = false;

    int last_index = isbn.size() - 1;
    if (!isdigit(isbn[0])) {
        return false;
    } else if (isbn[last_index - 1] != '-') {
        return false;
    } else if (isdigit(isbn[last_index]) == 0 && isalpha(isbn[last_index]) == 0) {
        return false;
    }

    for (int i = 0; i < isbn.size(); ++i) {
        if (isbn[i] == '-') {
            if (is_previous_char_hyphen) {
                return false;
            }
            ++number_of_hyphen;
            is_previous_char_hyphen = true;
        } else if (i != last_index && !isdigit(isbn[i])) {
            return false;
        } else {
            is_previous_char_hyphen = false;
        }
    }

    if (number_of_hyphen != 3)
        return false;

    return true;
}

Book::Book(string isbn_arg, string title_arg, string author_arg, string copyright_date_arg)
    : isbn{isbn_arg}, title{title_arg}, author{author_arg}, copyright_date{copyright_date_arg}, is_checked_out{false} {
    if (!is_valid_isbn(isbn_arg))
        throw Invalid_isbn{};
}

bool operator==(const Book& book_a, const Book& book_b) {
    return (book_a.get_isbn() == book_b.get_isbn());
}

bool operator!=(const Book& book_a, const Book& book_b) {
    return !(book_a == book_b);
}

ostream& operator<<(ostream& os, const Book& book) {
    os << "Title: " << book.get_title() << '\n'
       << "Author: " << book.get_author() << '\n'
       << "ISBN: " << book.get_isbn() << '\n';

    return os;
}

int main() {
    try {
        Book ppp{"978-03219-92789-A", "Programming: Principles and Practice 2nd edition", "Bjarne Stroustrup", "2014"};
        Book tcpl{"978-03215-63842-T", "The C++ Programming Language", "Bjarne Stroustrup", "2013"};
        Book tcpl_copy{"978-03215-63842-T", "The C++ Programming Language", "Bjarne Stroustrup", "2013"};

        cout << ppp << '\n';
        cout << tcpl << '\n';

        cout << (ppp == tcpl) << '\n';        // false
        cout << (tcpl == tcpl_copy) << '\n';  // true;

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception\n";
        return 2;
    }
}