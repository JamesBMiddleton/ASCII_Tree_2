#include "segment_base.h"
#include "segment_trunk.h"

SegmentBase::SegmentBase()
    :Segment{{10,20}, "/   \\"}
{}

std::vector<std::shared_ptr<Segment>> SegmentBase::get_next_segments()
{
    draw_segment();
    std::vector<std::shared_ptr<Segment>> next_segments;
    next_segments.push_back(std::shared_ptr<Segment>{new SegmentTrunk{{coords.x, coords.y+1}, "|   |"}});
    return next_segments;
}

void SegmentBase::draw_segment()
{
    std::cout << "base drawn" << std::endl;
}