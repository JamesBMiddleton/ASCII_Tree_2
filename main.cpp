#include "canvas.h"

void setup_screen(int x, int y)
// Prints a string of whitespace to clear the screen
// Removes the cursor
// Sets the screen max height and width 
{   
    TERMINAL_INFO::max_width = x;
    TERMINAL_INFO::max_height = y;
    int total{x*y};
    std::string s(total, ' ');
    std::cout << s << ANSI::HIDE_CURSOR;
    std::cout.flush();
}

int main(int argc, char* argv[])
{
    setup_screen(80, 24);
    Canvas canvas;
    canvas.grow_branches();
    std::cout << ANSI::move_cursor(1, 1) << ANSI::SHOW_CURSOR << ANSI::RESET_COLOUR;
    return 1;
}

// sort param naming
// sort messed up coords systems - goes from top left.  left = neg_x, right = pos_x, up = neg_y,  down = pos_y.  terminal takes y then x.