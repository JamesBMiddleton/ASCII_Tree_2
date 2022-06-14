#include "canvas.h"

void clear_screen(int x, int y)
// Prints a string of whitespace to clear the screen and removes the cursor.
{
    int total{x*y};
    std::string s(total, ' ');
    std::cout << s << "\x1b[?25l"; // CONSTANTS
    std::cout.flush();
}

int main(int argc, char* argv[])
{
    clear_screen(24, 80);
    Canvas canvas;
    canvas.grow_branches();
    std::cout << "\x1B[" << 24 << ";" << 1 << "H" << "\x1b[?25h";  // returns cursor to bottom of terminal. CONSTANTS IN NAMESPACE.
    return 1;
}

// sort param naming
// add constants
// sort colour member for segments
// sort messed up coords systems - goes from top left.  left = neg_x, right = pos_x, up = neg_y,  down = pos_y.  terminal takes y then x.