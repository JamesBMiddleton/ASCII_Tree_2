#define ARM_SEGMENTS_H_
#define ARM_SEGMENTS_H_

#include "segment.h"


struct SegmentArm : public Segment
{
protected:
    SegmentArm(Coords, std::string, std::shared_ptr<Constraints>);
    enum class Choice{Straight, Left, Right};
    void choose_arm_segment(std::map<Choice, int>, std::map<Choice, Coords>);
};


struct ArmStraight : public SegmentArm
{
    void choose_next_segments() override;
    ArmStraight(Coords, std::shared_ptr<Constraints>);
};

struct ArmLeft : public SegmentArm
{
    void choose_next_segments() override;
    ArmLeft(Coords, std::shared_ptr<Constraints>);
};

struct ArmRight : public SegmentArm
{
    void choose_next_segments() override;
    ArmRight(Coords, std::shared_ptr<Constraints>);
};




