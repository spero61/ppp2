// copy C-style string without using standard library functions

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
    char* dup = new char[n];
    for (int i = 0; i < n; ++i) {
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