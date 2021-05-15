// Create an enumerated type for the Book class called Genre.
// Have the types be fiction, nonfiction, periodical, biography, and children.
// Give each book a Genre and make appropriate changes to the Book constructor and member functions.

#include "std_lib_facilities.h"

class Invalid_isbn {
};

// If we don't initialize the first enumerator, the count starts with 0
enum class Genre {
    fiction,
    nonfiction,
    periodical,
    biography,
    children
};

class Book {
   public:
    Book(string isbn, string title, string author, string copyright_date, Genre genre);

    bool check_out() { return is_checked_out = true; }
    bool check_in() { return is_checked_out = false; }

    string get_isbn() const { return isbn; }
    string get_title() const { return title; }
    string get_author() const { return author; }
    string get_copyright_date() const { return copyright_date; }
    Genre get_genre() const { return genre; }
    bool get_is_checked_out() const { return is_checked_out; }

   private:
    string isbn;
    string title;
    string author;
    string copyright_date;
    Genre genre;

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

Book::Book(string isbn_arg, string title_arg, string author_arg, string copyright_date_arg, Genre genre_arg)
    : isbn{isbn_arg}, title{title_arg}, author{author_arg}, copyright_date{copyright_date_arg}, genre{genre_arg}, is_checked_out{false} {
    if (!is_valid_isbn(isbn_arg))
        throw Invalid_isbn{};
}

bool operator==(const Book& book_a, const Book& book_b) {
    return (book_a.get_isbn() == book_b.get_isbn());
}

bool operator!=(const Book& book_a, const Book& book_b) {
    return !(book_a == book_b);
}

string genre_tostring(const Genre& genre) {
    switch (genre) {
        case Genre::fiction:
            return "Fiction";
        case Genre::nonfiction:
            return "Non fiction";
        case Genre::periodical:
            return "Periodical";
        case Genre::biography:
            return "Biography";
        case Genre::children:
            return "Children";
        default:
            return "Not specified";
    }
}

ostream& operator<<(ostream& os, const Book& book) {
    os << "Title: " << book.get_title() << '\n'
       << "Author: " << book.get_author() << '\n'
       << "ISBN: " << book.get_isbn() << '\n'
       << "Genre: " << genre_tostring(book.get_genre()) << '\n';

    return os;
}

int main() {
    try {
        Book ppp{"978-03219-92789-A", "Programming: Principles and Practice 2nd edition", "Bjarne Stroustrup", "2014", Genre::nonfiction};
        Book tcpl{"978-03215-63842-T", "The C++ Programming Language", "Bjarne Stroustrup", "2013", Genre::nonfiction};
        Book tcpl_copy{"978-03215-63842-T", "The C++ Programming Language", "Bjarne Stroustrup", "2013", Genre::nonfiction};

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception\n";
        return 2;
    }
}