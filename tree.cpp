#include "tree.h"

Tree::Tree(Constraints constraints, Coords start_coords)
    :branch_pool{}
{
    branch_pool.push_back(
        std::unique_ptr<Segment>{new SegmentBase{
            start_coords,
            std::shared_ptr<Constraints>{new Constraints{constraints}}}}     // This is messy... also should be using 'make_shared/unique'.
    );
}

void Tree::grow_branches()
/* The main program loop.
   Draws the segments in the branch_pool and moves the next segments chosen by each segment into
   branch_pool via new_pool.
   Moving rather than copying due to unique_ptrs to allow virtual calls to different segment types */
{
    int n{15};
    while (branch_pool.size())
    {   
        std::vector<std::unique_ptr<Segment>> new_pool;
        for (std::unique_ptr<Segment>& seg_ptr : branch_pool)
        {
            seg_ptr->draw_segment();
            seg_ptr->choose_next_segments();
            std::vector<std::unique_ptr<Segment>>& temp = seg_ptr->get_next_segments();
            new_pool.insert(
                new_pool.end(),
                std::make_move_iterator(temp.begin()),
                std::make_move_iterator(temp.end())
            );
            temp.clear();    
        }
        branch_pool.clear();
        branch_pool.insert(
            branch_pool.end(),
            std::make_move_iterator(new_pool.begin()),
            std::make_move_iterator(new_pool.end())
        );
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}