#include "tree.h"

Tree::Tree(const Constraints& constraints, const Coords& start_coords)
// Add the first segment to the branch pool - a SegmentBase.
    :branch_pool{}
{
    branch_pool.push_back(
        std::unique_ptr<Segment>{new SegmentBase{
            start_coords,
            std::shared_ptr<Constraints>{new Constraints{constraints}}}}     // C++11 so not using make_unique/make_shared.
    );
}

void Tree::grow_branches()
/* Loop: Draws the segments in the branch_pool and moves the next segments chosen by each segment (if any)
   into branch_pool via new_pool.
   Moving rather than copying due to unique_ptrs to allow virtual calls to different segment types
   Loop ends when branch_pool is empty. */
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
}