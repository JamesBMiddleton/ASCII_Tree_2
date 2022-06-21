#include "twig_segments.h"

SegmentTwig::SegmentTwig(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, p_glyph, p_constraints}
{}

void SegmentTwig::choose_twig_segment(std::map<Choice, int> probability, std::map<Choice, Coords> adj_coords)
{
    next_segs.clear();
    std::vector<Choice> raffle;
    for (auto& it : probability)
    {
        while (it.second--)
            raffle.push_back(it.first);
    }
    int winner = rand() % (raffle.size());
    switch (raffle[winner])
    {
        case Choice::Straight:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigStraight{adj_coords[Choice::Straight], constraints}});
            break;
        case Choice::Left:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigLeft{adj_coords[Choice::Left], constraints}});
            break;
        case Choice::Right:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigRight{adj_coords[Choice::Right], constraints}});
            break;
        case Choice::Split:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigSplit{adj_coords[Choice::Split], constraints}});
            break;
        case Choice::SplitFlatLeft:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigSplitFlatLeft{adj_coords[Choice::SplitFlatLeft], constraints}});
            break;
        case Choice::SplitFlatRight:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigSplitFlatRight{adj_coords[Choice::SplitFlatRight], constraints}});
            break;
    }
}


TwigStraight::TwigStraight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTwig{p_coords, "|", p_constraints}
{}

void TwigStraight::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Left, 1},
                                    {Choice::Right, 1},
                                    {Choice::Split, 3}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}},
                                        {Choice::Right, {coords.x+1, coords.y+1}},
                                        {Choice::Split, {coords.x, coords.y+1}}};
    choose_twig_segment(probability, adj_coords);
}


TwigLeft::TwigLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTwig{p_coords, "\\", p_constraints}
{}

void TwigLeft::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Left, 1},
                                    {Choice::Split, 3},
                                    {Choice::SplitFlatRight, 3}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}},
                                        {Choice::Split, {coords.x-1, coords.y+1}},
                                        {Choice::SplitFlatRight, {coords.x-1, coords.y+1}}};
    choose_twig_segment(probability, adj_coords);
}



TwigRight::TwigRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTwig{p_coords, "/", p_constraints}
{}

void TwigRight::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Right, 1},
                                    {Choice::Split, 3},
                                    {Choice::SplitFlatLeft, 3}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Right, {coords.x+1, coords.y+1}},
                                        {Choice::Split, {coords.x, coords.y+1}},
                                        {Choice::SplitFlatLeft, {coords.x, coords.y+1}}};
    choose_twig_segment(probability, adj_coords);
}


TwigSplit::TwigSplit(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTwig{p_coords, "\\/", p_constraints}
{}

void TwigSplit::choose_next_segments()
{

}


TwigSplitFlatLeft::TwigSplitFlatLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTwig{p_coords, "_/", p_constraints}
{}

void TwigSplitFlatLeft::choose_next_segments()
{

}


TwigSplitFlatRight::TwigSplitFlatRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTwig{p_coords, "\\_", p_constraints}
{}

void TwigSplitFlatRight::choose_next_segments()
{

}