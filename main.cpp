#include "canvas.h"

int main(int argc, char* argv[])
{
    Canvas canvas;
    canvas.grow_branches();
    return 1;
}

// Check for memory leaks
// Work out if shared_ptr is what I need, whether I can use a unique_ptr, because I don't actually more than one ptr
// Start using 'using vector' or whatever it is.
// Workout how I want to implement the segment classes, e.g. the fact that I'm constantly creating the glyphs etc...