#include "trunk_segments.h"
#include "arm_segments.h"

SegmentTrunk::SegmentTrunk(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, p_glyph, p_constraints}
{}

void SegmentTrunk::choose_trunk_segment(std::map<Choice, int> probability, std::map<Choice, Coords> adj_coords)
{
    next_segs.clear();
    std::vector<Choice> raffle;
    for (auto& it : probability)
    {
        while (it.second--)
            raffle.push_back(it.first);
    }
    int winner = rand() % (raffle.size() -1);
    switch (raffle[winner])
    {
        case Choice::Straight:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkStraight{adj_coords[Choice::Straight], constraints}});
            break;
        case Choice::Left:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkLeft{adj_coords[Choice::Left], constraints}});
            break;
        case Choice::Right:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkRight{adj_coords[Choice::Right], constraints}});
            break;
        case Choice::Split:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkSplit{adj_coords[Choice::Split], constraints}});
            break;
        case Choice::ArmLeft:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmLeft{adj_coords[Choice::ArmLeft], constraints}});
            break;
        case Choice::ArmRight:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmRight{adj_coords[Choice::ArmRight], constraints}});
            break;
    }
}

TrunkStraight::TrunkStraight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "|   |", p_constraints}
{}

void TrunkStraight::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 1}, {Choice::Left, 1}, {Choice::Right, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}}, {Choice::Left, {coords.x, coords.y+1}}, {Choice::Right, {coords.x, coords.y+1}}};
    choose_trunk_segment(probability, adj_coords);
    std::cout << "worked...?";
    // next_segs.clear();
    // static std::vector<int> raffle {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5};
    // int choice = rand() % (raffle.size() -1);
    // switch (raffle[choice])
    // {
    //     case 0:
    //         next_segs.push_back(std::unique_ptr<Segment>{new TrunkStraight{{coords.x, coords.y+1}, constraints}});
    //         break;
    //     case 1:
    //         next_segs.push_back(std::unique_ptr<Segment>{new TrunkLeft{{coords.x-1, coords.y+1}, constraints}});
    //         break;
    //     case 2:
    //         next_segs.push_back(std::unique_ptr<Segment>{new TrunkRight{{coords.x+1, coords.y+1}, constraints}});
    //         break;
    //     case 3:
    //         next_segs.push_back(std::unique_ptr<Segment>{new TrunkSplit{{coords.x, coords.y+1}, constraints}});
    //         break;
    //     case 4:
    //         next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmLeft{{coords.x, coords.y+1}, constraints}});
    //         break;
    //     case 5:
    //         next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmRight{{coords.x, coords.y+1}, constraints}});
    //         break;
    // }  
}


TrunkLeft::TrunkLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "\\   \\", p_constraints}
{}

void TrunkLeft::choose_next_segments()
{
    next_segs.clear();
    static std::vector<int> raffle {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5};
    int choice = rand() % (raffle.size() -1);
    switch (raffle[choice])
    {
        case 0:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkStraight{{coords.x, coords.y+1}, constraints}});
            break;
        case 1:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkLeft{{coords.x-1, coords.y+1}, constraints}});
            break;
        case 2:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkRight{{coords.x, coords.y+1}, constraints}});
            break;
        case 3:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkSplit{{coords.x-1, coords.y+1}, constraints}});
            break;
        case 4:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmLeft{{coords.x-1, coords.y+1}, constraints}});
            break;
        case 5:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmRight{{coords.x-1, coords.y+1}, constraints}});
            break;
    }  
}

TrunkRight::TrunkRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "/   /", p_constraints}
{}

void TrunkRight::choose_next_segments()
{
    next_segs.clear();
    static std::vector<int> raffle {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5};
    int choice = rand() % (raffle.size() -1);
    switch (raffle[choice])
    {
        case 0:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkStraight{{coords.x, coords.y+1}, constraints}});
            break;
        case 1:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkLeft{{coords.x, coords.y+1}, constraints}});
            break;
        case 2:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkRight{{coords.x+1, coords.y+1}, constraints}});
            break;
        case 3:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkSplit{{coords.x+1, coords.y+1}, constraints}});
            break;
        case 4:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmLeft{{coords.x, coords.y+1}, constraints}});
            break;
        case 5:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmRight{{coords.x, coords.y+1}, constraints}});
            break;
    }  
}


TrunkSplit::TrunkSplit(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "\\ \\/ /", p_constraints}
{}

void TrunkSplit::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new ArmLeft{{coords.x-1, coords.y+1}, constraints}});
    next_segs.push_back(std::unique_ptr<Segment>{new ArmRight{{coords.x+4, coords.y+1}, constraints}});
} 


TrunkArmLeft::TrunkArmLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "\\    /", p_constraints}
{}

void TrunkArmLeft::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new ArmLeft{{coords.x-1, coords.y+1}, constraints}});
    next_segs.push_back(std::unique_ptr<Segment>{new TrunkRight{{coords.x+2, coords.y+1}, constraints}});
} 


TrunkArmRight::TrunkArmRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "\\    /", p_constraints}
{}

void TrunkArmRight::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new TrunkLeft{{coords.x-1, coords.y+1}, constraints}});
    next_segs.push_back(std::unique_ptr<Segment>{new ArmRight{{coords.x+4, coords.y+1}, constraints}});
} 
