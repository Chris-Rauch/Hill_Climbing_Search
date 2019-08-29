//@main.cpp

#ifndef ASTAR
#define ASTAR

#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <list>
#include <cmath>
#include <iterator>
#include "node.h"
using namespace std;

//FUNCTION HEADERS
void randomize(node& board);
void display(const node& board);
bool isGoalState(const node& board);
void calcHeuristic(node& board);
vector<node> getChildren(node& board);


int main() {
    priority_queue<node, std::vector<node>, CompareHeuristic> frontier;
    list<node> visited;
    node board;

    randomize(board);
    calcHeuristic(board);
    frontier.push(board);

    //A*
    while(true) {
        //pop node off frontier
        node temp(frontier.top());
        frontier.pop();
        //display(temp);

        //check goal state
        if(isGoalState(temp)) {
            cout << "\n==== Goal State ====\n";
            display(temp);
            break;
        }
        
        //check if already visited
        bool wasVisited = false;
        list<node>::iterator it;
        for(it = visited.begin(); it != visited.end(); ++it) {
            if(*it == temp) {
                wasVisited = true;
            } 
        }

        if(wasVisited == false) {
            //add to visited
            visited.push_back(temp);
            
            //add children to frontier
            vector<node> children;
            children = getChildren(temp);
            for(short x = 0; x < children.size(); ++x) {
                frontier.push(children[x]);
            }
        }
    }

    return 1;
}

//==== GET_CHILDREN ====
vector<node> getChildren(node& board) {
    int size = sqrt(SIZE);
    vector<node> children;
    
    //check up
    if(board.currPos / size != 0) {
        //create a new node and copy current board state
        node child(board);
        calcHeuristic(board);
        
        //swap the 0 tile with the above tile
        child.value[child.currPos] = board.value[board.currPos - size];
        child.value[child.currPos - size] = board.value[board.currPos];
        child.currPos = board.currPos - size;
        
        //calc new heuristic
        calcHeuristic(child); //h(x)
        child.heuristic += 1; //g(x)
        
        //add to children vector
        children.push_back(child);
    }
  
    //check down
    if(board.currPos / size != (size-1)) {
        //create a new node and copy current board state
        node child(board);
        
        //swap the 0 tile with the above tile
        child.value[child.currPos] = board.value[board.currPos + size];
        child.value[child.currPos + size] = board.value[board.currPos];
        child.currPos = board.currPos + size;
        
        //calc new heuristic
        calcHeuristic(child); //h(x)
        child.heuristic += 1; //g(x)
        
        //add to children vector
        children.push_back(child);
    }

    //check left
    if(board.currPos % size != 0) {
        //create a new node and copy current board state
        node child(board);
        
        //swap the 0 tile with the above tile
        child.value[child.currPos] = board.value[board.currPos - 1];
        child.value[child.currPos - 1] = board.value[board.currPos];
        child.currPos = board.currPos - 1;
        
        //calc new heuristic
        calcHeuristic(child); //h(x)
        child.heuristic += 1; //g(x)
        
        //add to children vector
        children.push_back(child);
    }

    //check right
    if(board.currPos % size != (size-1)) {
        //create a new node and copy current board state
        node child(board);
        
        //swap the 0 tile with the above tile
        child.value[child.currPos] = board.value[board.currPos + 1];
        child.value[child.currPos + 1] = board.value[board.currPos];
        child.currPos = board.currPos + 1;
        
        //calc new heuristic
        calcHeuristic(child); //h(x)
        child.heuristic += 1; //g(x)
        
        //add to children vector
        children.push_back(child);
    }

    return children;
}

//==== CALC_HEURISTIC ====
void calcHeuristic(node& board) {
    int size = sqrt(SIZE);
    int heuristic = 0;
    for(int x = 0; x < SIZE; ++x) {
        //get the current tile value
        int tile = board.value[x];

        //find the row & column it's SUPPOSED to be in
        int goalRow = tile / size;
        int goalColumn = tile % size;

        //find the row & column it's CURRENTLY in
        int currRow = x / size;
        int currColumn = x % size;

        //add their differences
        heuristic += abs(goalRow-currRow) + abs(goalColumn-currColumn);
    }
    board.heuristic = heuristic;
}

//==== IS_GOAL_STATE ====
bool isGoalState(const node& board) {
    bool goalState = true;

    for(short x = 0; x < SIZE; ++x) {
        if(board.value[x] != x) {
            goalState = false;
            break;
        }
    }
    return goalState;
}

//==== RANDOMIZE ====
void randomize(node& board) {
    bool number[SIZE] = {false};
    
    for(short x = 0; x < SIZE; ++x) {
        int y = rand() % SIZE; 
        if(number[y] == false) { 
            board.value[x] = y;
            number[y] = true;

            if(y == 0) {
                board.currPos = x; //sets the index of the 0 tile    
            }
        }
        else {
            --x;   
        }
    }
}

//==== DISPLAY ====
void display(const node& board) {
    for(short x = 0; x < SIZE; ++x) {
        if(x % 3 == 0) {
            cout << endl;
        }
        cout << board.value[x] << " ";
    }
    cout << "\nCurrent Position: " << board.currPos << endl;
    cout << "Heuristic:: " << board.heuristic << endl;
}

#endif
