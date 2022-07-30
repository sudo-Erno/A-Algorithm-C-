#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

#include "functions.h"

/*
    TODO:
    - [ ] Read the board from .txt file.
    - [x] Make the dimensions of the board global variables.
    - [x] Make a function to print the path.

    Steps:
    - [x] Create board (read it from a .txt file).
    - [x] Each node is a struct {x, y, g, h, is_available}.
    - [x] Get the available neighbours.
    - [x] Evaluate the best one.
    - [x] Move.
    - [x] Loop until condition.

*/

// std::vector<std::string> board;
// std::ifstream myfile("board.txt");

std::vector<std::vector<int>> board = {
    {0, -1, 0, 0, 0},
    {0, -1, 0, 0, 0},
    {0, -1, 0, 0, 0},
    {0, -1, 0, 0, 0},
    {0, -1, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

// Get board dims
int NUM_ROWS = board.size();
int NUM_COLS = board.at(0).size();

// Set the initial position of the agent and the goal
int init[2] = {0, 0};
int goal[2] = {3, 1};

// Store the selected nodes
std::vector<Node> path;

int main(){

    Node actual_state;
    std::vector<std::vector<Node>> nodes = initialize_nodes(board, NUM_ROWS, NUM_COLS, init, goal);

    actual_state.x = init[0];
    actual_state.y = init[1];

    int iter_max = 25;
    int iter_num = 0;
    bool reached_end = false;

    while((iter_num < iter_max) || reached_end){
        iter_num += 1;
        path.push_back(actual_state);
        
        std::vector<std::vector<int>> available_neighbours = get_available_neighbours(nodes, actual_state, NUM_ROWS, NUM_COLS, path);
        
        actual_state = select_next_state(nodes, available_neighbours);

        if(actual_state.x == goal[0] && actual_state.y == goal[1]){
            reached_end = true;
            path.push_back(actual_state);
            break;
        }
    }

    if (reached_end) std::cout<<"\nGoal reached at iteration number: "<<iter_num<<std::endl;
    else std::cout<<"\nGoal not reached :(\n";

    print_path(path);

    return 0;
}