# Random one file "projects" made with C++ (C++11)

Every one of them can be compiled and run like this:
```
clang++ -std=c++11 -o prog.out FILE
chmod +x prog.out
./prog.out
```

### monty_hall.cpp

A "game" that visualies [Monty Hall problem](https://en.wikipedia.org/wiki/Monty_Hall_problem).
If we always choose to not change our initial decision, we win ~1/3 of the time:

```
Pick a door (1-3): Host opens the door number 2.
"Nothing here. I'm giving you last chance to change your mind."
Switch to door number 3?: y
You lose. Win rate: 0.332031 (W/(W+L): 340/1024)
```

On the contrary, if we always agree to pick another door that gamemaster suggests, we win ~2/3 of the time:

```
Pick a door (1-3): Host opens the door number 3.
"Nothing here. I'm giving you last chance to change your mind."
Switch to door number 2?: y
You won! Win rate: 0.671875 (W/(W+L): 688/1024)
```

### longest_word_wo_asc_desc.cpp

Finds longest words that lack any descenders or ascenders (symbols like 'q' or 'h'), and makes top out of them. 
Usage:
```
./prog.out TOP_SIZE FILE
```
Example:
```
./prog.out 2 words_479k.txt
Longest words without ascenders/descenders (top 2):
[16 letters: 2 words]:
nonerroneousness
overnumerousness
[15 letters: 4 words]:
nonsensuousness
nonvenomousness
overnervousness
unerroneousness
```

### TicTacToe.cpp

Simple tic-tac-toe game. `BOARD_SIZE` macro may be tweaked to change the board size.
Here's how the gameplay looks like (fire):
```
    1   2   3
 1  o |   |
   ---+---+---
 2    |   | x
   ---+---+---
 3    |   |

Enter coords for player [x] (row, column):
```

### fuzzy_date.cpp

Formats a string to date (if it's possible):
```
"12 3 2000" -> "December 3, 2000"
"12-3-2000" -> "December 3, 2000"
"12 random data 3 more random data! 2000 even more..." -> "December 3, 2000"
"2.29.1999" -> "null" (no February 29 in a non-leap year)
```

### inserter_visualiser.cpp

Visualises the work of `std::inserter`.
```
Enter a range (inclusive): 3 7
[0][0][0][0][0][0][0][0][0][0][-]
               ^
[0][0][0][0][0][3][0][0][0][0][0][-]
                  ^
[0][0][0][0][0][3][4][0][0][0][0][0][-]
                     ^
[0][0][0][0][0][3][4][5][0][0][0][0][0][-]
                        ^
[0][0][0][0][0][3][4][5][6][0][0][0][0][0][-]
                           ^
[0][0][0][0][0][3][4][5][6][7][0][0][0][0][0][-]
                              ^
```

### txt_file_analyzer.cpp

Simple utility to count the number of lines (both empty and not), characters (incl. whitespaces) and whitespaces in a file.
Usage:
```
./prog.out FILE
```

Example:
```
./prog.out random_text.txt
Line count: 12 (incl. 5 empty lines)
Character count (incl. whitespaces): 1392
Whitespace count: 235
```
