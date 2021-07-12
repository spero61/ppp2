// Define an abstract class and try to define an object of that type.
// What happens?

// A: Compile error occurrs! see below:
// error: cannot declare variable 'herb' to be of abstract type 'Plant'
// note: because the following virtual functions are pure within 'Plant':

#include "std_lib_facilities.h"

class Plant {
   public:
    virtual void photosynthesis() = 0;
    virtual void cellular_respiration() = 0;
};

int main() {
    try {
        Plant herb;  // Compile error!

        return 0;
    } catch (exception& e) {
        cerr << e.what() << '\n';
        return 1;
    } catch (...) {
        cerr << "...Exception Occurred\n";
        return 2;
    }
}