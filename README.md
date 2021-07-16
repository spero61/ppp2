# Programming: Principles and Practice Using C++ 2nd Edition

## Graphics chapters

### [Chapter 12: A Display Model](./chapter12/README.md)

### [Chapter 13: Graphics Classes](./chapter13/README.md)

### [Chapter 14: Graphics Class Design](./chapter14/README.md)

### [Chapter 15: Graphing Functions and Data](./chapter15/README.md)

### [Chapter 16: Graphical User Interfaces](./chapter16/README.md)

["std_lib_facilities.h" header file for early chapters](https://www.stroustrup.com/Programming/std_lib_facilities.h)

**_std_lib_facilities.h_** can be replaced as below:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
inline void keep_window_open() { char ch; cin>>ch; }
```

## References

[official website for the textbook](https://www.stroustrup.com/programming.html)

[supporting information](https://www.stroustrup.com/programming_support.html)

[Installing FLTK with Visual Studio 2019](https://alf-p-steinbach.github.io/Install-FLTK-for-use-with-Visual-C-/#3-build-the-library-with-visual-studio-2019)

[How to compile FLTK](https://bumpyroadtocode.com/2017/08/29/how-to-install-and-use-fltk-1-3-4-in-visual-studio-2017-complete-guide-2-0-no-cross-contamination)

> **"I simply like C++ as a language for writing elegant and efficient code."**
>
> _Bjarne, Stroustrup. Programming (p. xxvi). Pearson Education. Kindle Edition._

## Code format style

chapter 3-8 : Visual Studio

chapter 9-cwd : Google with indentWidth: 4

## Note

I used FLTK 1.3.6 with Visual Studio 2019 on Windows 10 (20H2)
