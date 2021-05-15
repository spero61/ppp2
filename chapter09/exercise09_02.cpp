// Design and implement a Name_pairs class holding (name,age) pairs where name is a string and age is a double.
// Represent that as a vector<string> (called name) and a vector<double> (called age) member.
// Provide an input operation read_names() that reads a series of names.
// Provide a read_ages() operation that prompts the user for an age for each name.
// Provide a print() operation that prints out the (name[i],age[i]) pairs (one per line) in the order determined by the name vector.
// Provide a sort() operation that sorts the name vector in alphabetical order and reorganizes the age vector to match.
// Implement all "operations" as member functions.
// Test the class (of course: test early and often).

#include "std_lib_facilities.h"

class Name_pairs {
   public:
    void read_names();
    void read_ages();

    void print() const;
    void sort();

   private:
    vector<string> name;
    vector<double> age;
    const string quit{"quit"};  // quit read_names()
    bool is_duplicated(const string& name_val) const;
};

bool Name_pairs::is_duplicated(const string& user_input) const
// Checks if string n is already present on name vector.
{
    for (string x : name) {
        if (x == user_input) return true;
    }
    return false;
}

void Name_pairs::read_names() {
    string user_input{};
    int index{0};

    cout << "Please, provide a name followed by enter\n"
         << "If you want to stop read_names() just provide 'quit' instead of name\n";
    cout << "name[" << index << "]: ";
    while (cin >> user_input && user_input != quit) {
        cout << "name[" << ++index << "]: ";
        if (is_duplicated(user_input))
            cout
                << "Name you entered is already exist! try another name";
        else
            name.push_back(user_input);
    }
}

void Name_pairs::read_ages() {
    double user_input{};
    for (int i = 0; i < name.size(); ++i) {
        cout << name[i] << " : ";
        cin >> user_input;
        age.push_back(user_input);
    }
}

void Name_pairs::print() const {
    for (int i = 0; i < name.size(); ++i) {
        cout << "name[" << i << "] : age[" << i << "] is " << name[i] << " : " << age[i] << '\n';
    }
}

void Name_pairs::sort() {
    // to create sorted_index, copy name as name_copy
    vector<string> name_copy{name};

    for (int i = 0; i < name_copy.size(); ++i)
        name_copy[i] += to_string(i);

    // explicitly call std::sort(), if not complier would search Name_pairs::sort() instead, which is recursive.
    std::sort(name.begin(), name.end());
    std::sort(name_copy.begin(), name_copy.end());

    // create and set sorted_index to figure out sorted order of the index
    vector<int> sorted_index;
    for (int i = 0; i < name_copy.size(); ++i) {
        // last_index to get an index from last char of name_copy[i]
        int last_index = name_copy[i].size() - 1;

        // subtract '0' to convert char to int
        int index = name_copy[i][last_index] - '0';

        sorted_index.push_back(index);
    }

    // make a copy of age using sorted_index to match in correct order
    vector<double> age_copy;
    for (int i = 0; i < sorted_index.size(); ++i) {
        int index = sorted_index[i];
        age_copy.push_back(age[index]);
    }

    // substitute age_copy for age
    age = age_copy;
}

int main() {
    try {
        Name_pairs np_test;

        np_test.read_names();
        np_test.read_ages();
        cout << "~ before sort name ~";
        np_test.print();

        cout << '\n';

        np_test.sort();
        cout << "~ after sort name ~";
        np_test.print();

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception\n";
        return 2;
    }
}