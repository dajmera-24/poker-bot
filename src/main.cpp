# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <algorithm>
# include <cmath>
# include "types.h"
# include "player.h"

/*Private player cards*/
types::card card_one;
types::card card_two;

/*Community cards*/
types::card flop_one;
types::card flop_two;
types::card flop_three;
types::card turn;
types::card river;

/*Ingame metrics*/
double stack_size;
double big_blind;
std::vector<double> bets;
std::vector<int> positions; //may not need to store this, as all other players positions can be determined using curr_pos + i modulo n
std::vector<game::player> players;
double curr_bet;
int n; //number of players sitting at the table
int curr_pos;
int rounds;

/*Betting logic*/
std::vector<std::vector<double>> chen_table; //cards are mapped to the index v-2, where v is the value of the card (2-14)

/*Poker playing agent receives input of current pot size and previous bets at each iteration*/
std::vector<std::string> line_split(const std::string& s, const char delim){
    std::vector<std::string> result;
    std::string curr;

    for (char c : s) {
        if (c == delim) {
            result.push_back(curr);
            curr.clear();
        }
        else {curr.push_back(c);}
    }

    if (!curr.empty()) {result.push_back(curr);}

    return result;
}

/*If r < c, then the cards are suited. When r >= c, they are offsuit (includes pocket pairs)*/
void chen_init() {
    chen_table = std::vector<std::vector<double>>(13, std::vector<double>(13));
    std::ifstream inputFile("data/start_hands_pflop_vals.csv");
    if (!inputFile.is_open()) {
        std::cerr << "Error: cannot open the file." << std::endl;
    }
    std::string line;

    std::getline(inputFile, line);

    while(std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string s1,s2;

        std::getline(ss, s1, ',');
        std::getline(ss, s2, ',');

        std::vector<std::string> seq = line_split(s1, ';');
        int score = std::stod(s2);
        seq.pop_back();
        int col = std::stoi(seq.back());
        seq.pop_back();
        int row = std::stoi(seq.back());
        chen_table[row-2][col-2] = score;
    }
    inputFile.close();
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
    chen_init();
    /* Initial game setup module */
    std::cout << "Enter the starting stack size in dollars. >>>";
    std::cin >> stack_size;
    if (stack_size < 0) {throw std::invalid_argument("Stack size cannot be negative.");}

    std::cout << "Enter the big blind size in dollars. >>>";
    std::cin >> big_blind;
    if (big_blind < 0 || big_blind > stack_size) {throw std::invalid_argument("Such a big blind cannot exist.");}

    std::cout << "Enter the number of players at the table. >>>";
    std::cin >> n;
    if (n < 0 || n > 9) {throw std::invalid_argument("Such a number of players cannot exist.");}

    std::cout << "Enter the starting position at the table (place in line to play preflop, where UTG is 1). There are as many positions as there are players. >>>";
    std::cin >> curr_pos;
    if (curr_pos > n || curr_pos < 0) {throw std::invalid_argument("Such a position cannot exist.");}

    players = std::vector<game::player>(n);
    for (int i = 0; i < n; i++) {
        if (i == curr_pos) {players[i] = game::player{true, i, stack_size};}
        players[i] = game::player{false, i, stack_size};
    }
    bets = std::vector<double>(n);

    /* Condition for continuing to play the game: our player must be in and at least one other player must be in as well */
    while (players[curr_pos].in_game && std::any_of(players.begin(), players.end(), [&](const auto& p) {return &p != &players[curr_pos] && p.in_game})) {
        
        /*Preflop play module*/
        std::string line;
        std::cout << "Enter the numeric value of first card and suit, comma separated. Ace = 14, Spades = 1, Clubs = 2, Diamonds = 3, Hearts = 4. >>> ";
        std::cin >> line;
        std::vector<std::string> temp = line_split(line, ',');
        int suit = stoi(temp.back());
        temp.pop_back();
        int val = stoi(temp.back());
        card_one = types::card{val, suit};

        std::cout << "Enter the numeric value of second card and suit, comma separated. Ace = 14, Spades = 1, Clubs = 2, Diamonds = 3, Hearts = 4. >>> ";
        std::cin >> line;
        temp = line_split(line, ',');
        suit = stoi(temp.back());
        temp.pop_back();
        val = stoi(temp.back());
        card_two = types::card{val, suit};

        if (!check_validity()) {throw std::invalid_argument("Such a combination of cards cannot exist.");}
        
        int chen_val;
        if (card_one.suit == card_two.suit) {chen_val = chen_table[std::min(card_one.value, card_two.value)-2][std::max(card_one.value, card_two.value)-2];}
        else {chen_val = chen_table[std::max(card_one.value, card_two.value) - 2][std::min(card_one.value, card_two.value) - 2];}

        // Heuristic of benefit from betting late; aligns with the notion of bb and sb wanting to play, as they are already partially invested
        // f(1) = 1 (UTG), f(n) = 1.5 (BB)
        double multiplier = std::pow(1.5,(curr_pos-1)/(n-1));
        double preflop_score = chen_val * multiplier;

        // Cutoff determinants for preflop actions based on score: fold, limp, raise
        // Raises will have their own multiplier determined by how much the score exceeds the threshold (how many BB?)
    }


    return 0;
}
