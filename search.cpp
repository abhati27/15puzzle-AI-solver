#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<set>
#include<map>
#include<stack>
#include <time.h>
using namespace std;

int inc=0;

class FifteenPuzzle{
    private:
    vector<int> board;
    vector<int> goal={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    vector<char> actions = {'L', 'U', 'R', 'D'};

    //takes a vector representing the current state of a sliding puzzle game and returns the index of the blank tile.
    int blank_pos(vector<int> state) {
        int i = 0;
        for (int val : state) {
            if (val == 0) {
                return i;
            }
            i++;
        }
        return -1;
    }

    public:

    // Default constructor
    FifteenPuzzle(){}

    //initializes the internal board of a sliding puzzle game object using the input vector passed to the constructor.
    FifteenPuzzle(vector<int> board_passed){
        for (int val : board_passed) {
        board.push_back(val);
        }
    }

    //validates if the current state of puzzle matches the goal state by comparing
    // each element of the state vector with the corresponding element of a goal vector.
    bool winCondition(vector<int> state){
        for(int i=0; i<16; i++){
            if(state[i]!=goal[i]){
                return false;
            }
        }
        return true;
    }

    //determines the possible actions (represented by characters) that can be taken from the current 
    //puzzle, by checking which directions are not blocked by the edges of the board, and returns them as a vector.
    vector<char> possible_actions(vector<int> state){
        vector<char> all_act;
        int L=0;
        int U=0;
        int R=0;
        int D=0;
        int val = blank_pos(state);
        if(val>11){
            D=1;
        }
        if(val%4==0){
            L=1;
        } 
        if(val<4){
            U=1;
        }
        if(val%4==3){
            R=1;
        }

        if(L==0){
            all_act.push_back(actions[0]);
        }
        if(U==0){
            all_act.push_back(actions[1]);
        }
        if(R==0){
            all_act.push_back(actions[2]);
        }
        if(D==0){
            all_act.push_back(actions[3]);
        }
        return all_act;
    }



    //swaps the blank tile with an adjacent tile in the specified 
    //direction (left, right, up, or down) in puzzle 
    //vector, and returns the resulting new state vector.
    vector<int> swap(const char action, const vector<int>& state) {
        vector<int> new_state = state;
        const int pos = blank_pos(new_state);
        // Swap tiles based on the input action
        switch (action) {
            case 'L': {
                if (pos % 4 != 0) {
                    std::swap(new_state[pos - 1], new_state[pos]);
                }
                break;
            }
            case 'R': {
                if (pos % 4 != 3) {
                    std::swap(new_state[pos + 1], new_state[pos]);
                }
                break;
            }
            case 'U': {
                if (pos >= 4) {
                    std::swap(new_state[pos - 4], new_state[pos]);
                }
                break;
            }
            case 'D': {
                if (pos <= 11) {
                    std::swap(new_state[pos + 4], new_state[pos]);
                }
                break;
            }
        } 
        return new_state;
    }

    //Heuristic algo that calculates the misplaced tiles
    int mis_Tiles(vector<int> state, int path_length){
        int sumDiff=0;
        for(int i=0; i<16; i++){
            int goal_pos = -1;
            for(int j=0; j<16; j++){
                if(goal[j] == state[i]){
                    goal_pos = j;
                    break;
                }
            }
            if(goal_pos != i){
                sumDiff++;
            }
        }
        return sumDiff;
    }

    // manhattan distance algorithm
   int mandistalgo(vector<int> state) {
    int sumDist = 0; // total manhattan distance between current state and goal state
    for (int i = 0; i < 16; i++) {
        int index; // index of the current tile in the current state
        for (int j = 0; j < 16; j++) {
            if (state[j] == goal[i]) {
                index = j;
            }
        }
        // Calculate the manhattan distance between the current tile and its goal position
        sumDist += abs((index / 4) - (i / 4)) + abs((index % 4) - (i % 4));
    }
    return sumDist;
}


};

// Global Object
FifteenPuzzle a;

// Custom comparator
class comp {
public:

