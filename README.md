# shortestpath
Just a thing to find the shortest path written in C

## Installation

Just type `make`, or if you know how to use gcc, just use that.

## Usage

This is an example input nodes file (or see example\_nodes file)

```
# this is a comment, lines beginning with a # will be ignored
A:B=2,C=4
B:A=2,C=6
C:B=7,A=2

```

The file must end with a newline, if it does not, then your last node will be skipped.  Most text editors will put a newline in for you, but if your editor does not, you must do it yourself.

Then run the program with `./main <node_file>`
