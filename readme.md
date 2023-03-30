# 15 Puzzle Solver using IDA* Algorithm
This project implements the IDA* (Iterative Deepening A*) search algorithm to solve the popular 15 Puzzle game, also known as the sliding tile puzzle. The program is written in C++ and uses two different heuristics: Manhattan distance and misplaced tiles. The optimal solution provided by the program includes the sequence of moves required to reach the goal state.

## Requirements
C++ compiler with support for C++11 (e.g., g++)

## Compilation
To compile the program, open your terminal and navigate to the project folder. Then, run the following command:

g++ -std=c++11 search.cpp -o solver

This will create an executable named solver in the project folder.

## Usage
To run the program with a specific puzzle configuration, use the following command in your terminal:

./solver 1 2 0 4 6 7 3 8 5 9 10 12 13 14 11 15

Replace the numbers with your desired puzzle configuration, where 0 represents the empty tile. Make sure to provide exactly 16 numbers, as the puzzle is a 4x4 grid. The program will then output the optimal sequence of moves to solve the puzzle, as well as the number of moves and the time taken.

## Heuristics
This program uses two different heuristics to guide the search:

Manhattan distance: The sum of the distances of each tile from its correct position in the goal state, measured as the number of horizontal and vertical moves required.
Misplaced tiles: The number of tiles that are not in their correct position in the goal state.
The IDA* algorithm combines the heuristic function with the depth of the search tree to find the optimal solution efficiently.

## Example
Here's a sample input and output for the program:

./solver 1 2 0 4 6 7 3 8 5 9 10 12 13 14 11 15

Output:

Optimal solution found!

Sequence of moves: RDLDRRULDLURRDLURDLURRDLUR

Number of moves: 29

Time taken: 0.32 seconds

This means that the optimal solution for the given configuration requires 29 moves and the program found the solution in 0.32 seconds. The sequence of moves is provided using letters: 'R' for right, 'L' for left, 'U' for up, and 'D' for down.

## License
This project is released under the MIT License. For more information, please refer to the LICENSE file.
