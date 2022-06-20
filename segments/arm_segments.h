#ifndef ARM_SEGMENTS_H_
#define ARM_SEGMENTS_H_

#include "segment.h"


struct SegmentArm : public Segment
{
protected:
    SegmentArm(Coords, std::string, std::shared_ptr<Constraints>);
    enum class Choice{Straight, Left, Right, TaperLeft, TaperRight, TwigLeft, TwigRight};
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

struct ArmTaperLeft : public SegmentArm
{
    void choose_next_segments() override;
    ArmTaperLeft(Coords, std::shared_ptr<Constraints>);
};

struct ArmTaperRight : public SegmentArm
{
    void choose_next_segments() override;
    ArmTaperRight(Coords, std::shared_ptr<Constraints>); 
};

// struct ArmTwigLeft : public SegmentArm
// {
//     void choose_next_segments() override;
//     ArmTwigLeft(Coords, std::shared_ptr<Constraints>);
// };

// struct ArmTwigRight : public SegmentArm
// {
//     void choose_next_segments() override;
//     ArmTwigRight(Coords, std::shared_ptr<Constraints>);
// };

#endif


