// Chapter 18: Array drill (compare the effort involved to drill18_02.cpp)
#include <iostream>

int ga[10] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};  // define a global int array

int fac(int n) {  // factorial(n); n!
    int r = 1;
    while (n > 1) {
        r *= n;
        --n;
    }
    return r;
}

void print_arr(int arr[], int sz) {  // print out the elements of argument array
    for (int i = 0; i < sz; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

void f(int arr[], int n) {
    int la[10];                    // local int array la of ten ints
    for (int i = 0; i < n; ++i) {  // copy the values from ga int la
        la[i] = ga[i];
    }
    print_arr(la, 10);  // print out the elements of la

    int* p = new int[n];           // initialize with an array allocated on the free store
    for (int i = 0; i < n; ++i) {  // copy the values from the argument array into the free-store array
        p[i] = arr[i];
    }
    print_arr(p, 10);  // print out the elements of the free-store array

    delete[] p;  // deallocate the free-store array
}

int main() {
    try {
        std::cout << "f(ga, 10)\n";
        f(ga, 10);

        std::cout << "\nf(aa, 10)\n";
        int aa[10];
        for (int i = 0; i < 10; ++i) {  // initialize it with the first ten factorial values (e.g., 1, 2*1, 3*2*1, 4*3*2*1, etc.)
            aa[i] = fac(i + 1);
        }
        f(aa, 10);

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}
