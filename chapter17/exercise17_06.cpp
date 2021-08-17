// Approximately how much memory did you manage to allocate before failing?
// I used Windows 10 task manager and it shows that approximately 8 GB of free memory available (I have 16GB RAM in my computer)
// and this is equivalent to 8e+9 bytes.
// Since a 'double' in the system takes up 8 bytes of memory,
// approximately 1 billion of doubles are needed to induce 'memory exhaustion'

// Result:
// Windows 10 (21H01): terminal prints "std::bad_alloc" then the program is terminated, also it seems that some other (unrelated) programs are terminated
// Kali-Linux (WSL2): terminal prints "Killed" then the program is terminated

#include <iostream>

int main() {
    try {
        long double bytes{0};
        while (true) {
            double* killer = new double[1000000];  // cf. sizeof(double), is 8 bytes in most modern computing system (64 bit)
            std::cout << bytes << '\n';
            bytes += (1000000 * 8);  // 1 million doubles * 8 bytes (approx: 8MB)
            // delete[] killer;            // deliberately not deallocate the memory for the practice purpose
        }

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}