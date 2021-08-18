# exercise 11_09.md

## answer

Consider the case below:

```cpp
const Link* curriculum = new const Link{"CS50"};
const Link* test = curriculum->find("CS50");  // <- this requires const Link* find()
```

To be able to deal with the case above, two versions of find() are needed.
