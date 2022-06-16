#ifndef SEGMENT_BASE_H_
#define SEGMENT_BASE_H_

#include "segment.h"

struct SegmentBase : public Segment
{
    void choose_next_segments() override;
    // void draw_segment() override;
    SegmentBase(Coords, std::shared_ptr<Constraints>);
    ~SegmentBase() {};
};

#endif