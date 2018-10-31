# Search Algorithms

Containing Implementaion of various search algorithm in C++.

## Running the tests

```
$ g++ file_name.cpp -o file_name
$ file_name < file_name.txt
```
Additional files are present with the name file_name.* .

## Contents

1. [Depth First Search](https://github.com/malviyanshiv/ai/tree/master/searching_graph/README.md)
2. [Breadth First Search](https://github.com/malviyanshiv/ai/tree/master/toy_problems/README.md)
3. [Branch and Bound Search](https://en.wikipedia.org/wiki/Branch_and_bound)
5. [Best First Search](https://en.wikipedia.org/wiki/Best-first_search)
4. [Hill Climbing Search](https://en.wikipedia.org/wiki/Hill_climbing)
6. [A* Search](https://en.wikipedia.org/wiki/A*_search_algorithm)
7. [Weighted A* Search](https://en.wikipedia.org/wiki/A%2a_search_algorithm#Bounded_relaxation)
8. [Iterative Deepening A* Search](https://en.wikipedia.org/wiki/Iterative_deepening_A*)
9. [Recursive Best First Search](https://www.aaai.org/ocs/index.php/AAAI/AAAI15/paper/viewFile/10008/9352)

## Creating our own Map for the search

For building your own map the file should have content as:
* First line should contain if you are the give nodes as alphabets( upper case only ) or as integers [A or I].
* Then you should specify the number of nodes (**N**).
* If you are using search algorithms like *Best First Search, Hill Climbing, A star, RBFS, Weighted A star or IDA star*, then next **N** line should specify the coordinates of each nodes as x y pair for calculating the heuristics value.
* Next line should contain number of Edges (**M**).
* If building for *Best first search, Hill Climbing, A star, RBFS, Weighted A star, or IDA star* then next **M** lines should contains triplets specifying the start vertex, end vertex and the weight, otherwise only the start vertex and end vertex.
* Last line should specify the source node and destination node.
