#ifndef SEGMENT_BASE_H_
#define SEGMENT_BASE_H_

#include "segment.h"

struct SegmentBase : Segment
{
    void next_segment() override;
    void draw_segment() override;
    SegmentBase(std::set<Segment*>&);
};

#endif