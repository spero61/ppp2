// Drill 15 : Class definition drill

#include "std_lib_facilities.h"

// 1)
// struct Person {
//     Person(string name_arg, int age_arg) : name{name_arg}, age{age_arg} {} // 4)
//     string name;
//     int age;
// };

// 3)
// istream& operator>>(istream& is, Person& p) {
//     return is >> p.name >> p.age;
// }

// ostream& operator<<(ostream& os, const Person& p) {
//     return os << '(' << p.name << ": " << p.age << ')';
// }

// 5)
class Person {
   public:
    Person(string name_arg, int age_arg) : name_val{name_arg}, age_val{age_arg} {
        // 7)
        if (age_arg <= 0 || 150 < age_arg) error("Bad Person: age range [0:150)");
        for (char ch : name_arg) {
            if (ch == ';' || ch == ':' || ch == '"' || ch == '\'' || ch == '[' || ch == ']' || ch == '*' || ch == '&' || ch == '^' || ch == '%' || ch == '$' || ch == '#' || ch == '@' || ch == '!')
                error("Bad Person: invalid character for the name");
        }
    }
    string name() const { return name_val; }
    int age() const { return age_val; }
    void set_name(string name_arg) { name_val = name_arg; }
    void set_age(int age_arg) { age_val = age_arg; }

   private:
    string name_val;
    int age_val;
};

// 6)
istream& operator>>(istream& is, Person& p) {
    string name;
    int age;
    is >> name >> age;
    p.set_name(name);
    p.set_age(age);
    return is;
}

ostream& operator<<(ostream& os, const Person& p) {
    return os << p.name() << ": " << p.age();
}

int main() {
    try {
        // 2)
        Person p1{"Goofy", 63};
        cout << p1.name() << " : " << p1.age() << '\n';

        cout << "please type name, age separated by space\n> ";
        cin >> p1;
        cout << p1 << '\n';

        // 8)
        int count{0};
        cout << "how many variables of type Person are you going to create?\n> ";
        cin >> count;
        vector<Person> persons;
        for (int i = 0; i < count; ++i) {
            string name;
            int age;
            cout << "persons[" << i << "]\nname: ";
            cin >> name;
            cout << "age: ";
            cin >> age;
            cout << '\n';
            Person tmp{name, age};
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