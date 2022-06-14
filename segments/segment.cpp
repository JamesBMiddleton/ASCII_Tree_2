#include "segment.h"

Segment::Segment(Coords p_coords, std::string p_glyph)
    :coords{p_coords}, glyph{p_glyph}
{

}

void Segment::draw_segment()
{
    std::cout << "\x1B[" << coords.y << ';' << coords.x << 'H'; // CONSTANTS
    std::cout << "\x1b[38;2;161;61;45m" + glyph + "\x1b[m"; // CONSTANTS
    std::cout.flush();
}