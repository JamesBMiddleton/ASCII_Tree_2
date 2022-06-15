#include "segment.h"

Segment::Segment(Coords p_coords, std::string p_glyph)
    :coords{p_coords}, glyph{p_glyph}
{

}

void Segment::draw_segment()
{
    std::cout << ANSI::move_cursor(coords.x, coords.y);
    std::cout << ANSI::set_colour(161,61,45) << glyph;
    std::cout.flush();
}