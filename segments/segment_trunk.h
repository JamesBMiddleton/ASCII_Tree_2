#ifndef SEGMENT_TRUNK_H_
#define SEGMENT_TRUNK_H_

#include "segment.h"

struct SegmentTrunk : public Segment
{
    std::vector<std::shared_ptr<Segment>> get_next_segments() override;
    void draw_segment() override;
    SegmentTrunk(Coords, std::string);
    ~SegmentTrunk() {};
};

#endif