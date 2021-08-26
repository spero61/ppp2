// char* strdup(const char*) without using STL, subscripting
#include <iostream>

// instead of strlen()
int string_length(const char* s) {
    int count = 0;
    while (*s) {
        ++count;
        ++s;
    }
    return count;
}

char* strdup(const char* s) {
    int n = string_length(s) + 1;  // + 1 is for the space for '\0' (null character of the string)
    char* dup = new char[n];
    while (*dup++ = *s++)  // see also 276 page of The C++ Programming Language 4th edition §11.1.4 Increment and Decrement.
        ;
    dup -= n;  // let the dup pointer to indicate the first char of the C-style string (since did not move the pointer when )
    return dup;
}

int main() {
    try {
        char today[] = "Dum spiro spero means 'While I breathe, I hope' in Latin.";  // C++ version of C-style string
        printf("%s\n", today);

        char* copied_today = strdup(today);
        printf("%s\n", copied_today);
        delete[] copied_today;

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}