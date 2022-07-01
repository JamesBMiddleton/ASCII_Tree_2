#include "Forest/forest.h"
#include "Forest/terminal_abstractions.h"

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
    std::cout << std::flush << s << std::flush << ANSI::HIDE_CURSOR << std::flush;
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

    Constraints c{0, height / 2, (height / 3) * 2, 0, 
                {height, std::vector<char>(width, '0')}};

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(110));
        setup_screen(width, height);
        Forest forest{tree_num, width, height, c};
        forest.grow_trees(110);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    std::cout << ANSI::move_cursor(1, 1) << ANSI::SHOW_CURSOR << ANSI::RESET_COLOUR;
    return 0;
}

// TO DO:
// grab screen size automatically
