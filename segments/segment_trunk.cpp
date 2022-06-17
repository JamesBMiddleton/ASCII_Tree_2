#include "segment_trunk.h"

SegmentTrunk::SegmentTrunk(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, p_glyph, p_constraints}
{}

// void SegmentTrunk::choose_next_segments()
// {
//     next_segs.clear();
//     int choice = rand() % 3;
//     switch (choice)
//     {
//         case 0:
//             next_segs.push_back(std::unique_ptr<Segment>{new SegmentTrunk{{coords.x, coords.y+1}, "|   |", constraints}});
//             break;
//         case 1:
//             next_segs.push_back(std::unique_ptr<Segment>{new SegmentTrunk{{coords.x-1, coords.y+1}, "\\   \\", constraints}});
//             break;
//         case 2:
//             next_segs.push_back(std::unique_ptr<Segment>{new SegmentTrunk{{coords.x+1, coords.y+1}, "/   /", constraints}});
//             break;
//     }
    
// }



TrunkStraight::TrunkStraight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "|   |", p_constraints}
{}

void TrunkStraight::choose_next_segments()
{
    next_segs.clear();
    int choice = rand() % 3;
    switch (choice)
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
    }  
}


TrunkLeft::TrunkLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "\\   \\", p_constraints}
{}

void TrunkLeft::choose_next_segments()
{
    next_segs.clear();
    int choice = rand() % 3;
    switch (choice)
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
    }  
}

TrunkRight::TrunkRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "/   /", p_constraints}
{}

void TrunkRight::choose_next_segments()
{
    next_segs.clear();
    int choice = rand() % 3;
    switch (choice)
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
    }  
}