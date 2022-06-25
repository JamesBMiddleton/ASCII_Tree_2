#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "../terminal_abstractions.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>

struct Coords {int x, y;};

struct Colour {int r, g, b;};

struct Constraints
{
    int max_height;
    int max_trunk_height;
    int max_arm_height;
    int max_twig_height;

    Colour wood;
    Colour leaves;

    std::vector<std::vector<char>> segment_locations;

    bool has_hollow = false;
};

struct Segment
// Abstract base class for all Segment types.
{   
    virtual ~Segment() {};
    virtual void choose_next_segments() = 0;
    virtual void draw_segment();
    std::vector<std::unique_ptr<Segment>>& get_next_segments() {return next_segs;}
    const std::string& get_glyph() {return glyph;}
protected:
    std::vector<std::unique_ptr<Segment>> next_segs;
    Segment(Coords, std::string, std::shared_ptr<Constraints>);
    Coords coords;
    std::string glyph;
    std::shared_ptr<Constraints> constraints;
private:
    Segment() {};
};



struct SegmentBase : public Segment
{
    void choose_next_segments() override;
    SegmentBase(Coords, std::shared_ptr<Constraints>);
    ~SegmentBase() {};
};

#endif