#include <iostream>
#include <string>

using namespace std;

class Link {
   public:
    string value;
    Link(const string& v, Link* p = nullptr, Link* s = nullptr)
        : value{v}, prev{p}, succ{s} {}
    Link* insert(Link* n);                    // insert n before this object
    Link* add(Link* n);                       // insert n after this object
    Link* erase();                            // remove this object from list; return this object's successor
    Link* find(const string& s);              // find s in list; return nullptr for "not found"
    const Link* find(const string& s) const;  // find s in const list; return nullptr for "not found"
    const Link* advance(int n) const;         // move n positions in list; return nullptr for "not found"
    Link* next() const { return succ; }
    Link* previous() const { return prev; }

   private:
    Link* prev;
    Link* succ;
};

Link* Link::insert(Link* n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;
    n->succ = this;            // this object comes after n
    if (prev) prev->succ = n;  // n comes after what used to be this object's predecessor
    n->prev = prev;            // this object's predecessor becomes n's predecessor
    prev = n;                  // n becomes this object's predecessor
    return n;
}

Link* Link::add(Link* n)  // insert n after this object; return n
{
    if (n == nullptr) return this;
    if (this == nullptr) return n;
    n->prev = this;            // this object comes before n
    if (succ) succ->prev = n;  // n comes before what used to be this object's successor
    n->succ = succ;            // this object's successor becomes n's successor
    succ = n;                  // n becomes this object's successor
    return n;
}

Link* Link::erase() {
    if (this == nullptr) return nullptr;
    if (succ) succ->prev = prev;
    if (prev) prev->succ = succ;
    return succ;
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
    const Link* p = this;
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
            p2->erase();
            greek_gods = greek_gods->insert(p2);
        }

        print_all(norse_gods);
        cout << "\n";

        print_all(greek_gods);
        cout << "\n";

        // test other operations
        // cout << greek_gods->advance(3)->advance(-2)->previous()->advance(2)->next()->value << '\n';

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}