# exercise10_10.cpp

## Statement

Add a command from x to the calculator from Chapter 7 that makes it take input from a file x.
Add a command to y to the calculator that makes it write its output \(both standard output and error output\) to file y.
Write a collection of test cases based on ideas from §7.3 and use that to test the calculator.
Discuss how you would use these commands for testing.

## Implementations

- [exercise10_10_input.txt](./exercise10_10_input.txt)

- [exercise10_10.cpp](./exercise10_10.cpp)

- [exercise10_10_output.txt](./exercise10_10_output.txt)

## Thought

Duh, calculator again. I chose exercise07_05.cpp for simplicity. After a couple of hours of me digging int to the problem, I found out that I missed I have not corrected bugs from drill07.cpp. It's a good thing that now I can tell why parentheses did not work appropriately during chapter 7. \(It worked well in chapter 6.\)

I did not implement commends "from x" nor "to y."
As always, a quote from the author sheds light on the problem.

> It is most important to avoid “feature creep” early in a project. Instead, always first build a simple version, implementing the essential features only. Once you have something running, you can get more ambitious. It is far easier to build a program in stages than all at once.
>
> _Bjarne, Stroustrup. Programming (p. 188). Pearson Education. Kindle Edition._

Lastly, this kind of 'testing program' is helpful. Now we do not have to enter mathematical expressions line by line. We can make test cases in a text file then run the program. It might be a huge help when as we revise the program. Then test the features all at once, in a blink of time.
