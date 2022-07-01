#ifndef FOREST_H_
#define FOREST_H_

#include "tree.h"

struct Forest
{
    void grow_trees(int);
    Forest(const int, const int, const int, Constraints);
private:
    Forest();
    std::vector<Tree> tree_pool; 
};

#endif