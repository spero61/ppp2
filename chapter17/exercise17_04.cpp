// copy C-style string

#include <iostream>

char* strdup(const char* s, int n) {
    char* dup = new char[n];
    for (int i = 0; i < n; ++i) {
        dup[i] = s[i];
    }
    return dup;
}

int main() {
    char today[] = "Today is August 15, 2021 :)";  // C++ version of C-style string
    printf("%s\n", today);

    char* dup = strdup(today, sizeof(today));
    printf("%s\n", dup);
    delete[] dup;

    return 0;
}