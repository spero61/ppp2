// drill14_03.cpp

#include "std_lib_facilities.h"

class B1 {
   public:
    virtual void vf() const { cout << "B1::vf()\n"; }
    void f() const { cout << "B1::f()\n"; }
};

class D1 : public B1 {
   public:
    void vf() const override { cout << "D1::vf()\n"; }
};

int main() {
    D1 d1;
    B1& b1ref = d1;
    b1ref.vf();  // D1::vf()
    b1ref.f();   // B1::f()
}