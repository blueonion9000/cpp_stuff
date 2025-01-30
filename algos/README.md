# algos

Not very useful utility by itself. The code has been split into several files to show basic usage of header files. It also showcases some methods from `<algorithm>` library, as well as usage of lambda functions.

### Building
```
clang++ -std=c++11 -o prog.out main.cpp func.cpp
```

### Output
```
Before:
bravo delta bravo bravo delta alpha delta alpha bravo delta bravo bravo delta alpha delta alpha reallylongword impossiblylongword absurdlylongword
Without duplicate words:
absurdlylongword alpha bravo delta impossiblylongword reallylongword
Filtered by length:
alpha bravo delta
```