#include "arm_segments.h"
#include "twig_segments.h"

SegmentArm::SegmentArm(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, p_glyph, p_constraints}
{}

void SegmentArm::choose_arm_segment(std::map<Choice, int> probability, std::map<Choice, Coords> adj_coords)
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
    }
}


ArmStraight::ArmStraight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "| |", p_constraints}
{}

void ArmStraight::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Left, 1},
                                    {Choice::Right, 1},
                                    {Choice::TaperLeft, 1},
                                    {Choice::TaperRight, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}},
                                        {Choice::Right, {coords.x+1, coords.y+1}},
                                        {Choice::TaperLeft, {coords.x, coords.y+1}}};
    choose_arm_segment(probability, adj_coords);
}


ArmLeft::ArmLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "\\ \\", p_constraints}
{}

void ArmLeft::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Left, 1},
                                    {Choice::TaperLeft, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}},
                                        {Choice::TaperLeft, {coords.x, coords.y+1}}};
    choose_arm_segment(probability, adj_coords);
}



ArmRight::ArmRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "/ /", p_constraints}
{}

void ArmRight::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Right, 1},
                                    {Choice::TaperRight, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Right, {coords.x+1, coords.y+1}},
                                        {Choice::TaperRight, {coords.x+1, coords.y+1}}};
    choose_arm_segment(probability, adj_coords);
}



ArmTaperLeft::ArmTaperLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "|\\", p_constraints}
{}

void ArmTaperLeft::choose_next_segments()
{
    int choice = rand() % 2;
    if (choice)
        next_segs.push_back(std::unique_ptr<Segment>{new TwigLeft{{coords.x, coords.y+1}, constraints}});
    else
        next_segs.push_back(std::unique_ptr<Segment>{new TwigStraight{{coords.x, coords.y+1}, constraints}});
}


ArmTaperRight::ArmTaperRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "/|", p_constraints}
{}

void ArmTaperRight::choose_next_segments()
{
    next_segs.clear();
    int choice = rand() % 2;
    if (choice)
        next_segs.push_back(std::unique_ptr<Segment>{new TwigRight{{coords.x+1, coords.y+1}, constraints}});
    else
        next_segs.push_back(std::unique_ptr<Segment>{new TwigStraight{{coords.x+1, coords.y+1}, constraints}});
}
