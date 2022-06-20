#ifndef TWIG_SEGMENTS_H_
#define TWIG_SEGMENTS_H_

#include "segment.h"


struct SegmentTwig : public Segment
{
protected:
    SegmentTwig(Coords, std::string, std::shared_ptr<Constraints>);
    enum class Choice{Straight, Left, Right};
    void choose_twig_segment(std::map<Choice, int>, std::map<Choice, Coords>);
};


struct TwigStraight : public SegmentTwig
{
    void choose_next_segments() override;
    TwigStraight(Coords, std::shared_ptr<Constraints>);
};

struct TwigLeft : public SegmentTwig
{
    void choose_next_segments() override;
    TwigLeft(Coords, std::shared_ptr<Constraints>);
};

struct TwigRight : public SegmentTwig
{
    void choose_next_segments() override;
    TwigRight(Coords, std::shared_ptr<Constraints>);
};

#endif