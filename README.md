# shortestpath
Just a thing to find the shortest path written in C

## Installation

Just type `make`, or if you know how to use gcc, just use that.

## Usage

![](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3b/Shortest_path_with_direct_weights.svg/250px-Shortest_path_with_direct_weights.svg.png)

This is an example input file for the above graph.

```
# this is a comment, lines beginning with a # will be ignored
# the starting node must be first
A:B=4,C=2
B:C=5,D=10
C:E=2
D:F=11
E:D=4
# this is the ending node. if it has no neighbors, it can be on a line with itself and a colon
F:
```

The file must end with a LF (`\n`), if it does not, then your last node will be skipped.  Most text editors will put a newline in for you, but if your editor does not, you must do it yourself.

Then run the program with `./main <node_file>`
