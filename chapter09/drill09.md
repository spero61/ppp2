# Drill 1 to 5 from Chapter 9

## Statement

This drill simply involves getting the sequence of versions of Date to work.
For each version define a Date called today initialized to June 25, 1978.
Then, define a Date called tomorrow and give it a value by copying today into it and increasing its day by one using add_day().
Finally, output today and tomorrow using a << defined as in §9.8.

```cpp
ostream& operator<<(ostream& os, const Date& d) {
    return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
}
```

Your check for a valid date may be very simple. Feel free to ignore leap years.
However, don’t accept a month that is not in the [1,12] range or day of the month that is not in the [1,31] range.
Test each version with at least one invalid date (e.g., 2004, 13, –5).

_Bjarne, Stroustrup.Programming(p.338).Pearson Education.Kindle Edition._

[Chrono.h](https://github.com/spero61/ppp2/blob/main/chapter09/Chrono.h)
[Chrono.cpp](https://github.com/spero61/ppp2/blob/main/chapter09/Chrono.cpp)

## Implementations

1. The version from §9.4.1
   [drill09_01.cpp](https://github.com/spero61/ppp2/blob/main/chapter09/drill09_01.cpp)

2. The version from §9.4.2
   [drill09_02.cpp](https://github.com/spero61/ppp2/blob/main/chapter09/drill09_02.cpp)

3. The version from §9.4.3
   [drill09_03.cpp](https://github.com/spero61/ppp2/blob/main/chapter09/drill09_03.cpp)

4. The version from §9.7.1
   [drill09_04.cpp](https://github.com/spero61/ppp2/blob/main/chapter09/drill09_04.cpp)

5. The version from §9.7.4
   The version from 9.7.4 const member functions

   Comment:
   We have already used const member functions from drill 3 of Chapter 9
   Because ostream& operator<<(ostream& os, const Date& d) requires them.
   Hence, I just skipped this one.

## Thought

I might have added a feature that each month has specific number of days as it is in real world.
(e.g., January: 31 days, June: 30 days)
Also I skipped the leap years which also relevant to the number of days of February.

Implementing those are not infeasible, however, as the author mentioned on page 338,
I would follow Dr. Stroustrup's advice.

> "When we program, we always have to ask ourselves what is good enough for a given application. We usually don’t have the luxury of being able to search “forever” for the perfect solution after we have already found one that is good enough. Search further, and we might even come up with something that’s so elaborate that it is worse than the simple early solution. This is one meaning of the saying **“_The best is the enemy of the good_” (Voltaire).**"

_Bjarne, Stroustrup.Programming(p.338).Pearson Education.Kindle Edition._
