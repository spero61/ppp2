// finds the first occurrence of the C-style string x in s
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

char* findx(const char* s, const char* x) {  // find string x in string s, return the substring s from the first occurrence of x
    int s_len = string_length(s);
    int x_len = string_length(x);
    int count = 0;
    for (int i = 0; i < s_len - x_len; ++i) {
        for (int j = 0; x[j]; ++j) {
            if (s[i + j] != x[j])
                break;
            count++;
        }
        if (count == x_len)
            return const_cast<char*>(&s[i]);  // Note: might be better to change the return type to 'const char*' instead of using const_cast
        count = 0;
    }
    return nullptr;  // return nullptr for "not found"
}

int main() {
    try {
        char greetings[] = "7:22 PM Tuesday, August 17, 2021 Sunset";  // C++ version of C-style string
        char x[] = "day";
        printf("%s\n", greetings);

        char* result = findx(greetings, x);
        printf("%s\n", result);

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}