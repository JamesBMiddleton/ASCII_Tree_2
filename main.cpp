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
    const int tree_num = 3;
    const int width = 80;
    const int height = 24;
    const int max_trunk_height = height / 2;
    const int max_arm_height = (height / 3) * 2;
    
    const int border = 10;
    const int tree_x_interval = width / tree_num; //((width - (border*2)) / tree_num) + 3;

    Constraints c{0,
        max_trunk_height,
        max_arm_height,
        0,
        {0,0,0},
        {0,0,0},
        {height, std::vector<char>(width, '0')}
    };

    while (true)
    {
        setup_screen(width, height);
        int x_pos = border;
        for (int i{0}; i<tree_num; ++i)
        {
            Tree tree{c, {x_pos,1}};
            tree.grow_branches();
            x_pos += tree_x_interval;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    std::cout << ANSI::move_cursor(1, 1) << ANSI::SHOW_CURSOR << ANSI::RESET_COLOUR;
    return 0;
}


// grab screen size automatically
// allow num of trees to be specified
// fix spacing between different number of trees
