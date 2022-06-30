#include "forest.h"

Forest::Forest(const int tree_num, const int width, const int height, Constraints constraints)
{
    const int x_border = width/5;
    const int adj_width = width - (2*x_border);
    const int tree_x_interval = (tree_num > 1)? adj_width / (tree_num -1) : 0;

    int x_pos = (tree_num > 1)? x_border : width/2;
    x_pos -= 3;
    for (int i{0}; i<tree_num; ++i)
    {
        tree_pool.push_back({constraints, {x_pos,1}});
        x_pos += tree_x_interval;
    }
}

void Forest::grow_trees(int growth_rate)
{
    int finished = 0;
    while (finished < tree_pool.size())
    {   
        finished = 0;
        for (Tree& tree : tree_pool)
        {
            if (tree.is_finished())
                finished++;
            else
                tree.grow_branches();
        }
        // std::cout << std::flush << ANSI::move_cursor(10,10) << finished << tree_pool.size() << std::flush; 
        std::this_thread::sleep_for(std::chrono::milliseconds(growth_rate));
    }  
}

