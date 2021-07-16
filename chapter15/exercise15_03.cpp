// Modify My_Fct with an extra argument
// reference: https://en.cppreference.com/w/cpp/language/template_parameters

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities.h"

class My_Fct : public Shape {
   public:
    My_Fct(Fct* f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25, double coef = 1);
    void reset(Fct* f, double r1, double r2, Point orig, int count = 100, double xscale = 25, double yscale = 25, double coef = 1);

   private:
    Fct* f_val;
    double r1_val;
    double r2_val;
    Point orig_val;
    int count_val;
    double xscale_val;
    double yscale_val;
    double coef_val;  // extra argument: coefficient value
};

My_Fct::My_Fct(Fct f, double r1, double r2, Point orig, int count,
               double xscale, double yscale, double coef) : f_val{f}, r1_val{r1}, r2_val{r2}, orig_val{orig}, count_val{count}, xscale_val{xscale}, yscale_val{yscale}, coef_val{coef} {
}

void My_Fct::reset(Fct f, double r1, double r2, Point orig, int count,
                   double xscale, double yscale, double coef) {
    f_val = f;
    r1_val = r1;
    r2_val = r2;
    orig_val = orig;
    count_val = count;
    xscale_val = xscale;
    yscale_val = yscale;
    coef_val = coef;
}