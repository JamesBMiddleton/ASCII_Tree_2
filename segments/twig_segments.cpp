#include "twig_segments.h"
#include "../terminal_abstractions.h"

#include <chrono>
#include <thread>

SegmentTwig::SegmentTwig(Coords p_coords, std::string p_glyph, std::shared_ptr<Constraints> p_constraints, bool p_terminate=false)
    :Segment{p_coords, p_glyph, p_constraints}
{
    is_terminating = p_terminate;
}

void SegmentTwig::choose_twig_segment(std::map<Choice, int> probability, std::map<Choice, Coords> adj_coords, bool terminate=false)
{
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
            next_segs.push_back(std::unique_ptr<Segment>{new TwigStraight{adj_coords[Choice::Straight], constraints, terminate}});
            break;
        case Choice::Left:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigLeft{adj_coords[Choice::Left], constraints, terminate}});
            break;
        case Choice::Right:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigRight{adj_coords[Choice::Right], constraints, terminate}});
            break;
        case Choice::FlatLeft:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigFlatLeft{adj_coords[Choice::FlatLeft], constraints, terminate}});
            break;
        case Choice::FlatRight:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigFlatRight{adj_coords[Choice::FlatRight], constraints, terminate}});
            break;
        case Choice::Split:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigSplit{adj_coords[Choice::Split], constraints, terminate}});
            break;
        case Choice::SplitFlatLeft:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigSplitFlatLeft{adj_coords[Choice::SplitFlatLeft], constraints, terminate}});
            break;
        case Choice::SplitFlatRight:
            next_segs.push_back(std::unique_ptr<Segment>{new TwigSplitFlatRight{adj_coords[Choice::SplitFlatRight], constraints, terminate}});
            break;
    }
}

void SegmentTwig::add_leaves()
{
    std::vector<Coords> leaf_coords = {{coords.x, coords.y+1}, {coords.x, coords.y-1}, {coords.x+1, coords.y}, {coords.x-1, coords.y}};
    next_segs.push_back(std::unique_ptr<Segment>{new LeafGroup{coords, constraints, leaf_coords, false}});
}


TwigStraight::TwigStraight(Coords p_coords, std::shared_ptr<Constraints> p_constraints, bool p_terminate)
    :SegmentTwig{p_coords, "|", p_constraints, p_terminate}
{}

void TwigStraight::choose_next_segments()
{
    add_leaves();
    if (is_terminating)
        return;
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Left, 1},
                                    {Choice::Right, 1},
                                    {Choice::Split, 6}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}},
                                        {Choice::Right, {coords.x+1, coords.y+1}},
                                        {Choice::Split, {coords.x, coords.y+1}}};
    choose_twig_segment(probability, adj_coords);
}


TwigLeft::TwigLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints, bool p_terminate)
    :SegmentTwig{p_coords, "\\", p_constraints, p_terminate}
{}

void TwigLeft::choose_next_segments()
{
    add_leaves();
    if (is_terminating)
        return;
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Left, 1},
                                    {Choice::Split, 6},
                                    {Choice::SplitFlatRight, 6}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}},
                                        {Choice::Split, {coords.x-1, coords.y+1}},
                                        {Choice::SplitFlatRight, {coords.x-1, coords.y+1}}};
    choose_twig_segment(probability, adj_coords);
}



TwigRight::TwigRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints, bool p_terminate)
    :SegmentTwig{p_coords, "/", p_constraints, p_terminate}
{}

void TwigRight::choose_next_segments()
{
    add_leaves();
    if (is_terminating)
        return;
    std::map<Choice, int> probability {{Choice::Straight, 1},
                                    {Choice::Right, 1},
                                    {Choice::Split, 6},
                                    {Choice::SplitFlatLeft, 6}};
    std::map<Choice, Coords> adj_coords {{Choice::Straight, {coords.x, coords.y+1}},
                                        {Choice::Right, {coords.x+1, coords.y+1}},
                                        {Choice::Split, {coords.x, coords.y+1}},
                                        {Choice::SplitFlatLeft, {coords.x, coords.y+1}}};
    choose_twig_segment(probability, adj_coords);
}

