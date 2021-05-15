// This exercise and the next few require you to design and implement a Book class,
// such as you can imagine as part of software for a library.
// Class Book should have members for the ISBN, title, author, and copyright date.
// Also store data on whether or not the book is checked out.

// Create functions for returning those data values.
// Create functions for checking a book in and out.
// Do simple validation of data entered into a Book;
// for example, accept ISBNs only of the form n-n-n-x where n is an integer and x is a digit or a letter.
// Store an ISBN as a string.

// Comment:
// I deliberately not use regular expression for validation of ISBN
// as the regex is going to be introduced in chapter 23: Text Manipulation.

#include "std_lib_facilities.h"

class Invalid_isbn {};

class Book {
   public:
    Book(string isbn, string title, string author, string copyright_date);

    bool check_out() { return is_checked_out = true; }
    bool check_in() { return is_checked_out = false; }

    string get_isbn() { return isbn; }
    string get_title() { return title; }
    string get_author() { return author; }
    string get_copyright_date() { return copyright_date; }
    bool get_is_checked_out() { return is_checked_out; }

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

int main() {
    try {
        string test1 = "978-03219-92789-A";  // true: 1
        string test2 = "978-03215-63842-T";  // true: 1
        string test3 = "08-7201-4514--S";    // false: 0
        string test4 = "08-7201-4514-S";     // true: 1
        string test5 = "-4989-9977-55442";   // false: 0
        string test6 = "4989-9977-5544-5G";  // false: 0
        string test7 = "2021-0514-1212-0";   // true: 1
        cout << "test1: " << is_valid_isbn(test1) << '\n';
        cout << "test2: " << is_valid_isbn(test2) << '\n';
        cout << "test3: " << is_valid_isbn(test3) << '\n';
        cout << "test4: " << is_valid_isbn(test4) << '\n';
        cout << "test5: " << is_valid_isbn(test5) << '\n';
        cout << "test6: " << is_valid_isbn(test6) << '\n';
        cout << "test7: " << is_valid_isbn(test7) << '\n';
        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception\n";
        return 2;
    }
}