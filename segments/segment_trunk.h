#ifndef SEGMENT_TRUNK_H_
#define SEGMENT_TRUNK_H_

#include "segment.h"

struct SegmentTrunk : Segment
{
    void next_segment() override;
    void draw_segment() override;
    SegmentTrunk(Coords, std::string, Segment*);
};

#endif