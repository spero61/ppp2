// Create a Library class. Include vectors of Books and Patrons.
// Include a struct called Transaction. Have it include a Book, a Patron,
// and a Date from the chapter. Make a vector of Transactions.
// Create functions to add books to the library, add patrons to the library,
// and check out books. Whenever a user checks out a book,
// have the library make sure that both the user and the book are in the library.
// If they aren’t, report an error. Then check to make sure that the user owes no fees.
// If the user does, report an error. If not, create a Transaction, and place it in the vector of Transactions.
// Also write a function that will return a vector that contains the names of all Patrons who owe fees.

#include "exercise09_09_Chrono.h"
#include "std_lib_facilities.h"

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

    bool check_out() { return is_checked_out = true; };
    bool check_in() { return is_checked_out = false; };

    string get_isbn() const { return isbn; };
    string get_title() const { return title; };
    string get_author() const { return author; };
    string get_copyright_date() const { return copyright_date; };
    Genre get_genre() const { return genre; };
    bool get_is_checked_out() const { return is_checked_out; };

   private:
    string isbn;
    string title;
    string author;
    string copyright_date;
    Genre genre;

    bool is_checked_out;
};

class Invalid_isbn {
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

class Patron {
   public:
    Patron(string name, int card_number);

    void set_fee(int amount) {
        if (amount >= 0)
            fee = amount;
        else
            cerr << "error: provide fee that is greater than or equal to 0\n";
    }

    string get_name() const { return name; };
    int get_card_number() const { return card_number; };
    int get_fee() const { return fee; };

   private:
    string name;
    int card_number;
    int fee;
};

class Invalid_Patron {};

// default: fee equals to 0
Patron::Patron(string name_arg, int card_number_arg)
    : name{name_arg}, card_number{card_number_arg}, fee{0} {
}

bool is_owed(Patron user) {
    if (user.get_fee() > 0)
        return true;

    return false;
}

class Library {
   public:
    struct Transaction {
        Book book;
        Patron patron;
        Date date;
    };

    void add_book(Book book) { books.push_back(book); };
    void add_patron(Patron patron) { patrons.push_back(patron); };
    void check_out(Book book, Patron patron, Date date);

    // Reports
    vector<string> get_owe_fees_names();  // Return a vector that constains the names of all Patrons who owe fees

   private:
    bool has_book;  // m_patron equal to p
    bool has_patron;
    vector<Book> books;
    vector<Patron> patrons;
    vector<Transaction> transactions;
};

bool operator==(const Book& a, const Book& b) {
    return (a.get_isbn() == b.get_isbn());
}

bool operator!=(const Book& a, const Book& b) {
    return !(a == b);
}

bool operator==(const Patron& a, const Patron& b) {
    return (a.get_card_number() == b.get_card_number());
}

bool operator!=(const Patron& a, const Patron& b) {
    return !(a == b);
}

// make sure that both the user and the book are in the library, if they aren't report an error
// then check to make sure that user owes no fee, if the user does, report an error
// if not create a Transaction and place it in the vector of Transactions
void Library::check_out(Book book, Patron patron, Date date) {
    // initialize two bool variables as below:
    has_patron = false;
    has_book = false;

    // check whether the book is already checked out
    for (Transaction t : transactions) {
        if (t.book == book) {
            cerr << "error: " << book.get_title() << " is already checked out.\n";
            return;
        }
    }

    for (Book x : books) {
        if (x == book) has_book = true;
    }
    for (Patron user : patrons) {
        if (user == patron) has_patron = true;
    }

    if (!has_book) {
        cerr << "error: " << book.get_title() << " is not exist in the library.\n";
    }

    // REVIEW on this after learning pointers from later chapters.
    // maybe the author's intention is to utilize the function below instead of checking Transaction to determine the book is avaiable.
    // currently it is commented out

    // else if (book.get_is_checked_out()) { cerr << "error: " << book.get_title() << " is already checked out.\n"; }

    else if (is_owed(patron)) {
        cerr << "error: " << patron.get_name() << " owes fee, check out is not permitted\n";
    } else if (!has_patron) {
        cerr << "error: " << patron.get_name() << " is not exist in the library.\n";
    } else {
        transactions.push_back(Transaction{book, patron, date});
        cout << "success: " << book.get_title() << " is borrowed to " << patron.get_name() << " on "
             << date.year() << " " << int(date.month()) << " " << date.day() << '\n';
    }
}

vector<string> Library::get_owe_fees_names() {
    vector<string> owed_patrons;
    for (Patron user : patrons) {
        if (is_owed(user)) {
            owed_patrons.push_back(user.get_name());
        }
    }
    return owed_patrons;
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

ostream& operator<<(ostream& os, const Patron& patron) {
    os << "Username: " << patron.get_name() << '\n'
       << "Card Number: " << patron.get_card_number() << '\n'
       << "Owed Fee: " << patron.get_fee() << '\n';

    return os;
}

int main() {
    try {
        Book tcpl{"978-03215-63842-T", "The C++ Programming Language", "Bjarne Stroustrup", "2013", Genre::nonfiction};
        Book ppp{"978-03219-92789-A", "Programming: Principles and Practice 2nd edition", "Bjarne Stroustrup", "2014", Genre::nonfiction};
        Book tourcpp{"978-01349-97834-T", "A Tour of C++", "Bjarne Stroustrup", "2018", Genre::nonfiction};

        Patron rinko("Kamata Rinko", 20170118);
        Patron rika("Akana Rika", 20200429);
        Patron satomi("Sekiguchi Satomi", 20200430);
        Patron kokoro("Kurosawa Kokoro", 20160412);

        Library homaesil;

        homaesil.add_book(ppp);
        // homaesil.add_book(tcpl); // library does not own this book
        homaesil.add_book(tourcpp);

        rinko.set_fee(33);
        homaesil.add_patron(rinko);
        homaesil.add_patron(rika);
        homaesil.add_patron(kokoro);

        vector<string> owed_names = homaesil.get_owe_fees_names();

        for (string name : owed_names) {
            cout << "owed fee: " << name << '\n';
        }

        Date today{2021, Month::may, 14};
        homaesil.check_out(ppp, rika, today);        // success
        homaesil.check_out(ppp, satomi, today);      // fail: satomi has not added to the library
        homaesil.check_out(tourcpp, rinko, today);   // fail: rinko is owed fee
        homaesil.check_out(tourcpp, kokoro, today);  // success
        homaesil.check_out(tcpl, kokoro, today);     // fail: the book does not exist in the library
        homaesil.check_out(ppp, kokoro, today);      // fail: the book is already checked out

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception\n";
        return 2;
    }
}