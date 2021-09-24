// write a function, strcmp() to compare C-style strings
#include <iostream>

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
        // text1 is lexicographically before text2
        char text1[] = "friday";
        char text2[] = "perjantai";
        printf("%i\n", strcmp(text1, text2));

        // text3 is lexicographically after text4
        char text3[] = "wednesday";
        char text4[] = "keskiviikko";
        printf("%i\n", strcmp(text3, text4));

        // text5 is eqaul to text6
        char text5[] = "Diablo 2: Resurrected has released";
        char text6[] = "Diablo 2: Resurrected has released";
        printf("%i\n", strcmp(text5, text6));

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}