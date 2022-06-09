#include "canvas.h"
#include "segments/segment_base.h"

Canvas::Canvas()
    :branch_pool{}
{
    branch_pool.push_back(std::unique_ptr<Segment>{new SegmentBase{}});
}

void Canvas::grow_branches()
{
    int n{10};
    while (n--)
    {   
        std::vector<std::shared_ptr<Segment>> new_pool;
        for (std::shared_ptr<Segment>& s_ptr : branch_pool)
        {
            std::vector<std::shared_ptr<Segment>> temp = s_ptr.get()->get_next_segments();
            new_pool.insert(
                    new_pool.end(),
                    std::make_move_iterator(temp.begin()),
                    std::make_move_iterator(temp.end())
                );
        }
        branch_pool = new_pool;
    }
    
}