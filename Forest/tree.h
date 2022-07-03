#ifndef TREE_H_
#define TREE_H_

#include "segments/segment.h"

#include <vector>
#include <chrono>
#include <thread>

struct Tree
// Each instance holds a pool of segments, one for each branch of a tree.
{
    void grow_branches();
    bool is_finished() {return branch_pool.size() == 0;}
    Tree(const Constraints&, const Coords&);
private:
    Tree();
    std::vector<std::unique_ptr<Segment>> branch_pool;
};

#endif