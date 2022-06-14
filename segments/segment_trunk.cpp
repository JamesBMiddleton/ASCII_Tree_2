#include "segment_trunk.h"

SegmentTrunk::SegmentTrunk(Coords p_coords, std::string p_glyph)
    :Segment{p_coords, p_glyph}
{}

void SegmentTrunk::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new SegmentTrunk{{coords.x, coords.y+1}, "|   |"}});
}

void SegmentTrunk::draw_segment()
{
    std::cout << "trunk drawn" << std::endl;
}