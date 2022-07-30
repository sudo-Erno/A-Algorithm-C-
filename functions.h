#include <iostream>
#include <vector>
#include <cstdlib>

#include "node.h"

int heuristic(Node node, int pos[2]){
    int x0 = node.x;
    int y0 = node.y;

    int xf = pos[0];
    int yf = pos[1];

    return abs(x0 - xf) + abs(y0 - yf);
}

std::vector<std::vector<Node>> initialize_nodes(std::vector<std::vector<int>> board, int nrows, int ncols, int init[2], int goal[2]){
    std::vector<Node> cols;
    std::vector<std::vector<Node>> rows;

    for(int r=0; r<nrows; r++){
        for(int c=0; c<ncols; c++){
            Node node;
            node.x = c;
            node.y = r;
            // node.g = heuristic(node, init);
            node.g = 1; // 1 since every move cost 1
            node.h = heuristic(node, goal);
            node.is_available = (!board[r][c]) ? true : false;
            // if(node.x == init[0] && node.y == init[1]) node.used = true;

            cols.push_back(node);
        }
        rows.push_back(cols);
        cols.erase(cols.begin(), cols.end());
    }

    return rows;
}

bool node_in_path(Node posible_node, std::vector<Node> path){
    for(auto node: path){
        if(node.x == posible_node.x && node.y == posible_node.y) return true;
    }
    return false;
}

std::vector<std::vector<int>> get_available_neighbours(std::vector<std::vector<Node>> nodes, Node actual_pos, int nrows, int ncols, std::vector<Node> path){
    int x = actual_pos.x;
    int y = actual_pos.y;

    std::vector<std::vector<int>> posible_future_states {
        {x, y - 1}, // Up
        {x + 1, y}, // Right
        {x, y + 1}, // Down
        {x - 1, y} // Left
    };

    std::vector<std::vector<int>> neighbours;

    for(auto next_state: posible_future_states){

        if (next_state[0] >= 0 && next_state[0] < ncols && next_state[1] >= 0 && next_state[1] < nrows){ // Check if neigh. is inside maze.
            for(auto rows: nodes){
                for(auto node: rows){
                    if(node.x == next_state[0] && node.y == next_state[1])// iterate over the nodes and check if it's available to move
                        if(node.is_available){
                            if(!node_in_path(node, path)) neighbours.push_back(next_state);
                        }  
                }
            }
        }
    }

    return neighbours;
}

Node select_next_state(std::vector<std::vector<Node>> nodes, std::vector<std::vector<int>> neighbours){
    
    int lower_cost;
    bool is_first = true;
    int cost = 0;
    
    Node next_state;
    
    for(auto neighbour: neighbours){
        for(auto rows: nodes){
            for(auto node: rows){
                if(node.x == neighbour[0] && node.y == neighbour[1]){ // Get the corresponding node
                    cost = node.g + node.h;

                    if(is_first){
                        lower_cost = cost;
                        next_state = node;
                        is_first = false;
                    }
                    else{
                        if(cost < lower_cost) next_state = node;
                    }
                }
            }
        }
    }
    return next_state;
}

void print_path(std::vector<Node> path){
    
    std::cout<<"\nPATH:\n";
    for(auto node: path) std::cout<<"x: "<<node.x<<" y: "<<node.y<<std::endl;

}