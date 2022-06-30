#include "arm_segments.h"
#include "twig_segments.h"

SegmentArm::SegmentArm(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, p_glyph, p_constraints}
{}

void SegmentArm::choose_arm_segment(std::map<Choice, int> probability, std::map<Choice, Coords> adj_coords)
{
    if (coords.y >= constraints->max_arm_height)
    {
        if (glyph == "\\~\\")
            next_segs.push_back(std::unique_ptr<Segment>{new ArmTaperLeft{adj_coords[Choice::TaperLeft], constraints}});
        else
            next_segs.push_back(std::unique_ptr<Segment>{new ArmTaperRight{adj_coords[Choice::TaperRight], constraints}});
        return;
    }
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
            next_segs.push_back(std::unique_ptr<Segment>{new ArmStraight{adj_coords[Choice::Straight], constraints}});
            break;
        case Choice::Left:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmLeft{adj_coords[Choice::Left], constraints}});
            break;
        case Choice::Right:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmRight{adj_coords[Choice::Right], constraints}});
            break;
        case Choice::TaperLeft:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmTaperLeft{adj_coords[Choice::TaperLeft], constraints}});
            break;
        case Choice::TaperRight:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmTaperRight{adj_coords[Choice::TaperRight], constraints}});
            break;
        case Choice::TwigLeft:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmTwigLeft{adj_coords[Choice::TwigLeft], constraints}});
            break;
        case Choice::TwigRight:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmTwigRight{adj_coords[Choice::TwigRight], constraints}});
            break;
    }
}


ArmStraight::ArmStraight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "|~|", p_constraints}
{}

void ArmStraight::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Left, 3},
                                    {Choice::Right, 3},
                                    {Choice::TaperLeft, 1},
                                    {Choice::TaperRight, 1},
                                    {Choice::TwigLeft, 1},
                                    {Choice::TwigRight, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}},
                                        {Choice::Right, {coords.x+1, coords.y+1}},
                                        {Choice::TaperLeft, {coords.x, coords.y+1}},
                                        {Choice::TaperRight, {coords.x+1, coords.y+1}},
                                        {Choice::TwigLeft, {coords.x, coords.y+1}},
                                        {Choice::TwigRight, {coords.x, coords.y+1}}};
    choose_arm_segment(probability, adj_coords);
}


ArmLeft::ArmLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "\\~\\", p_constraints}
{}

void ArmLeft::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 2},
                                    {Choice::Left, 2},
                                    {Choice::TaperLeft, 4},
                                    {Choice::TwigRight, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}},
                                        {Choice::TaperLeft, {coords.x, coords.y+1}},
                                        {Choice::TwigRight, {coords.x-1, coords.y+1}}};
    choose_arm_segment(probability, adj_coords);
}



ArmRight::ArmRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "/~/", p_constraints}
{}

void ArmRight::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 2},
                                    {Choice::Right, 2},
                                    {Choice::TaperRight, 4},
                                    {Choice::TwigLeft, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Right, {coords.x+1, coords.y+1}},
                                        {Choice::TaperRight, {coords.x+1, coords.y+1}},
                                        {Choice::TwigLeft, {coords.x, coords.y+1}}};
    choose_arm_segment(probability, adj_coords);
}



ArmTaperLeft::ArmTaperLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "|\\", p_constraints}
{}

void ArmTaperLeft::choose_next_segments()
{
    int choice = rand() % 2;
    if (choice)
        next_segs.push_back(std::unique_ptr<Segment>{new TwigLeft{{coords.x, coords.y+1}, constraints, false}});
    else
        next_segs.push_back(std::unique_ptr<Segment>{new TwigStraight{{coords.x, coords.y+1}, constraints, false}});
}


ArmTaperRight::ArmTaperRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "/|", p_constraints}
{}

void ArmTaperRight::choose_next_segments()
{
    next_segs.clear();
    int choice = rand() % 2;
    if (choice)
        next_segs.push_back(std::unique_ptr<Segment>{new TwigRight{{coords.x+1, coords.y+1}, constraints, false}});
    else
        next_segs.push_back(std::unique_ptr<Segment>{new TwigStraight{{coords.x+1, coords.y+1}, constraints, false}});
}



ArmTwigLeft::ArmTwigLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "\\/~/", p_constraints}
{}

void ArmTwigLeft::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new TwigLeft{{coords.x-1, coords.y+1}, constraints, false}});
    next_segs.push_back(std::unique_ptr<Segment>{new ArmRight{{coords.x+2, coords.y+1}, constraints}});
}


ArmTwigRight::ArmTwigRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "\\~\\/", p_constraints}
{}

void ArmTwigRight::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new ArmLeft{{coords.x-1, coords.y+1}, constraints}});
    next_segs.push_back(std::unique_ptr<Segment>{new TwigRight{{coords.x+4, coords.y+1}, constraints, false}});
}