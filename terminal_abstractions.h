#ifndef TERMINAL_ABSTRACTIONS_H_
#define TERMINAL_ABSTRACTIONS_H_

#include <string>
#include <sstream>

struct TERMINAL_INFO
{
    static int max_width;
    static int max_height;
};

namespace ANSI
{
    const std::string CSI = "\x1b[";
    const std::string HIDE_CURSOR = CSI + "?25l";
    const std::string SHOW_CURSOR = CSI + "?25h";
    const std::string RESET_COLOUR = CSI + 'm';

    inline std::string move_cursor(int x, int y) 
        {std::ostringstream oss; oss << CSI << TERMINAL_INFO::max_height-y << ';' << x << 'H'; return oss.str();} // y axis is backwards.
    inline std::string set_colour(int r, int g, int b) 
        {std::ostringstream oss; oss << CSI << "38;2;" << r << ';' << g << ';' << b << 'm'; return oss.str();}
}

// should inline functions be all caps? "MOVE_CURSOR"?
// I need to know the width and height of the screen in multiple files... I'm not sure whether TERMINAL_INFO is a good solution...

#endif