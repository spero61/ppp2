#include <iostream>
#include <string>

using namespace std;

struct Link {
    string value;
    Link* prev;
    Link* succ;
    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} {}
};

Link* insert(Link* p, Link* n)  // insert n before p; return n
{
    if (n == nullptr) return p;
    if (p == nullptr) return n;
    n->succ = p;                     // p comes after n
    if (p->prev) p->prev->succ = n;  // n comes after what used to be p's predecessor
    n->prev = p->prev;               // p's predecessor becomes n's predecessor
    p->prev = n;                     // n becomes p's predecessor
    return n;
}

Link* add(Link* p, Link* n)  // insert n after p; return n
{
    if (n == nullptr) return p;
    if (p == nullptr) return n;
    n->prev = p;                     // p comes before n
    if (p->succ) p->succ->prev = n;  // n comes before what used to be p's successor
    n->succ = p->succ;               // p's successor becomes n's successor
    p->succ = n;                     // n becomes p's successor
    return n;
}

Link* erase(Link* p)  // remove *p from list; return p's successor
{
    if (p == nullptr) return nullptr;
    if (p->succ) p->succ->prev = p->prev;
    if (p->prev) p->prev->succ = p->succ;
    return p->succ;
}

Link* find(Link* p, const string& s)  // find s in list; return nullptr for "not found"
{
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return nullptr;
}

Link* advance(Link* p, int n)  // move n positions in list; return nullptr for "not found"
{
    if (p == nullptr) return nullptr;
    if (0 < n) {  // positive n moves forward
        while (n--) {
            if (p->succ == nullptr) return nullptr;
            p = p->succ;
        }
    } else if (n < 0) {  // negative n moves backward
        while (n++) {
            if (p->prev == nullptr) return nullptr;
            p = p->prev;
        }
    }
    return p;
}

void print_all(Link* p) {
    cout << "{";
    while (p) {
        cout << p->value;
        if (p = p->succ) cout << ", ";
    }
    cout << "}";
}

int main() {
    Link* norse_gods = new Link{"Thor"};
    norse_gods = insert(norse_gods, new Link{"Odin"});
    norse_gods = insert(norse_gods, new Link{"Zeus"});
    norse_gods = insert(norse_gods, new Link{"Freia"});

    Link* greek_gods = new Link{"Hera"};
    greek_gods = insert(greek_gods, new Link{"Athena"});
    greek_gods = insert(greek_gods, new Link{"Mars"});
    greek_gods = insert(greek_gods, new Link{"Poseidon"});

    print_all(norse_gods);
    cout << "\n";

    print_all(greek_gods);
    cout << "\n";

    cout << "\n~ corrections have made ~\n\n";

    Link* p1 = find(greek_gods, "Mars");
    if (p1) p1->value = "Ares";

    Link* p2 = find(norse_gods, "Zeus");
    if (p2) {
        if (p2 == norse_gods) norse_gods = p2->succ;
        erase(p2);
        greek_gods = insert(greek_gods, p2);
    }

    print_all(norse_gods);
    cout << "\n";

    print_all(greek_gods);
    cout << "\n";

    return 0;
}
