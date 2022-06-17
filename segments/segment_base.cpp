#include "segment_base.h"
#include "segment_trunk.h"

SegmentBase::SegmentBase(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, "/     \\", p_constraints}
{}

void SegmentBase::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new TrunkStraight{{coords.x+1, coords.y+1}, constraints}});
}

// void SegmentBase::draw_segment()
// {
//     std::cout << "base drawn" << std::endl;
// }