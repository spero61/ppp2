// a program that reads characters into a std::string instead
// (string knows how to use the free store for you)

#include <iostream>
#include <string>

int main() {
    try {
        std::string str{""};
        bool is_finished{false};  // true when an exclamation mark '!' is entered

        while (!is_finished) {
            std::string tmp{""};
            std::getline(std::cin, tmp);  // https://www.cplusplus.com/reference/string/string/getline/
            tmp += '\n';                  // add a new line character to tmp
            for (char ch : tmp) {
                if (ch == '!') {
                    is_finished = true;
                    break;  // so as to not include characters after exclamation mark, '!'
                }
                str += ch;
            }
        }
        std::cout << "\nresult: \n";
        std::cout << str << '\n';

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}