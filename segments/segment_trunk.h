#ifndef SEGMENT_TRUNK_H_
#define SEGMENT_TRUNK_H_

#include "segment.h"

struct SegmentTrunk : public Segment
{
    virtual void choose_next_segments() override;
    // void draw_segment() override;
    SegmentTrunk(Coords, std::string, std::shared_ptr<Constraints>);
    ~SegmentTrunk() {};
};

#endif