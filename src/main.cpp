# include <iostream>
# include "types.h"

using namespace types;
using namespace std;

int main() {
    types::hands my_hand = types::hands::FLUSH;
    string s;
    cout << "Enter the first card and suit, comma separated >>> ";
    cin >> s;
}
