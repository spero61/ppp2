# Chapter 17

### The focus of this chapter and the next two is the design and implementation of the most common and most useful STL container: **vector**.

> **_Chapter 17_** (this chapter): How can we deal with varying amounts of memory? In particular, how can different **vector**s have different numbers of elements and how can a single **vector** have different numbers of elements at different times? This leads us to examine free store (heap storage), pointers, casts, and references.
>
> **_Chapter 18_**: How can we copy **vector**s? How can we provide a subscript operation for them? We also introduce arrays and explore their relation to pointers.
>
> **_Chapter 19_**: How can we have **vector**s with different element types? And how can we deal with out-of-range errors? To answer those questions, we explore the C++ template and exception facilities.
>
> _Bjarne, Stroustrup. Programming (p. 583-584). Pearson Education. Kindle Edition._

## Wisdom

> More philosophically, I am among the large group of computer professionals who are of the opinion that if you lack a basic and practical understanding of how a program maps onto a computer's memory and operations, you will have problems getting a solid grasp of higher-level topics, such as data structures, algorithms, and operating systems.
>
> _Bjarne, Stroustrup. Programming (p. 585). Pearson Education. Kindle Edition._

> - For tiny objects prefer pass-by-value.
> - For functions where _nullptr_ is a valid argument use a pointer parameter (and remember to test for _nullptr_)
> - Otherwise, use a reference parameter
>
> _Bjarne, Stroustrup. Programming (p. 612). Pearson Education. Kindle Edition._

## Postscript

> Why bother with messy low-level stuff like pointers and free store when we can simply use **vector**?
>
> Our favorite reason, however, is simply that you can't really claim to understand computers and programming until you have seen how software meets hardware.
>
> _Bjarne, Stroustrup. Programming (p. 625). Pearson Education. Kindle Edition._
