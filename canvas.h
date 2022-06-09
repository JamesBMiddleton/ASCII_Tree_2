#ifndef CANVAS_H_
#define CANVAS_H_

#include "segments/segment.h"

#include <vector>

struct Constraints{};

struct Canvas
{
    void grow_branches();
    Canvas();
private:
    std::vector<std::shared_ptr<Segment>> branch_pool;
    //Constraints constraints;
};

#endif