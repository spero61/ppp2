// a program to determine which way do the stack and the heap (free store) grows

/* 
-- higher address --

(Stack)
  ↓


  ↑
(Heap)

(Static Storage)

-- lower address --
*/

#include <iostream>

// to check static storage
int global01 = 2021;
int global02 = 9;
int global03 = 29;

void growth_direction(int* address01, int* address02, const char* name = "this one") {
    if ((address02 - address01) > 0)             // if address of the variable assigned later has higher address than the previous one
        std::cout << name << " grows upward\n";  // grows to larger addresses
    else
        std::cout << name << " grows downward\n";
}

int main() {
    try {
        // static storage check
        std::cout << "static storage:\n"
                  << "address of global01: " << &global01 << '\n'
                  << "address of global02: " << &global02 << '\n'
                  << "address of global03: " << &global03 << "\n\n";

        // stack growth determination
        int stack01 = 2021;
        int stack02 = 9;
        int stack03 = 29;

        std::cout << "stack addresses:\n"
                  << "address of stack01: " << &stack01 << '\n'
                  << "address of stack02: " << &stack02 << '\n'
                  << "address of stack03: " << &stack03 << "\n\n";

        // heap growth determination using array on the free store
        int* heap_arr = new int[3]{2021, 9, 29};

        std::cout << "heap addresses:\n"
                  << "address of heap_arr[0]: " << &heap_arr[0] << '\n'
                  << "address of heap_arr[1]: " << &heap_arr[1] << '\n'
                  << "address of heap_arr[2]: " << &heap_arr[2] << "\n\n";

        // print results
        std::cout << "Result:\n";
        growth_direction(&global01, &global02, "Static storage");
        growth_direction(&stack01, &stack02, "Stack");
        growth_direction(&heap_arr[0], &heap_arr[1], "Heap");

        delete[] heap_arr;

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}