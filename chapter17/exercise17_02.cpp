#include <iostream>

int main() {
    try {
        std::cout << "sizeof(char): " << sizeof(char) << '\n'
                  << "sizeof(bool): " << sizeof(bool) << "\n\n"

                  // integer types
                  << "sizeof(short): " << sizeof(short) << '\n'
                  << "sizeof(int): " << sizeof(int) << '\n'
                  << "sizeof(long): " << sizeof(long) << '\n'  // 4 bytes in Windows 10 (64bit), 8 bytes in Linux (64bit) on x64 CPU (Ryzen 5600X)
                  << "sizeof(long long): " << sizeof(long long) << "\n\n"

                  // floating-point types
                  << "sizeof(float): " << sizeof(float) << '\n'
                  << "sizeof(double): " << sizeof(double) << '\n'
                  << "sizeof(long double): " << sizeof(long double) << "\n\n"

                  // pointers (on modern computer systems, pointers tend to take up 8 bytes)
                  << "sizeof(char*): " << sizeof(char*) << '\n'
                  << "sizeof(bool*): " << sizeof(bool*) << '\n'
                  << "sizeof(short*): " << sizeof(short*) << '\n'
                  << "sizeof(int*): " << sizeof(int*) << '\n'
                  << "sizeof(double*): " << sizeof(double*) << '\n'
                  << "sizeof(long double*): " << sizeof(long double*) << '\n';

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}
