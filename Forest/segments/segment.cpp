#include "segment.h"
#include "trunk_segments.h"

Segment::Segment(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints)
    :coords{p_coords}, glyph{p_glyph}, constraints{p_constraints}
{
    if (coords.x >= TERMINAL_INFO::max_width)
        coords.x = TERMINAL_INFO::max_width-1;
    if (coords.x < 0)
        coords.x = 0;
    if (coords.y >= TERMINAL_INFO::max_height)
        coords.y = TERMINAL_INFO::max_height-1;
}

void Segment::draw_segment()
{
    std::cout << ANSI::move_cursor(coords.x, coords.y);
    std::cout << ANSI::set_colour(161,61,45) << glyph << std::flush;
    for (int i{0}; i<glyph.size(); i++)
        constraints->segment_locations[coords.y][coords.x+i] = glyph[i];
    
    // Show the segment matrix for debugging.
    // for (int i{0}; i<constraints->segment_locations.size(); ++i)
    //     for (int j{0}; j<constraints->segment_locations[0].size(); ++j)
    //         std::cout << constraints->segment_locations[i][j]; 
}




SegmentBase::SegmentBase(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, "/     \\", p_constraints}
{}

void SegmentBase::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new TrunkStraight{{coords.x+1, coords.y+1}, constraints}});
}