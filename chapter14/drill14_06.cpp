// drill14_06.cpp

#include "std_lib_facilities.h"

class B1 {
   public:
    virtual void vf() const { cout << "B1::vf()\n"; }
    void f() const { cout << "B1::f()\n"; }
    virtual void pvf() = 0;  // This causes "compile error" as a derived class(here, class D1) must implement a pure virtual function and it did not.
};

class D1 : public B1 {
   public:
    void vf() const override { cout << "D1::vf()\n"; }
    void f() const { cout << "D1::f()\n"; }
};

class D2 : public D1 {
   public:
    void vf() const override { cout << "D2::vf()\n"; }
    void f() const { cout << "D2::f()\n"; }
    void pvf() override { cout << "D2::pvf()\n"; }
};

int main() {
    D2 d2;
    d2.vf();   // D2::vf();
    d2.f();    // D2::f()
    d2.pvf();  // D2::pvf();
}