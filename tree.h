#ifndef TREE_H_
#define TREE_H_

#include "segments/segment.h"

#include <vector>

struct Tree
{
    void grow_branches();
    Tree(Constraints);
private:
    Tree();
    std::vector<std::unique_ptr<Segment>> branch_pool;
    //Constraints constraints;
};

#endif