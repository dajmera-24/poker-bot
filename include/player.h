#pragma once
# include <string>
# include <vector>

namespace game{
    struct player{
        bool is_me;
        int id;
        double stack_size;
        double bluff_val = 0.5;
    };
}