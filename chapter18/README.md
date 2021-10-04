# Chapter 18

## Wisdom

> When implementing the assignment , you could consider simplifying the code by freeing the memory for the old elements before creating the copy, but it is usually a very good idea not to throw away information before you know that you can replace it.
>
> _Bjarne, Stroustrup. Programming (p. 636). Pearson Education. Kindle Edition._

> I've been thinking about that and there is one clear answer, constructors and destructors. The ways a constructor can establish the environment for the use of the type for object and the destructor that cleans up any messes at the end of it. That is the key to C++.
>
> That's why we don't have to use garbage collection, that's how we can get predictable performance, that's how we can get the minimal overhead in many many cases and have really clean types.

[_Bjarne Stroustrup, Lex Fridman Podcast #48_](https://youtu.be/uTxRF5ag27A?t=5298)
