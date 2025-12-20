#pragma once

namespace types{
    // All possible poker hands
    enum class hands {HIGH_CARD=10, ONE_PAIR=20, TWO_PAIR=30, TRIPS=40, STRAIGHT=50, FLUSH=60, QUADS=70, FULL_HOUSE=80, STRAIGHT_FLUSH=90, ROYAL_FLUSH=100}; 
    enum class cards {ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, KING, QUEEN, ACE};
    enum class suits {SPADES, CLUBS, DIAMONDS, HEARTS};
}