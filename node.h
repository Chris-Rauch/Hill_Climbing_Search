//@node.h
#include "node.cpp"
const int SIZE = 9;

struct node {
    node(){}
    node(const node& rhs);
    
    int value[SIZE];
    int heuristic;
    int currPos; //represents the index of the empty tile, aka 0
};

struct CompareHeuristic {
    bool operator()(node const& lhs, node const& rhs) {
        return lhs.heuristic > rhs.heuristic;
    }
};

node::node(const node& rhs) : heuristic(rhs.heuristic), currPos(rhs.heuristic) {
    for(short x = 0; x < SIZE; ++x) {
        this->value[x] = rhs.value[x];
    }
}

inline bool operator==(const node& lhs, const node& rhs) {
    bool visited = true;

    for(short x = 0; x < SIZE; ++x) {
        if(lhs.value[x] != rhs.value[x]) {
            visited = false;
            break;
        }
    }
    return visited;
}