TwigFlatLeft::TwigFlatLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints, bool p_terminate)
    :SegmentTwig{p_coords, "_", p_constraints, p_terminate}
{}

void TwigFlatLeft::choose_next_segments()
{
    add_leaves();
}

TwigFlatRight::TwigFlatRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints, bool p_terminate)
    :SegmentTwig{p_coords, "_", p_constraints, p_terminate}
{}

void TwigFlatRight::choose_next_segments()
{
    add_leaves();
}


TwigSplit::TwigSplit(Coords p_coords, std::shared_ptr<Constraints> p_constraints, bool p_terminate)
    :SegmentTwig{p_coords, "\\/", p_constraints, p_terminate}
{}

void TwigSplit::choose_next_segments()
{
    add_leaves();
    if (is_terminating)
        return;
    std::map<Choice, int> probability {{Choice::FlatLeft, 1},
                                    {Choice::Split, 1},
                                    {Choice::Left, 1}};
    std::map<Choice, Coords> adj_coords {{Choice::FlatLeft, {coords.x-1, coords.y+1}},
                                        {Choice::Split, {coords.x-1, coords.y+1}},
                                        {Choice::Left, {coords.x-1, coords.y+1}}};
    choose_twig_segment(probability, adj_coords, true);

    probability = {{Choice::FlatRight, 1},
                {Choice::Split, 1},
                {Choice::Right, 1}};

    if ((*(next_segs.end()-1))->get_glyph() == "\\/")   // disgusting pointer deferencing 
        probability[Choice::Split] = 0;                 // avoid splitting twice - looks messy.

    adj_coords = {{Choice::FlatRight, {coords.x+2, coords.y+1}},
                {Choice::Split, {coords.x+1, coords.y+1}},
                {Choice::Right, {coords.x+2, coords.y+1}}};
    choose_twig_segment(probability, adj_coords, true);
}


TwigSplitFlatLeft::TwigSplitFlatLeft(Coords p_coords, std::shared_ptr<Constraints> p_constraints, bool p_terminate)
    :SegmentTwig{p_coords, "_/", p_constraints, p_terminate}
{}

void TwigSplitFlatLeft::choose_next_segments()
{
    add_leaves();
}


TwigSplitFlatRight::TwigSplitFlatRight(Coords p_coords, std::shared_ptr<Constraints> p_constraints, bool p_terminate)
    :SegmentTwig{p_coords, "\\_", p_constraints, p_terminate}
{}

void TwigSplitFlatRight::choose_next_segments()
{
    add_leaves();
}



LeafGroup::LeafGroup(Coords p_coords, std::shared_ptr<Constraints> p_constraints, std::vector<Coords> p_leaf_coords, bool p_terminate=false)
    :Segment{p_coords, "&", p_constraints}, leaf_coords{p_leaf_coords}, is_terminating{p_terminate} 
{

}

void LeafGroup::choose_next_segments()
{
    if (is_terminating)
        return;
    bool terminate = false;
    std::vector<Coords> new_leaf_coords = {{leaf_coords[0].x-1, coords.y+1},
                                       {leaf_coords[1].x-1, coords.y-1},
                                       {leaf_coords[2].x+1, coords.y},
                                       {leaf_coords[3].x-1, coords.y}};
    if (leaf_coords.size() > 4)
    {
        new_leaf_coords.push_back({leaf_coords[4].x+1, coords.y+1});
        new_leaf_coords.push_back({leaf_coords[4].x+1, coords.y-1});
        terminate = true;
    }
    else
    {
        new_leaf_coords.push_back({leaf_coords[0].x+1, coords.y+1});
        new_leaf_coords.push_back({leaf_coords[1].x+1, coords.y-1});
    }

    next_segs.push_back(std::unique_ptr<Segment>{new LeafGroup{coords, constraints, new_leaf_coords, terminate}});
}

void LeafGroup::draw_segment()
{
    for (Coords& leaf : leaf_coords)
    {
        if (constraints->segment_locations[leaf.y][leaf.x] == '0')
        {
            std::cout << ANSI::move_cursor(leaf.x, leaf.y);
            std::cout << ANSI::set_colour(45,90,39) << glyph;
            constraints->segment_locations[coords.y][coords.x] = glyph[0]; // !
            std::cout.flush();
        }
    }
}