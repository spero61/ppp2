// what happens if you give strdup(), findx(), and strcmp() implemented
// in exercise18_01 - 03 an argument that is not a C-style string.

// NEVER do this in real code (non-experimental).

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

// from exercise18_01
// copies a C-style string into memory it allocates on the free store
char* strdup(const char* s) {
    int n = string_length(s) + 1;  // + 1 is for the space for '\0' (null character of the string)
    char* dup = new char[n];
    while (*dup++ = *s++)  // see also 276 page of The C++ Programming Language 4th edition §11.1.4 Increment and Decrement.
        ;
    dup -= n;  // let the dup pointer to indicate the first char of the C-style string (since did not move the pointer when )
    return dup;
}

// from exercise18_02
// find string x in string s, return the substring s from the first occurrence of x
char* findx(const char* s, const char* x) {
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

// from exercise18_03
// compares two strings case-sensitively in lexicographical order
int strcmp(const char* s1, const char* s2) {
    while (*s1 && *s2) {
        if (*s1 < *s2) {  // s1 is lexicographically before s2
            return -1;
        } else if (*s1 > *s2) {  // s1 is lexicographically after s2
            return 1;
        } else {
            ++s1;
            ++s2;
        }
    }
    // s1 equals s2
    return 0;
}

int main() {
    try {
        // strdup()
        char today[] = {'T', 'o', 'd', 'a', 'y'};  // fake C-style string without having a '\0'
        printf("%s\n", today);

        char* copied_today = strdup(today);
        printf("%s\n", copied_today);

        delete[] copied_today;

        // NOTE: Using fake C-style string leads to copy 'random' 6th character
        // (which is supposed to '\0') from somewhere in the memory which can create havoc.
        // ---------------------------------------------

        // findx()
        char wishlist[] = {'M', 'a', 'c', 'B', 'o', 'o', 'k', 'P', 'r', 'o', 'M', '1', 'M', 'a', 'x'};  // fake C-style string without having a '\0'
        char x[] = {'P', 'r', 'o'};
        printf("%s\n", wishlist);

        char* result = findx(wishlist, x);
        printf("%s\n", result);

        // NOTE: findx does not work with stack-allocated "fake C-style strings"
        // ---------------------------------------------

        // strcmp()
        // text1 is lexicographically before text2
        char text1[] = {'f', 'r', 'i', 'd', 'a', 'y'};
        char text2[] = {'p', 'e', 'r', 'j', 'a', 'n', 't', 'a', 'i'};
        printf("%i\n", strcmp(text1, text2));

        // text3 is lexicographically after text4
        char text3[] = {'w', 'e', 'd', 'n', 'e', 's', 'd', 'a', 'y'};
        char text4[] = {'k', 'e', 's', 'k', 'i', 'v', 'i', 'i', 'k', 'k', 'o'};
        printf("%i\n", strcmp(text3, text4));

        // text5 is eqaul to text6
        char text5[] = {'d', 'o', 'n', 'e'};
        char text6[] = {'d', 'o', 'n', 'e'};
        printf("%i\n", strcmp(text5, text6));

        // NOTE: It seems strcmp work along with text1,2 and text3,4 comparison,
        //       which is the case lexicographically before or after.
        //       However, it does not work when the text is the 'same'.
        //       I assume that the space for omitted '\0' is read to evaluate two strings
        //       cause this problem as they compare two randomly read memory for those respectively.
        // ---------------------------------------------

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}