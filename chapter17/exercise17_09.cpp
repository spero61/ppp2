// a program to determine which way do the stack and the heap (free store) grows

#include <iostream>

void growth_direction(int* address01, int* address02, const char* name = "this one") {
    if ((address02 - address01) > 0)  // if address of the variable assigned later has higher address than the previous one
        std::cout << name << " grows upward\n";
    else
        std::cout << name << " grows downward\n";
}

int main() {
    try {
        // stack growth determination
        int stack01 = 2021;
        int stack02 = 8;
        int stack03 = 17;

        int* stack01_p = &stack01;
        int* stack02_p = &stack02;
        int* stack03_p = &stack03;

        std::cout << "stack addresses:\n"
                  << "stack01_p: " << stack01_p << '\n'
                  << "stack02_p: " << stack02_p << '\n'
                  << "stack03_p: " << stack03_p << "\n\n";

        // heap growth determination
        int* heap01_p = new int{19};
        int* heap02_p = new int{5};
        int* heap03_p = new int{57};

        std::cout << "heap addresses:\n"
                  << "heap01_p: " << heap01_p << '\n'
                  << "heap02_p: " << heap02_p << '\n'
                  << "heap03_p: " << heap03_p << "\n\n";

        // print results
        std::cout << "Result:\n";
        growth_direction(stack01_p, stack02_p, "Stack");
        growth_direction(heap01_p, heap02_p, "Heap");

        delete heap01_p;
        delete heap02_p;
        delete heap03_p;

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}