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


// Make leaves segments
// fix segmentation fault?
// add hollow

// I can't create different types of trees when the real constraints are magic constants in 
// every individual choose_next_segments() implementation.

// I need to have a brain storm about ensuring separation between twig segments,
// and spreading the tree out further.
// Once we go into twigs, it need to be local groupings of twigs, trying to expand out more than up
// Maybe completely remove single twigs, only have split ones that create more splits

// I need a better way to implement choose_next_segments()
// There raffle and choice thing introduces magic literals
// I'm copying so much code which is a sign the design is bad... :(