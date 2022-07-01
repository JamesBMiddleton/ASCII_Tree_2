#ifndef TWIG_SEGMENTS_H_
#define TWIG_SEGMENTS_H_

#include "segment.h"


struct SegmentTwig : public Segment
{
protected:
    SegmentTwig(Coords, std::string, std::shared_ptr<Constraints>, bool);
    enum class Choice{Straight, Left, Right, FlatLeft, FlatRight, Split, SplitFlatLeft, SplitFlatRight};
    void choose_twig_segment(std::map<Choice, int>, std::map<Choice, Coords>, bool);
    void add_leaves();
    bool is_terminating = false;
};


struct TwigStraight : public SegmentTwig
{
    void choose_next_segments() override;
    TwigStraight(Coords, std::shared_ptr<Constraints>, bool);
};

struct TwigLeft : public SegmentTwig
{
    void choose_next_segments() override;
    TwigLeft(Coords, std::shared_ptr<Constraints>, bool);
};

struct TwigRight : public SegmentTwig
{
    void choose_next_segments() override;
    TwigRight(Coords, std::shared_ptr<Constraints>, bool);
};

struct TwigFlatLeft : public SegmentTwig
{
    void choose_next_segments() override;
    TwigFlatLeft(Coords, std::shared_ptr<Constraints>, bool);
};

struct TwigFlatRight : public SegmentTwig
{
    void choose_next_segments() override;
    TwigFlatRight(Coords, std::shared_ptr<Constraints>, bool);
};

struct TwigSplit : public SegmentTwig
{
    void choose_next_segments() override;
    TwigSplit(Coords, std::shared_ptr<Constraints>, bool);
};


struct TwigSplitFlatLeft : public SegmentTwig
{
    void choose_next_segments() override;
    TwigSplitFlatLeft(Coords, std::shared_ptr<Constraints>, bool);
};

struct TwigSplitFlatRight : public SegmentTwig
{
    void choose_next_segments() override;
    TwigSplitFlatRight(Coords, std::shared_ptr<Constraints>, bool);
};





struct LeafGroup : public Segment
{
    LeafGroup(Coords, std::shared_ptr<Constraints>, std::vector<Coords>, bool);
    std::vector<Coords> leaf_coords;
    void choose_next_segments() override;
    void draw_segment() override;
    bool is_terminating = false;
};

#endif
