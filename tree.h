#ifndef TREE_H_
#define TREE_H_

#include "segments/segment.h"

#include <vector>
#include <chrono>
#include <thread>

struct Tree
{
    void grow_branches();
    Tree(Constraints, Coords);
private:
    Tree();
    std::vector<std::unique_ptr<Segment>> branch_pool;
};

#endif