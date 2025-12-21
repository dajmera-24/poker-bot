# include <iostream>
# include <string>
# include <vector>
# include "types.h"

using namespace types;
using namespace std;

card card_one;
card card_two;

vector<string> comma_split(const string& s){
    vector<string> result;
    string curr;

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
    types::hands my_hand = types::hands::FLUSH;
    string line;
    cout << "Enter the numeric value of first card and suit, comma separated. Ace = 14, Spades = 1, Clubs = 2, Diamonds = 3, Hearts = 4. >>> ";
    cin >> line;
    vector<string> temp = comma_split(line);
    int suit = stoi(temp.back());
    temp.pop_back();
    int val = stoi(temp.back());
    card_one = card{val, suit};

    cout << "Enter the numeric value of second card and suit, comma separated. Ace = 14, Spades = 1, Clubs = 2, Diamonds = 3, Hearts = 4. >>> ";
    cin >> line;
    temp = comma_split(line);
    suit = stoi(temp.back());
    temp.pop_back();
    val = stoi(temp.back());
    card_two = card{val, suit};

    if (!check_validity()) {throw invalid_argument("Such a combination of cards cannot exist.");}
}
