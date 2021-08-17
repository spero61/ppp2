// calculate the size (in byte) of types without using sizeof() except to verify the answer
#include <iostream>

int size(int) {  // just use the type of the argument, not its value
    int* p = new int[2];
    int sz = reinterpret_cast<char*>(&p[1]) - reinterpret_cast<char*>(&p[0]);  // turn pointers into char*s (that is byte addresses)
    // Note that plain &p[1] - &p[0] is 0. Subtracting pointers to elements of an array gives the number of elements between the two pointers.
    delete[] p;
    return sz;  // the size
}

int size(double) {
    double* p = new double[2];
    int sz = reinterpret_cast<bool*>(&p[1]) - reinterpret_cast<bool*>(&p[0]);  // also works, because bool is also 1 byte
    delete[] p;
    return sz;
}

int size(bool) {
    bool* p = new bool[2];
    int sz = reinterpret_cast<char*>(&p[1]) - reinterpret_cast<char*>(&p[0]);
    delete[] p;
    return sz;
}

int size(char) {
    char* p = new char[2];
    int sz = reinterpret_cast<char*>(&p[1]) - reinterpret_cast<char*>(&p[0]);
    delete[] p;
    return sz;
}

int main() {
    try {
        std::cout << "size(1): " << size(1) << '\n';
        std::cout << "size(0.1): " << size(0.1) << '\n';
        std::cout << "size(true): " << size(true) << '\n';
        std::cout << "size('$'): " << size('$') << "\n\n";

        // verify the answer
        std::cout << "Verify the answer using sizeof():\n";
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
