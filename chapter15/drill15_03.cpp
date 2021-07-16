// Drill 15 : Class definition drill. 9). the last one

#include "std_lib_facilities.h"

class Person {
   public:
    Person(string fname_arg, string sname_arg, int age_arg) : fname_val{fname_arg}, sname_val{sname_arg}, age_val{age_arg} {
        // 7)
        if (age_arg <= 0 || 150 < age_arg) error("Bad Person: age range [0:150)");
        if (!is_valid_char(fname_arg) || !is_valid_char(sname_arg)) {
            error("Bad Person: Invalid char for the names");
        }
    }
    string fname() const { return fname_val; }
    string sname() const { return sname_val; }
    int age() const { return age_val; }

    void set_fname(string fname_arg) { fname_val = fname_arg; }
    void set_sname(string sname_arg) { sname_val = sname_arg; }
    void set_age(int age_arg) { age_val = age_arg; }
    bool is_valid_char(string str);

   private:
    string fname_val;  // first_name
    string sname_val;  // second_name
    int age_val;
};

bool Person::is_valid_char(string str) {
    for (char ch : str) {
        // This might also be considered. However, isalpha() does not valid for the name other than in English.
        if (ch == ';' || ch == ':' || ch == '"' || ch == '\'' || ch == '[' || ch == ']' || ch == '*' || ch == '&' || ch == '^' || ch == '%' || ch == '$' || ch == '#' || ch == '@' || ch == '!')
            return false;
    }
    return true;
}

// 6)
istream& operator>>(istream& is, Person& p) {
    string fname, sname;
    int age;
    is >> fname >> sname >> age;
    p.set_fname(fname);
    p.set_sname(sname);
    p.set_age(age);
    return is;
}

ostream& operator<<(ostream& os, const Person& p) {
    return os << p.fname() << ' ' << p.sname() << ": " << p.age();
}

int main() {
    try {
        Person p1{"Goofy", "Muffy", 63};
        cout << p1.fname() << ' ' << p1.sname() << " : " << p1.age() << '\n';

        // 9)
        int count{0};
        cout << "how many variables of type Person are you going to create?\n> ";
        cin >> count;
        vector<Person> persons;
        for (int i = 0; i < count; ++i) {
            string fname, sname;
            int age;
            cout << "persons[" << i << "]\nfirst_name: ";
            cin >> fname;
            cout << "second_name: ";
            cin >> sname;
            cout << "age: ";
            cin >> age;
            cout << '\n';
            Person tmp{fname, sname, age};
            persons.push_back(tmp);
        }

        cout << "< Total: " << count << " Persons >\n";
        for (Person p : persons) {
            cout << p << '\n';
        }

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}