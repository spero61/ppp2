// drill14_02.cpp

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
    d1.vf();  // D1::vf()
    d1.f();   // B1::f()
}