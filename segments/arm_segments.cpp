#include "arm_segments.h"

SegmentArm::SegmentArm(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, p_glyph, p_constraints}
{}


ArmStraight::ArmStraight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "| |", p_constraints}
{}

void ArmStraight::choose_next_segments()
{
    next_segs.clear();
    static std::vector<int> raffle {0,0,0,1,1,1,2,2,2};
    int choice = rand() % (raffle.size() -1);
    switch (raffle[choice])
    {
        case 0:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmStraight{{coords.x, coords.y+1}, constraints}});
            break;
        case 1:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmLeft{{coords.x-1, coords.y+1}, constraints}});
            break;
        case 2:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmRight{{coords.x, coords.y+1}, constraints}});
            break;
    }
}


ArmLeft::ArmLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "\\ \\", p_constraints}
{}

void ArmLeft::choose_next_segments()
{
    next_segs.clear();
    static std::vector<int> raffle {0,0,0,1,1,1,2,2,2};
    int choice = rand() % (raffle.size() -1);
    switch (raffle[choice])
    {
        case 0:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmStraight{{coords.x, coords.y+1}, constraints}});
            break;
        case 1:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmLeft{{coords.x-1, coords.y+1}, constraints}});
            break;
        case 2:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmRight{{coords.x+1, coords.y+1}, constraints}});
            break;
    }
}



ArmRight::ArmRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentArm{p_coords, "/ /", p_constraints}
{}

void ArmRight::choose_next_segments()
{
    next_segs.clear();
    static std::vector<int> raffle {0,0,0,1,1,1,2,2,2};
    int choice = rand() % (raffle.size() -1);
    switch (raffle[choice])
    {
        case 0:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmStraight{{coords.x, coords.y+1}, constraints}});
            break;
        case 1:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmLeft{{coords.x, coords.y+1}, constraints}});
            break;
        case 2:
            next_segs.push_back(std::unique_ptr<Segment>{new ArmRight{{coords.x+1, coords.y+1}, constraints}});
            break;
    }
}

