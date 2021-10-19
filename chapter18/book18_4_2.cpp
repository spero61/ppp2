// 18.4.2 Debugging constructors and destructors

#include <iostream>
#include <vector>

using namespace std;

struct X {  // simple test class
    int val;
    void out(const string& s, int nv) { cerr << this << "->" << s << ": " << val << " (" << nv << ")\n"; }
    X() {  // default constructor
        out("X()", 0);
        val = 0;
    }
    X(int v) {
        val = v;
        out("X(int)", v);
    }
    X(const X& x) {  // copy constructor
        val = x.val;
        out("X(X&) ", x.val);
    }
    X& operator=(const X& a) {  // copy assignment
        out("X::operator=()", a.val);
        val = a.val;
        return *this;
    }
    ~X() { out("~X()", 0); }  // destructor
};

X glob(2);  // a global variable

X copy(X a) { return a; }

X copy2(X a) {
    X aa = a;
    return aa;
}

X& ref_to(X& a) { return a; }

X* make(int i) {
    X a(i);
    return new X(a);
}

struct XX {
    X a;
    X b;
};

int main() {
    try {
        X loc{4};          // local variable
        X loc2{loc};       // copy construction
        loc = X{5};        // copy assignment
        loc2 = copy(loc);  // call by value and return
        loc2 = copy2(loc);
        X loc3{6};
        X& r = ref_to(loc);  // call by reference and return
        delete make(7);
        delete make(8);
        vector<X> v(4);
        XX loc4;
        X* p = new X{9};  // an X on the free store
        delete p;
        X* pp = new X[5];  // an array of Xx on the free store
        delete[] pp;

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "unknown exception\n";
        return 2;
    }
}
