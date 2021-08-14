#include <iostream>
#include <vector>

void print_array10(std::ostream& os, int* a) {
    for (int i = 0; i < 10; ++i) {
        os << a[i] << '\t';
    }
    os << '\n';
}

void print_array(std::ostream& os, int* a, int n) {
    for (int i = 0; i < n; ++i) {
        os << a[i] << '\t';
    }
    os << '\n';
}

void print_vector(std::ostream& os, std::vector<int> vi) {
    for (int i = 0; i < vi.size(); ++i) {
        os << vi[i] << '\t';
    }
    os << '\n';
}

int main() {
    try {
        int* numbers = new int[10]{2021, 8, 13, 23, 36, 1, 9, 9, 3, 7};
        for (int i = 0; i < 10; ++i) {
            std::cout << numbers[i] << '\n';
        }
        delete[] numbers;
        std::cout << '\n';

        int* from_hundred_10 = new int[10]{100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
        print_array10(std::cout, from_hundred_10);
        delete[] from_hundred_10;

        int* from_hundred_11 = new int[11]{100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
        print_array(std::cout, from_hundred_11, 11);
        delete[] from_hundred_11;

        int* from_hundred_20 = new int[20]{100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119};
        print_array(std::cout, from_hundred_20, 20);
        delete[] from_hundred_20;

        // do the same as above using vector
        std::cout << "\nusing a vector instead of an array and a print_vector() instead of print_array()\n\n";
        std::vector<int> v_nums = {100, 101, 102, 103, 104, 105, 106, 107, 108, 109};
        print_vector(std::cout, v_nums);  // equals to print_array10(cout, from_hundred_10);

        v_nums.push_back(110);
        print_vector(std::cout, v_nums);  // equals to print_array(cout, from_hundred_11, 11);

        int next_num{v_nums[v_nums.size() - 1]};
        for (int i = v_nums.size(); i < 20; ++i) {
            v_nums.push_back(++next_num);
        }
        print_vector(std::cout, v_nums);  // equals to print_array(cout, from_hundred_20, 20);

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}
