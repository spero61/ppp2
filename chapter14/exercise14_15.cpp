// Define a class Iterator with a pure virtual function next() that returns a double* (see Chapter 17).
// Now derive Vector_iterator and List_iterator from Iterator so that next() for a Vector_iterator
// yields a pointer to the next element of a vector<double> and List_iterator does the same for a list<double>.
// You initialize a Vector_iterator with a vector<double> and the first call of next() yields a pointer to its first element,
// if any. If there is no next element, return 0.

// Test this by using a function void print(Iterator&) to print the elements of a vector<double> and a list<double>.

#include "std_lib_facilities.h"

class My_Iterator {
   public:
    My_Iterator& operator=(const My_Iterator&) = delete;
    virtual double* next() = 0;  // "pure" virtual function
    void begin() { index = 0; }  //https://www.cplusplus.com/reference/iterator/begin/

   protected:
    int index;
};

class Vector_iterator : public My_Iterator {
   public:
    Vector_iterator(vector<double>& v_arg) : v{v_arg} { index = 0; }
    double* next() override;

   private:
    vector<double> v;
};

double* Vector_iterator::next() {
    if (v.size() == 0 || index > v.size() - 1) {  // when there is no next element
        return 0;
    } else {
        return &v[index++];  // return &v[index] then index++
    }
}

class List_iterator : public My_Iterator {
   public:
    List_iterator(list<double>& lst_arg) : lst{lst_arg} { index = 0; }
    double* next() override;

   private:
    list<double> lst;
};

// https://www.cplusplus.com/reference/list/list/
// Of course you may use "list<double>::iterator" then it is going to be far simpler
// but I tried not to use it for practice purpose as this exercise is to implement the "Iterator" by one's self
double* List_iterator::next() {
    if (index == 0) {                                        // when List_iterator is pointing at the first element of the list
        index++;                                             // move the pointer(here, index) to the next element
        return (lst.size() != 0) ? &lst.front() : 0;         // check if the lst is empty it it is empty return 0 instead
    } else if (lst.size() == 0 || index > lst.size() - 1) {  // when there is no next element
        return 0;
    } else {                               // this code is to check "next" element of the list
        list<double> tmp = lst;            // copy list<double> list to tmp for temporary use
        for (int i = 0; i < index; ++i) {  // delete the number of elements (eqauls to index) of the list from the front
            tmp.pop_front();
        }
        index++;              // move the pointer(here, index) to the next element
        return &tmp.front();  // this element is equivalent to lst[index] as if the List has subscript
    }
}

// from the iterator index(pointer), print the rest of elements in sequence
void print(My_Iterator& itr) {
    double* ptr{itr.next()};
    int idx{0};
    while (ptr != 0) {
        cout << *ptr << '\n';
        ptr = itr.next();
    }
}

int main() {
    try {
        cout << "<Vector_iterator>\n";
        constexpr double PI{3.141592};
        vector<double> numbers;
        for (int i = 1; i <= 4; ++i) {
            numbers.push_back(i * PI);
        }

        Vector_iterator v_itr(numbers);
        for (int i = 0; i < 3; ++i) {
            double tmp = *v_itr.next();
            cout << tmp << '\n';
        }
        cout << "\n(returns an iterator pointing to the first element in the sequence)\n";

        v_itr.begin();
        print(v_itr);

        cout << "\n<List_iterator>\n";
        list<double> elems;
        elems.push_back(2021);
        elems.push_back(7);
        elems.push_back(12);
        elems.push_back(14.16);

        List_iterator lst_itr(elems);
        print(lst_itr);

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}
