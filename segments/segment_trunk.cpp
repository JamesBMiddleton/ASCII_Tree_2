#include "segment_trunk.h"

SegmentTrunk::SegmentTrunk(Coords p_coords, std::string p_glyph, Segment* p_previous_segment)
    :Segment(p_coords, p_glyph, p_previous_segment)
{

}

void SegmentTrunk::next_segment()
{
    draw_segment();
    Segment* s = new SegmentTrunk{{coords.x, coords.y+1}, glyph, this};
    branch_pool.insert(s);
    if (branch_pool.find(prev_segment) != branch_pool.end())
    {
        delete prev_segment;
        branch_pool.erase(prev_segment);
    }
}

void SegmentTrunk::draw_segment()
{
    std::cout << "trunk drawn" << std::endl;
}