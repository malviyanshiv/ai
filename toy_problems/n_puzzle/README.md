# Welcome to N-Puzzle
The python program to solve the your choice of n-puzzle problem using A* search and manhattan distance heuristic internally.

## Initial and Goal States
The initial state is generated randomly but you can also specify it. The default **goal state** is
```
   +---+---+---+
   |   | 1 | 2 |
   +---+---+---+
   | 3 | 4 | 5 |
   +---+---+---+
   | 6 | 7 | 8 |
   +---+---+---+
```
but you can also specify your goal state.

## Dependencies
Requires Python3. No additional dependencies.

## Running
```
>> python n_puzzle.py -h
   usage: n_puzzle.py [-h] [-n N] [-s S] [-g G]
   
   This is a automatic solver for n-Puzzle toy game using A* search and manhattan
   heuristic.
   
   optional arguments:
     -h, --help  show this help message and exit
     -n N        Specify size of problem [A problem of size n contains n*n
                 blocks]
     -s S        This is the initial configuration of board
     -g G        This is the goal configuration to reach
```

##  Specifying initial and goal state
The states are given as a list of comma-seperated values with number **0** representing the *blank tile*.
For initial state like:
```
	+---+---+---+
	| 1 | 4 | 2 |
	+---+---+---+
	| 6 | 3 | 5 |
	+---+---+---+
	| 7 | 8 |   |
	+---+---+---+
>> python n_puzzle.py -n 3 -s 1,4,2,6,3,5,7,8,0
```

## Contributing

1. Fork it (<https://github.com/malviyanshiv/ai>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
