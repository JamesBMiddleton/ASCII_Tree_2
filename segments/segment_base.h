#ifndef SEGMENT_BASE_H_
#define SEGMENT_BASE_H_

#include "segment.h"

struct SegmentBase : public Segment
{
    std::vector<std::shared_ptr<Segment>> get_next_segments() override;
    void draw_segment() override;
    SegmentBase();
    ~SegmentBase() {};
};

#endif