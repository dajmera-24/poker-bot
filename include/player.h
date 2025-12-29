#pragma once
# include <string>
# include <vector>

namespace game{
    struct player{
        bool is_me;
        int id;
        double stack_size;
        double bluff_val = 0.5;
        bool in_round = true;
        bool in_game = true;
        double curr_bet = 0.0;
    };
}