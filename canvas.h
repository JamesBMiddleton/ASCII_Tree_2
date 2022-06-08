#ifndef CANVAS_H_
#define CANVAS_H_

#include "segments/segment.h"

#include <set>

struct Constraints{};

struct Canvas
{
    void grow_branches();
    Canvas();
private:
    std::set<Segment*> branch_pool;
    //Constraints constraints;
};

#endif