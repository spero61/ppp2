// Make an "analog clock."
//
// A major part of this exercise is to find the functions
// that give you the time of day and a way of waiting for a short period of time
// and to learn to use them based on the documentation you found.
#include <stdio.h>
#include <time.h>

#include <chrono>
#include <iostream>
#include <thread>

int main() {
    try {
        time_t rawtime;
        struct tm* timeinfo;
        std::string s{""};

        while (true) {
            time(&rawtime);
            timeinfo = localtime(&rawtime);  // https://www.cplusplus.com/reference/ctime/localtime/
            s = asctime(timeinfo);
            std::cout << "hour: " << s[11] << s[12] << '\n';          // hh
            std::cout << "minute: " << s[14] << s[15] << '\n';        // mm
            std::cout << "second: " << s[17] << s[18] << '\n';        // ss
            printf("The current local time: %s", asctime(timeinfo));  // https://www.cplusplus.com/reference/ctime/ctime/
            std::this_thread::sleep_for(std::chrono::seconds(1));     // https://www.cplusplus.com/reference/thread/this_thread/sleep_for/
        }
        return 0;
    } catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...exception occurred\n";
        return 2;
    }
}