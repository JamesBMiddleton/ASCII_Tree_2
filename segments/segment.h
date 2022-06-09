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
    virtual std::vector<std::shared_ptr<Segment>> get_next_segments() = 0;
    virtual void draw_segment() = 0;
    
protected:
    Segment() {};
    Segment(Coords, std::string);
    Coords coords;
    std::string glyph;
};

#endif