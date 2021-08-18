// modify the Link class from §17.10.1 using singly-linked list, left the prev member out of Link
#include <iostream>
#include <string>

using namespace std;

class Link {
   public:
    string value;
    Link(const string& v, Link* s = nullptr)
        : value{v}, succ{s} {}
    Link* insert(Link* n);                    // insert n before this object
    Link* erase(Link* n);                     // remove Link* n object from list, return nullptr for "not found"
    Link* find(const string& s);              // find s in list; return nullptr for "not found"
    const Link* find(const string& s) const;  // find s in const list; return nullptr for "not found"
    const Link* advance(int n) const;         // move n positions in list; return nullptr for "not found"
    Link* next() const { return succ; }

   private:
    Link* succ;
};

Link* Link::insert(Link* n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;
    n->succ = this;
    return n;
}

Link* Link::erase(Link* n) {
    Link* p = this;
    while (p->succ) {
        if (p->succ->value == n->value) {
            p->succ = p->succ->succ;
            return n;
        }
        p = p->succ;
    }
    return nullptr;  // "not found"
}

Link* Link::find(const string& s) {
    Link* p = this;
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return nullptr;
}

const Link* Link::find(const string& s) const {
    const Link* p = this;
    while (p) {
        if (p->value == s) return p;
        p = p->succ;
    }
    return nullptr;
}

const Link* Link::advance(int n) const {  // this operation does not change the state of a Link
    if (n < 0) {
        cerr << "error: n cannot be negative integer\n";
        return this;
    }
    const Link* p = this;
    if (p == nullptr) return nullptr;
    if (0 < n) {  // positive n moves forward
        while (n--) {
            if (p->succ == nullptr) return nullptr;
            p = p->succ;
        }
    }
    // return const_cast<Link*>(p);  // probably return type is given to Link* not const Link* for the practice purpose of "Casts"
    // so I changed the return type from 'Link*' to 'const Link*' to follow the author's advice mentioned in 610 page.
    return p;
}

void print_all(Link* p) {
    cout << "{";
    while (p) {
        cout << p->value;
        if (p = p->next()) cout << ", ";
    }
    cout << "}";
}

int main() {
    try {
        Link* norse_gods = new Link{"Thor"};
        norse_gods = norse_gods->insert(new Link{"Odin"});
        norse_gods = norse_gods->insert(new Link{"Zeus"});
        norse_gods = norse_gods->insert(new Link{"Freia"});

        Link* greek_gods = new Link{"Hera"};
        greek_gods = greek_gods->insert(new Link{"Athena"});
        greek_gods = greek_gods->insert(new Link{"Mars"});
        greek_gods = greek_gods->insert(new Link{"Poseidon"});

        print_all(norse_gods);
        cout << "\n";

        print_all(greek_gods);
        cout << "\n";

        cout << "\n~ corrections have made ~\n\n";

        Link* p1 = greek_gods->find("Mars");
        if (p1) p1->value = "Ares";

        Link* p2 = norse_gods->find("Zeus");
        if (p2) {
            if (p2 == norse_gods) norse_gods = p2->next();
            greek_gods = greek_gods->insert(norse_gods->erase(p2));
        }

        print_all(norse_gods);
        cout << "\n";

        print_all(greek_gods);
        cout << "\n";

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}