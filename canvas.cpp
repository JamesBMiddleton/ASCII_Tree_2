#include "canvas.h"
#include "segments/segment_base.h"

Canvas::Canvas()
    :branch_pool{}
{
    branch_pool.insert(new SegmentBase{branch_pool});
}

void Canvas::grow_branches()
{
    std::cout << branch_pool.size();
    while (branch_pool.size())
    {
        for (Segment* s : branch_pool)   // can't add to it while iterating over it anyway...
            s->next_segment();
    }
}