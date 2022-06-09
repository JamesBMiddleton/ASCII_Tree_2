#include "segment_trunk.h"

SegmentTrunk::SegmentTrunk(Coords p_coords, std::string p_glyph)
    :Segment{p_coords, p_glyph}
{}

std::vector<std::shared_ptr<Segment>> SegmentTrunk::get_next_segments()
{
    draw_segment();
    std::vector<std::shared_ptr<Segment>> next_segments;
    next_segments.push_back(std::shared_ptr<Segment>{new SegmentTrunk{{coords.x, coords.y+1}, "|   |"}});
    return next_segments;
}

void SegmentTrunk::draw_segment()
{
    std::cout << "trunk drawn" << std::endl;
}