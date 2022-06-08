#include "segment.h"

Segment::Segment(Coords p_coords, std::string p_glyph, Segment* p_prev_segment)
    :coords{p_coords}, glyph{p_glyph}, prev_segment{p_prev_segment}
{

}