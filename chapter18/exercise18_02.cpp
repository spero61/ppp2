// finds the first occurrence of the C-style string x in s without using STL, subscripting
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
    char* tmp_s = const_cast<char*>(s);  // since the function is provided as follows: char* findx(const char* s, const char* x)
    char* tmp_x = const_cast<char*>(x);  // it is necessary to remove const from x and y respectively
    for (int i = 0; i < s_len - x_len; ++i) {
        for (int j = 0; j < x_len; ++j) {
            if (*tmp_s == *tmp_x) {
                ++count;
            }
            ++tmp_s;
            ++tmp_x;
        }
        tmp_s -= x_len;
        tmp_x -= x_len;

        if (count == x_len)
            return tmp_s;  // Note: might be better to change the return type to 'const char*' instead of using const_cast
        count = 0;
        ++tmp_s;
    }

    tmp_s -= (s_len - x_len);  // set pointer to the first element of the array s;
    return nullptr;            // return nullptr for "not found"
}

int main() {
    try {
        char greetings[] = "5:50 PM Tuesday, October 19, 2021 Sunset";  // C++ version of C-style string
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