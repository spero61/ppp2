// Define a class My_Fct

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class My_Fct : public Shape {
   public:
    My_Fct(Fct* f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);
    void reset(Fct* f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25);

   private:
    Fct* f_val;
    double r1_val;
    double r2_val;
    Point orig_val;
    int count_val;
    double xscale_val;
    double yscale_val;
};

My_Fct::My_Fct(Fct f, double r1, double r2, Point orig, int count,
               double xscale, double yscale) : f_val{f}, r1_val{r1}, r2_val{r2}, orig_val{orig}, count_val{count}, xscale_val{xscale}, yscale_val{yscale} {
}

void My_Fct::reset(Fct f, double r1, double r2, Point orig, int count,
                   double xscale, double yscale) {
    f_val = f;
    r1_val = r1;
    r2_val = r2;
    orig_val = orig;
    count_val = count;
    xscale_val = xscale;
    yscale_val = yscale;
}