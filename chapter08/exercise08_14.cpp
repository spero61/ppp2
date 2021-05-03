// Q. Can we declare a non-reference function argument const (e.g., void f(const int);)?
// A. Yes.

// What might that mean? Why might we want to do that? Why don’t people do that often?
// A. That might mean that the function argument is passed-by-const-reference.
//    As if you try to change the value of that argument in the function, compiler catches the error.
//    People do not often do this because in this way it is obligated to use pass-by-const-reference only.
//    And might be confused with 'pass-by-value' as it does not contain ampersand(&) character.

// Try it; write a couple of small programs to see what works.

#include "std_lib_facilities.h"

void my_function(const int c)
{
    // c += 100; // compile-error
    cout << c + 70 << '\n';
}

int main()
{
    const int age = 33;
    my_function(age);
    my_function(2021);
}