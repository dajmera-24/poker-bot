#pragma once
# include <string>
# include <Eigen/Dense>

namespace types{
    // All possible poker hands
    enum class hands {HIGH_CARD=10, ONE_PAIR=20, TWO_PAIR=30, TRIPS=40, STRAIGHT=50, FLUSH=60, QUADS=70, FULL_HOUSE=80, STRAIGHT_FLUSH=90, ROYAL_FLUSH=100};

    struct card {
        int value; // 2-14, but A is 14 and 1
        int suit; // 1=Spades, 2=Clubs, 3=Diamonds, 4=Hearts

        bool operator==(const card &other) const {
            return value == other.value && suit == other.suit;
        }
    };
}

namespace tables{
    Eigen::Matrix<float, 13, 13> init_hands;
}