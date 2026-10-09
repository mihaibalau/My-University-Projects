# Assembly

Homework from the computer architecture course, written in NASM for 32-bit Windows and linked against `msvcrt.dll` (`printf`, `scanf`, `fopen`, `exit`).

`Homework5.asm` builds a string D from two sources: characters on odd positions in S2, then characters on even positions in S1.

`Homework6.asm` merges two alphabetically sorted strings into one sorted string, the same idea as the merge step of merge sort.

`Homework7.asm` reads an integer from the keyboard and writes it to a text file.

`Homework8.asm` adds two numbers and turns the sum into digits by repeated division.

`Homework9.asm` reads `a` and `b` in base 10 and prints their arithmetic average in base 16.

`Homework10.asm` opens `read.txt` and counts how many times `y` and `z` appear.

`Homework11` is two modules. `main.asm` reads a string of unsigned numbers and prints the maximum. `modul.asm` exports `find_maximum_value`, which walks the string and keeps the largest value.

`Homework12` calls assembly from C. `main.c` reads a string of 8-bit binary groups separated by commas. `modul.asm` converts each group to an integer. `example.asm` is the other exercise from that lab: an `asmConcat` routine that concatenates a string received as a parameter, one read from the keyboard inside the module, and a global string from the C program, using the stdcall stack frame.

Technologies: NASM, x86 assembly, C (for the mixed module in Homework 12).
