#include "tree.h"

#include <chrono>

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
    srand(time(NULL));
    setup_screen(80, 24);
    Constraints c{0,0,0,0, {0,0,0}, {0,0,0}};
    Tree tree{c};
    tree.grow_branches();
    std::cout << ANSI::move_cursor(1, 1) << ANSI::SHOW_CURSOR << ANSI::RESET_COLOUR;
    return 1;
}

// current choose_segment implementation involves a lot of copied code... there must be a better
// solution. I hope its not an inherent problem with the design.

// Arm coords need tweaking.