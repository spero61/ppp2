// a program that reads characters from cin into an array (on the free store)
// Do not use a std::string, Do not worry about memory exhaustion

#include <iostream>

constexpr int MAX_LENGTH{65536};

int main() {
    try {
        char* str = new char[MAX_LENGTH];        // big enough to read characters
        std::cin.getline(str, MAX_LENGTH, '!');  // http://www.cplusplus.com/reference/istream/istream/getline/

        std::cout << "\nresult: \n";
        std::cout << str << '\n';
        delete[] str;

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}