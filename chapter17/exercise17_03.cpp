// C-style string manipulation

#include <stdio.h>  // the C standard I/O

void to_lower(char* s) {
    while (*s != '\0') {
        if ('A' <= *s && *s <= 'Z') {
            *s += 32;
        }
        *s++;
    }
}

int main() {
    // char* greeting = "Hello World"; // warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]
    char greeting[] = "Hello, World!";  // C++ version of C-style string
    printf("%s\n", greeting);

    to_lower(greeting);
    printf("%s\n", greeting);
    return 0;
}