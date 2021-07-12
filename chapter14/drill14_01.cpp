// drill14_01.cpp

#include "std_lib_facilities.h"

class B1 {
   public:
    virtual void vf() const { cout << "B1::vf()\n"; }
    void f() const { cout << "B1::f()\n"; }
};

int main() {
    B1 b1;
    b1.vf();  // B1::vf()
    b1.f();   // B1::f()
}