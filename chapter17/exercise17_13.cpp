// modify the Link class from §17.10.1 to hold a value of a struct God
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

struct God {
    God(string name_arg, string mythology_arg, string vehicle_arg = "none", string weapon_arg = "none")
        : name{name_arg}, mythology{mythology_arg}, vehicle{vehicle_arg}, weapon{weapon_arg} {}
    string name;
    string mythology;
    string vehicle;
    string weapon;
};

bool operator==(const God& a, const God& b) {
    return (a.name == b.name && a.mythology == b.mythology && a.vehicle == b.vehicle && a.weapon == b.weapon);
}
bool operator!=(const God& a, const God& b) {
    return !(a == b);
}

ostream& operator<<(ostream& os, const God& g) {
    return os << "{ " << g.name << ", " << g.mythology << ", " << g.vehicle << ", " << g.weapon << " }";
}

class Link {
   public:
    God god;
    Link(const God& g, Link* p = nullptr, Link* s = nullptr)
        : god{g}, prev{p}, succ{s} {}
    Link* insert(Link* n);                    // insert n before this object
    Link* add(Link* n);                       // insert n after this object
    Link* erase();                            // remove this object from list; return this object's successor
    Link* find(const string& s);              // find s in list; return nullptr for "not found"
    const Link* find(const string& s) const;  // find s in const list; return nullptr for "not found"
    const Link* advance(int n) const;         // move n positions in list; return nullptr for "not found"
    Link* add_ordered(Link* n);               // places its new element in its correct lexicographical position
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
        if (p->god.name == s) return p;
        // if (strcmp(p->god.name.c_str(), s.c_str()) == 0) return p;
        p = p->succ;
    }
    return nullptr;
}

const Link* Link::find(const string& s) const {
    const Link* p = this;
    while (p) {
        if (p->god.name == s) return p;
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

Link* Link::add_ordered(Link* n) {
    // To do
    return nullptr;
}

void print_all(Link* p) {
    if (!p) {
        cout << "This Link* list is empty";
    } else {
        cout << "{\n";
        while (p) {
            cout << "    " << p->god;
            if (p = p->next()) cout << '\n';
        }
        cout << "\n}";
    }
}

int main() {
    try {
        // make gods list from three mythologies
        Link* gods = new Link{God{"Zeus", "Greek", "none", "lightning"}};
        gods = gods->insert(new Link{God{"Hera", "Greek"}});
        gods = gods->insert(new Link{God{"Poseidon", "Greek"}});
        gods = gods->insert(new Link{God{"Demeter", "Greek"}});
        gods = gods->insert(new Link{God{"Athena", "Greek"}});
        gods = gods->insert(new Link{God{"Apollon", "Greek"}});
        gods = gods->insert(new Link{God{"Artemis", "Greek"}});
        gods = gods->insert(new Link{God{"Ares", "Greek"}});
        gods = gods->insert(new Link{God{"Aphrodite", "Greek"}});
        gods = gods->insert(new Link{God{"Hermes", "Greek"}});
        gods = gods->insert(new Link{God{"Hephaistos", "Greek"}});
        gods = gods->insert(new Link{God{"Hestia", "Greek"}});
        gods = gods->insert(new Link{God{"Odin", "Norse", "Sleipner", "Gungnir"}});
        gods = gods->insert(new Link{God{"Frigg", "Norse"}});
        gods = gods->insert(new Link{God{"Baldr", "Norse"}});
        gods = gods->insert(new Link{God{"Freyja", "Norse"}});
        gods = gods->insert(new Link{God{"Thor", "Norse", "Chariot", "Mjolnir"}});   // it's Mjölnir though
        gods = gods->insert(new Link{God{"Loki", "Norse", "none", "Laevatein"}});    // Lævateinn
        gods = gods->insert(new Link{God{"Tyr", "Norse"}});                          // Týr
        gods = gods->insert(new Link{God{"Ukko", "Finnish", "none", "lightning"}});  // Ukko on ylijumala!
        gods = gods->insert(new Link{God{"Ahti", "Finnish"}});
        gods = gods->insert(new Link{God{"Kuu", "Finnish"}});
        gods = gods->insert(new Link{God{"Pekko", "Finnish"}});
        gods = gods->insert(new Link{God{"Perkele", "Finnish", "none", "thunder"}});
        gods = gods->insert(new Link{God{"Tapio", "Finnish"}});
        gods = gods->insert(new Link{God{"Mielikki", "Finnish"}});
        cout << "~ gods from three mythologies ~\n";
        print_all(gods);
        cout << '\n';

        // this C-style array is used for loop when moving elements (deliberately did not use vector for practice)
        string norse_names[] = {"Odin", "Frigg", "Baldr", "Freyja", "Thor", "Loki", "Tyr"};
        string greek_names[] = {"Zeus", "Hera", "Poseidon", "Demeter", "Athena", "Apollon", "Artemis", "Ares", "Aphrodite", "Hermes", "Hephaistos", "Hestia"};
        string finnish_names[] = {"Ukko", "Ahti", "Kuu", "Pekko", "Perkele", "Tapio", "Mielikki"};

        // calculate the element size of the array, respectively
        const int norse_size{(sizeof(norse_names) / sizeof(string))};      // 7
        const int greek_size{(sizeof(greek_names) / sizeof(string))};      // 12
        const int finnish_size{(sizeof(finnish_names) / sizeof(string))};  // 7

        // Norse gods
        Link* norse_gods{nullptr};
        for (int i = 0; i < norse_size; ++i) {
            norse_gods = norse_gods->insert(new Link{gods->find(norse_names[i])->god});
            gods->find(norse_names[i])->erase();
            // greek_gods = greek_gods->add_ordered(tmp);
            // gods-> find(greek_names[i])->erase();
        }
        cout << "\n\n~ Norse gods ~\n";
        print_all(norse_gods);

        // Greek gods
        Link* greek_gods{nullptr};
        for (int i = 0; i < greek_size; ++i) {
            greek_gods = greek_gods->insert(new Link{gods->find(greek_names[i])->god});
            gods->find(greek_names[i])->erase();
            // greek_gods = greek_gods->add_ordered(tmp);
            // gods-> find(greek_names[i])->erase();
        }
        cout << "\n\n~ Greek gods ~\n";
        print_all(greek_gods);

        // Finnish gods
        Link* finnish_gods{nullptr};
        for (int i = 0; i < finnish_size; ++i) {
            finnish_gods = finnish_gods->insert(new Link{gods->find(finnish_names[i])->god});
            gods->find(finnish_names[i])->erase();
            // finnish_gods = finnish_gods->add_ordered(tmp);
            // gods-> find(finnish_names[i])->erase();
        }
        cout << "\n\n~ Finnish gods ~\n";
        print_all(finnish_gods);

        // check whether gods list is empty
        gods = gods->erase();  // this is to remove the last element of the gods (REVIEW: why this process is neccessary to empty the Link* list?)
        cout << "\n\n";
        print_all(gods);

        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        std::cerr << "...Exception Occurred\n";
        return 2;
    }
}