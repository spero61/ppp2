// char* strdup(const char*) without using STL, subscripting
#include <iostream>

// instead of strlen()
int string_length(const char* s) {
    int count = 0;
    while (*s != '\0') {
        count++;
        *s++;
    }
    return count;
}

char* strdup(const char* s) {
    int n = string_length(s);
    char* dup = new char[n + 1];  // n + 1: because it needs one more byte for the null character '\0'
    // deal with the case until n (copy contents of the string)
    for (int i = 0; i < n; ++i) {
        *dup++ = *s++;
    }
    // deal with the n+1 th value to mark end of the string
    *dup = '\0';  // end the C-style string with the null character '\0'
    dup -= n;     // let the dup pointer to indicate the first char of the C-style string (since did not move the pointer when )
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