#pragma once
# include <string>
# include <vector>

namespace game{
    struct player{
        bool is_me;
        int id;
        double stack_size;
        double fold_tend = 0.0; // Here, 1.0 represents a person who will fold every single hand they have
        double call_tend = 0.0; // Here, 1.0 represents a person who will call every single hand they have
        double raise_tend = 0.0; // Here, 1.0 represents a person who will raise every single hand they have
        bool in_round = true;
        bool in_game = true;
        double curr_bet = 0.0;
    };
}