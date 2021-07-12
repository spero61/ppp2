// drill14_05.cpp

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

int main() {
    // 1
    B1 b1;
    b1.vf();  // B1::vf() same as drill14_01
    b1.f();   // B1::f() same as drill14_01
    cout << '\n';

    // 2
    D1 d1;
    d1.vf();  // D1::vf() same as drill14_01
    d1.f();   // D1::f() different from drill14_01 which was B1::f()
    cout << '\n';

    // 3
    B1& b1ref = d1;
    b1ref.vf();  // D1::vf() same as drill14_03
    b1ref.f();   // B1::f() same as drill14_03
}