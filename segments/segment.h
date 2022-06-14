#ifndef SEGMENT_H_
#define SEGMENT_H_

#include <string>
#include <vector>
#include <iostream>
#include <memory>

struct Coords {int x, y;};

struct Segment
{   
    virtual ~Segment() {};
    virtual void choose_next_segments() = 0;
    virtual void draw_segment();
    std::vector<std::unique_ptr<Segment>>& get_next_segments() {return next_segs;}
protected:
    std::vector<std::unique_ptr<Segment>> next_segs;
    Segment() {};
    Segment(Coords, std::string);
    Coords coords;
    std::string glyph;
};

#endif