    bool operator()(vector<int> const& lhs, vector<int> const& rhs) const {
        return a.mandistalgo(lhs)>a.mandistalgo(rhs);
    }
};


// This function implements the Iterative Deepening A* (IDA*) search algorithm
// It recursively searches for the minimum cost to reach the goal state of the puzzle
// Returns the minimum cost to reach the goal state or -1 if the goal state is found
int idSearch(stack<pair<vector<int>, char>>& stateStack, char prevMove, int pathCost, int& threshold, FifteenPuzzle& puzzle){
    // Get the current state of the puzzle and calculate the heuristic value
    vector<int> currentState = (stateStack.top()).first;
    int f = pathCost + puzzle.mandistalgo(currentState);
    // If the heuristic value exceeds the threshold, return the value
    if(f > threshold){
        return f;
    }
    // If the goal state is found, return -1
    if(puzzle.winCondition(currentState)){
        return -1;
    }
    // Initialize the minimum cost to a very large value
    int minCost = INT_MAX;
    // Get the list of possible actions for the current state
    vector<char> actions = puzzle.possible_actions(currentState);
    // Iterate through the list of possible actions
    for(auto action : actions){
        // Generate a new state by performing the action
        vector<int> newState = puzzle.swap(action, currentState);
        // If the previous and current moves are opposite, skip the current move
        if((prevMove == 'L' && action == 'R') || (prevMove == 'R' && action == 'L') || (prevMove == 'U' && action == 'D') || (prevMove == 'D' && action == 'U')){
            continue;
        }
        // Push the new state and action onto the state stack
        stateStack.push(make_pair(newState, action));
        // Increment the number of nodes expanded
        inc++;
        // Recursively call the idSearch function with the new state and action
        int tempCost = idSearch(stateStack, action, pathCost+1, threshold, puzzle);
        // If the goal state is found, return -1
        if(tempCost == -1){
            return -1;
        }
        // Update the minimum cost if necessary
        if(tempCost < minCost){
            minCost = tempCost;
        }
        // Pop the current state and action from the stack
        stateStack.pop();
    }
    // If the minimum cost was not updated, return the heuristic value
    if(minCost == INT_MAX){
        return f;
    }
    // Return the minimum cost
    return minCost;
}

int idastar(vector<int> initBoard, FifteenPuzzle& thePuzzle){

    // Set the initial threshold to the Manhattan distance of the initial board state
    int threshold = thePuzzle.mandistalgo(initBoard);

    // Initialize a stack to keep track of the visited board states
    stack<pair<vector<int>, char>> visited;

    // Push the initial board state onto the stack with a dummy move
    visited.push(make_pair(initBoard, ' '));

    // Repeat until the solution is found or the search space is exhausted
    while(true){

        // Perform a depth-limited search using the current threshold
        int temp = idSearch(visited, ' ', 0, threshold, thePuzzle);

        // If the solution is found, print the moves and return the number of moves
        if(temp == -1){
            int numMoves = visited.size() - 1; // Subtract 1 for the dummy move
            stack<char> moves;

            // Extract the moves from the stack in reverse order
            while((visited.top()).second != ' '){
                moves.push(visited.top().second);
                visited.pop();
            }

            // Print the moves in the correct order
            cout << "Moves: ";
            while(!moves.empty()){
                cout << moves.top() << " ";
                moves.pop();
            }
            cout << endl;

            return numMoves;
        }

        // If the search space is exhausted, increase the threshold
        threshold = temp;
    }
}


int main(int argc, char** argv){
// Start the timer
clock_t timer = clock();

// Parse the input arguments as a vector of integers representing the initial board state
vector<int> initBoard;
for (int i = 1; i < argc; i++) {
    initBoard.push_back(stoi(argv[i]));
}

// Create a new FifteenPuzzle object with the given initial board state
FifteenPuzzle thePuzzle(initBoard);

// Use IDA* search to solve the puzzle and obtain the number of moves
int numMoves = idastar(initBoard, thePuzzle);

// Print the solution and performance metrics
cout << endl;
cout << "Number of moves: " << numMoves << endl;
cout << "Nodes expanded: " << inc << endl; // `inc` counts the number of nodes expanded in the search
cout << "Time taken: " << (double)(clock() - timer)/CLOCKS_PER_SEC << " seconds" << endl;
cout << "Memory used: " << sizeof(pair<vector<int>,int>) * (numMoves * sizeof(vector<int>)) << " bytes" << endl;


}
