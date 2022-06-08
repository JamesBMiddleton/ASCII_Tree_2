#include "segment_base.h"
#include "segment_trunk.h"

SegmentBase::SegmentBase(std::set<Segment*>& pool)
    :Segment(Coords{10,20}, "/    \\", this)
{
    branch_pool = pool;
}

void SegmentBase::next_segment()
{
    draw_segment();
    Segment* s = new SegmentTrunk{{coords.x, coords.y+1}, "|   |", this};
    branch_pool.insert(s);
}

void SegmentBase::draw_segment()
{
    std::cout << "base drawn" << std::endl;
}