// reimplementation of exercise 18_06.cpp with C-style strings
#include <iostream>

using namespace std;

// instead of strlen()
int string_length(const char* s) {
    int count = 0;
    while (*s) {
        ++count;
        ++s;
    }
    return count;
}

// concatenates two strings with a separator using C-style strings
string cat_dot(const char* s1, const char* s2, const char* sep) {
    int s1_len = string_length(s1);
    int s2_len = string_length(s2);
    int sep_len = string_length(sep);
    int n = s1_len + s2_len + sep_len;

    char* result = new char[n];
    int count = 0;
    for (int i = 0; i < s1_len; ++i) {
        result[count++] = s1[i];
    }
    for (int i = 0; i < sep_len; ++i) {
        result[count++] = sep[i];
    }
    for (int i = 0; i < s2_len; ++i) {
        result[count++] = s2[i];
    }

    return result;
}

int main() {
    try {
        char firstname[] = "Niels";
        char lastname[] = "Bohr";
        char separator[] = " Henrik David ";

        cout << cat_dot(firstname, lastname, separator) << '\n';

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}