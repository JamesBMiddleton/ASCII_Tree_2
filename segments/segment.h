#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <string>
#include <set>
#include <iostream>

struct Coords {int x, y;};

struct Segment
{
    virtual void next_segment();
    virtual void draw_segment();
protected:
    Coords coords;
    std::string glyph;
    Segment* prev_segment;
    static std::set<Segment*>& branch_pool;  // static members cannot be inherited
    Segment(Coords, std::string, Segment*);
};

#endif