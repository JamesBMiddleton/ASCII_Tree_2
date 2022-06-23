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
    while (true)
    {
        setup_screen(80, 24);
        Constraints c{0,12,16,0, {0,0,0}, {0,0,0}, {24, std::vector<char>(80, '0')}};

        Tree tree1{c, {10,1}};
        tree1.grow_branches();
        Tree tree2{c, {35,1}};
        tree2.grow_branches();
        Tree tree3{c, {60,1}};
        tree3.grow_branches();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    std::cout << ANSI::move_cursor(1, 1) << ANSI::SHOW_CURSOR << ANSI::RESET_COLOUR;
    return 1;
}


// tweak probabilities
// tweak which twigs follow others
// fix segmentation fault when leaving screen?
