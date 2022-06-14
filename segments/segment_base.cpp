#include "segment_base.h"
#include "segment_trunk.h"

SegmentBase::SegmentBase()
    :Segment{{10,20}, "/   \\"}
{}

void SegmentBase::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new SegmentTrunk{{coords.x, coords.y+1}, "|   |"}});
}

void SegmentBase::draw_segment()
{
    std::cout << "base drawn" << std::endl;
}