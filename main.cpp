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
    const int width = 80;
    const int height = 24;
    
    srand(time(NULL));
    int tree_num = 3;
    for (int i{0}; i<argc; ++i)
    {
        std::string arg = std::string(argv[i]);
        if (arg == "--seed")
            srand(std::stoi(argv[i+1]));
        if (arg == "--tree_num")
            tree_num = std::stoi(argv[i+1]);
    }

    const int x_border = width/5;
    const int adj_width = width - (2*x_border);
    const int tree_x_interval = (tree_num > 1)? adj_width / (tree_num -1) : 0;

    Constraints c{0, height / 2, (height / 3) * 2, 0, 
                {height, std::vector<char>(width, '0')}};

    while (true)
    {
        setup_screen(width, height);
        int x_pos = (tree_num > 1)? x_border : width/2;
        x_pos -= 3;
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

// TO DO:
// grab screen size automatically
