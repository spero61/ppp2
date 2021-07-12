// drill14_07.cpp

#include "std_lib_facilities.h"

class B2 {
   public:
    virtual void pvf() = 0;
};

class D21 : public B2 {
   public:
    void pvf() override { cout << str << '\n'; }
    void set_str(string str_arg) { str = str_arg; }

   private:
    string str;
};

class D22 : public B2 {
   public:
    void pvf() override { cout << num << '\n'; }
    void set_num(int num_arg) { num = num_arg; }

   private:
    int num;
};

void f(B2& b2ref) {
    b2ref.pvf();
}

int main() {
    D21 d21;
    d21.set_str("this is D21::pvf()");

    D22 d22;
    d22.set_num(2021);

    f(d21);  // this is D21::pvf()
    f(d22);  // 2021
}