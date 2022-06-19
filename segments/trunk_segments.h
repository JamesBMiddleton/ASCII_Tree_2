#ifndef TRUNK_SEGMENTS_H_
#define TRUNK_SEGMENTS_H_

#include "segment.h"

struct SegmentTrunk : public Segment
{
protected:
    SegmentTrunk(Coords, std::string, std::shared_ptr<Constraints>);
};

struct TrunkStraight : public SegmentTrunk
{
    void choose_next_segments() override;
    TrunkStraight(Coords, std::shared_ptr<Constraints>);
};

struct TrunkLeft : public SegmentTrunk
{
    void choose_next_segments() override;
    TrunkLeft(Coords, std::shared_ptr<Constraints>);
};

struct TrunkRight : public SegmentTrunk
{
    void choose_next_segments() override;
    TrunkRight(Coords, std::shared_ptr<Constraints>);
};


struct TrunkSplit : public SegmentTrunk
{
    void choose_next_segments() override;
    TrunkSplit(Coords, std::shared_ptr<Constraints>);
};

struct TrunkArmLeft : public SegmentTrunk
{
    void choose_next_segments() override;
    TrunkArmLeft(Coords, std::shared_ptr<Constraints>);
};

struct TrunkArmRight : public SegmentTrunk
{
    void choose_next_segments() override;
    TrunkArmRight(Coords, std::shared_ptr<Constraints>);
};

#endif