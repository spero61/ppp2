// copy C-style string without using standard library functions

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
    int n = string_length(s);
    char* dup = new char[n + 1];       // should be n + 1 NOT n because of '\0' (null character of the string)
    for (int i = 0; i < n + 1; ++i) {  // when i = n, it copies the null character to indicate the end of the string
        dup[i] = s[i];
    }
    return dup;
}

int main() {
    try {
        char today[] = "Today is August 15, 2021 :)";  // C++ version of C-style string
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