# include <iostream>
# include <string>
# include <vector>
# include "types.h"
# include "player.h"

types::card card_one;
types::card card_two;
double stack_size;
double big_blind;
std::vector<double> bets;
std::vector<bool> in_game;
std::vector<int> positions; //may not need to store this, as all other players positions can be determined using curr_pos + i modulo n
std::vector<game::player> players;
double curr_bet;
int n; //number of players sitting at the table
int curr_pos;
int rounds;


std::vector<std::string> comma_split(const std::string& s){
    std::vector<std::string> result;
    std::string curr;

    for (char c : s) {
        if (c == ',') {
            result.push_back(curr);
            curr.clear();
        }
        else {curr.push_back(c);}
    }

    if (!curr.empty()) {result.push_back(curr);}

    return result;
}

bool check_validity() {
    if (card_one.value > 14 || card_one.value < 2) {return false;}
    if (card_two.value > 14 || card_two.value < 2) {return false;}
    if (card_one.suit > 4 || card_one.suit < 0) {return false;}
    if (card_two.suit > 4 || card_two.suit < 0) {return false;}
    if (card_one == card_two) {return false;}

    return true;
}

int main() {
    // Initial game setup module
    std::cout << "Enter the starting stack size in dollars. >>>";
    std::cin >> stack_size;
    if (stack_size < 0) {throw std::invalid_argument("Stack size cannot be negative.");}

    std::cout << "Enter the big blind size in dollars. >>>";
    std::cin >> big_blind;
    if (big_blind < 0 || big_blind > stack_size) {throw std::invalid_argument("Such a big blind cannot exist.");}

    std::cout << "Enter the number of players at the table. >>>";
    std::cin >> n;
    if (n < 0) {throw std::invalid_argument("Such a number of players cannot exist.");}

    std::cout << "Enter the starting position at the table (place in line to play, where UTG is 1). There are as many positions as there are players. >>>";
    std::cin >> curr_pos;
    if (curr_pos > n || curr_pos < 0) {throw std::invalid_argument("Such a position cannot exist.");}

    players = std::vector<game::player>(n);
    for (int i = 0; i < n; i++) {
        if (i == curr_pos) {players[i] = game::player{true, i, stack_size};}
        players[i] = game::player{false, i, stack_size};
    }


    // Preflop play module
    std::string line;
    std::cout << "Enter the numeric value of first card and suit, comma separated. Ace = 14, Spades = 1, Clubs = 2, Diamonds = 3, Hearts = 4. >>> ";
    std::cin >> line;
    std::vector<std::string> temp = comma_split(line);
    int suit = stoi(temp.back());
    temp.pop_back();
    int val = stoi(temp.back());
    card_one = types::card{val, suit};

    std::cout << "Enter the numeric value of second card and suit, comma separated. Ace = 14, Spades = 1, Clubs = 2, Diamonds = 3, Hearts = 4. >>> ";
    std::cin >> line;
    temp = comma_split(line);
    suit = stoi(temp.back());
    temp.pop_back();
    val = stoi(temp.back());
    card_two = types::card{val, suit};

    if (!check_validity()) {throw std::invalid_argument("Such a combination of cards cannot exist.");}
}
