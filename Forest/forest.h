#ifndef FOREST_H_
#define FOREST_H_

#include "tree.h"

struct Forest
{
    void grow_trees(const int);
    Forest(const int, const int, const int, const Constraints&);
private:
    Forest();
    std::vector<Tree> tree_pool; 
};

#endif