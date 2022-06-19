#include "trunk_segments.h"
#include "arm_segments.h"

SegmentTrunk::SegmentTrunk(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, p_glyph, p_constraints}
{}


TrunkStraight::TrunkStraight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "|   |", p_constraints}
{}

void TrunkStraight::choose_next_segments()
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
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkRight{{coords.x+1, coords.y+1}, constraints}});
            break;
        case 3:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkSplit{{coords.x, coords.y+1}, constraints}});
            break;
        case 4:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmLeft{{coords.x, coords.y+1}, constraints}});
            break;
        case 5:
            next_segs.push_back(std::unique_ptr<Segment>{new TrunkArmRight{{coords.x, coords.y+1}, constraints}});
            break;
    }  
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
