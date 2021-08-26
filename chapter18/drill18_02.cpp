// Chapter 18: STL vector drill (compare the effort involved to drill18_01.cpp)
#include <iostream>
#include <vector>

std::vector<int> gv{1, 2, 4, 8, 16, 32, 64, 128, 256, 512};  // define a global vector<int>

int fac(int n) {  // factorial(n); n!
    int r = 1;
    while (n > 1) {
        r *= n;
        --n;
    }
    return r;
}

void print_vector_int(const std::vector<int>& vi) {
    for (int x : vi) {  // print out the elements of argument vector<int>
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

void f(const std::vector<int>& vi) {
    std::vector<int> lv(vi.size());  // local vector<int> with the same number of elements as the argument vector<int> vi
    lv = gv;                         // copy the values from gv into lv
    print_vector_int(lv);            // print out the elements of lv

    std::vector<int> lv2{vi};  // initialize lv2 to be a copy of the argument vector
    print_vector_int(lv2);     // print out the elements of lv2
}

int main() {
    try {
        std::cout << "f(gv)\n";
        f(gv);

        std::cout << "\nf(vv)\n";
        std::vector<int> vv;
        for (int i = 0; i < 10; ++i) {  // initialize it with the first ten factorial values (e.g., 1, 2*1, 3*2*1, 4*3*2*1, etc.)
            vv.push_back(fac(i + 1));
        }
        f(vv);

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}
