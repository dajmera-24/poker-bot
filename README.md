# Poker Bot
This bot serves to autonomously dictate the most effective course of action in a game of "Texas Hold 'em" poker.
## Setup
1. Clone Repo
2. Download and extract Eigen: https://eigen.tuxfamily.org
3. Add to local directory

## v1.0
The preliminary implementation of this bot utilizes the Chen Formula to dictate the strength of its hole cards preflop. This heuristic does not take into account the number of players, stack size, or various other factors. Changes including a more detailed algorithm will follow in future versions.

![Chen Values of All Starting Hands](./figures/st_hnd_chn_scrs.png)

The .py script used to generate this heatmap, along with the .csv file of all of these values can be found in the aux_scripts subdirectory.

### Current Decision-Making
1. Preflop, the bot will determine the strength of its hand according to the Chen Formula. It's position at the table will affect the hands it is willing to play (later        positioning enables it to play otherwise weaker hands). The bot will document all other player's bets and actions to inform its later actions. Currently, as a heuristic, we multiply our chen value by 
    $$
    f(x) = 1.5^{\frac{x-1}{n-1}}, \quad 1 \le x \le n,
    $$
    where $n$ is the number of players at the table, and $x$ is our position (UTG is 1, and BB is $n$).

2. 

### Current Limitations
1. This implementation assumes that the big blind will remain constant throughout the entire game.
2. The program will simply throw an exception if any invalid values are enter (e.g. a negative number of players at the table).