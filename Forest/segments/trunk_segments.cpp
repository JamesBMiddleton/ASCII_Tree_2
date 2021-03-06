#include "trunk_segments.h"
#include "arm_segments.h"

SegmentTrunk::SegmentTrunk(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints)
    :Segment{p_coords, p_glyph, p_constraints}
{}

void SegmentTrunk::choose_trunk_segment(std::map<Choice, int> probability, std::map<Choice, Coords> adj_coords)
{
    if (coords.y >= constraints->max_trunk_height)
    {
        next_segs.push_back(std::unique_ptr<Segment>{new TrunkSplit{adj_coords[Choice::Split], constraints}});
        return;
    }

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
{
    int n = rand() % 3;
    switch (n)
    {
        case 0:
            glyph = "|~  |";
            break;
        case 1:
            glyph = (!constraints->has_hollow && coords.y > 5)? "| @ |" : "| ~ |";
            constraints->has_hollow = true;
            break;
        case 2:
            glyph = "|  ~|";
            break;
    }
}

void TrunkStraight::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 2},
                                    {Choice::Left, 4},
                                    {Choice::Right, 4}, 
                                    {Choice::Split, 1},
                                    {Choice::ArmLeft, 1},
                                    {Choice::ArmRight, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}},
                                        {Choice::Right, {coords.x+1, coords.y+1}},
                                        {Choice::Split, {coords.x, coords.y+1}},
                                        {Choice::ArmLeft, {coords.x, coords.y+1}},
                                        {Choice::ArmRight, {coords.x, coords.y+1}}};
    choose_trunk_segment(probability, adj_coords);
}


TrunkLeft::TrunkLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "\\   \\", p_constraints}
{
    int n = rand() % 4;
    switch (n)
    {
        case 0:
            glyph = "\\~  \\";
            break;
        case 1:
            glyph = (!constraints->has_hollow && coords.y > 5)? "\\ @ \\" : "\\ ~ \\";
            constraints->has_hollow = true;
            break;
        case 2:
            glyph = "\\  ~\\";
            break;
    }
}

void TrunkLeft::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 2},
                                    {Choice::Left, 4},
                                    {Choice::Split, 1},
                                    {Choice::ArmLeft, 1},
                                    {Choice::ArmRight, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                         {Choice::Left, {coords.x-1, coords.y+1}},
                                         {Choice::Split, {coords.x-1, coords.y+1}},
                                         {Choice::ArmLeft, {coords.x-1, coords.y+1}},
                                         {Choice::ArmRight, {coords.x-1, coords.y+1}}};
    choose_trunk_segment(probability, adj_coords); 
}

TrunkRight::TrunkRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "/   /", p_constraints}
{
    int n = rand() % 3;
    switch (n)
    {
        case 0:
            glyph = "/~  /";
            break;
        case 1:
            glyph = (!constraints->has_hollow && coords.y > 5)? "/ @ /" : "/ ~ /";
            constraints->has_hollow = true;
            break;
        case 2:
            glyph = "/  ~/";
            break;
    }
}

void TrunkRight::choose_next_segments()
{
    std::map<Choice, int> probability {{Choice::Straight, 2},
                                    {Choice::Right, 4},
                                    {Choice::Split, 1},
                                    {Choice::ArmLeft, 1},
                                    {Choice::ArmRight, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                         {Choice::Right, {coords.x+1, coords.y+1}},
                                         {Choice::Split, {coords.x, coords.y+1}},
                                         {Choice::ArmLeft, {coords.x, coords.y+1}},
                                         {Choice::ArmRight, {coords.x, coords.y+1}}};
    choose_trunk_segment(probability, adj_coords);
}


TrunkSplit::TrunkSplit(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "\\~\\/~/", p_constraints}
{}

void TrunkSplit::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new ArmLeft{{coords.x-1, coords.y+1}, constraints}});
    next_segs.push_back(std::unique_ptr<Segment>{new ArmRight{{coords.x+4, coords.y+1}, constraints}});
} 


TrunkArmLeft::TrunkArmLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "\\    /", p_constraints}
{
    int n = rand() % 4;
    switch (n)
    {
        case 0:
            glyph = "\\~   /";
            break;
        case 1:
            glyph = "\\ ~  /";
            break;
        case 2:
            glyph = "\\  ~ /";
            break;
        case 3:
            glyph = "\\   ~/";
            break;
    }
}

void TrunkArmLeft::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new ArmLeft{{coords.x-1, coords.y+1}, constraints}});
    next_segs.push_back(std::unique_ptr<Segment>{new TrunkRight{{coords.x+2, coords.y+1}, constraints}});
} 


TrunkArmRight::TrunkArmRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints)
    :SegmentTrunk{p_coords, "\\    /", p_constraints}
{
    int n = rand() % 4;
    switch (n)
    {
        case 0:
            glyph = "\\~   /";
            break;
        case 1:
            glyph = "\\ ~  /";
            break;
        case 2:
            glyph = "\\  ~ /";
            break;
        case 3:
            glyph = "\\   ~/";
            break;
    }
}

void TrunkArmRight::choose_next_segments()
{
    next_segs.clear();
    next_segs.push_back(std::unique_ptr<Segment>{new TrunkLeft{{coords.x-1, coords.y+1}, constraints}});
    next_segs.push_back(std::unique_ptr<Segment>{new ArmRight{{coords.x+4, coords.y+1}, constraints}});
} 
