// Look at the headache-inducing last example of §8.4.
// Indent it properly and explain the meaning of each construct.
// Note that the example doesn't do anything meaningful; it is pure obfuscation.

/*
// dangerously ugly code
struct X {
void f(int x) {
struct Y {
int f() { return 1; } int m; };
int m;
m=x; Y m2;
return f(m2.f()); }
int m; void g(int m) {
if (m) f(m+2); else {
g(m+2); }}
X() { } void m3() {
}
 void main() {
X a; a.f(2);}
};
*/

struct X {
    // function within a class: a member function (the most common and useful case)
    void f(int x) {
        // class within a function: local class (avoid this)
        struct Y {
            int f() { return 1; }
            int m;  // this data member is never used
        };
        // redundant expressions as it just replace m for x
        // and assigned m is not used, thus argument int x has also no meaning
        int m;
        m = x;

        Y m2;  // create a Y variable m2 (a named object)

        // it returns 1, no matter the value of m2.f()
        // however, it has no meaning as well since the function f's return type is void
        return f(m2.f());
    }

    int m;  // variable is declared within a class scope of X

    void g(int m) {
        if (m)         // if m is the other than 0, it is excuted
            f(m + 2);  // does not mean anything
        else {         // excute only if m is equal to 0
            g(m + 2);  // also meaning less expression and it cause the infinite recursion
        }
    }
    X() {}  // default constructor
    // m3 is a defined member function that does not do anything

    void m3() {}

    // poorly named main function and it is misplaced
    void main() {
        X a;
        a.f(2);
    }
};