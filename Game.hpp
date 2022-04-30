#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <array>

using namespace std;

const int MAX_PLAYERS = 6;

namespace coup
{
    class Game
    {
    private:
        size_t curr_player;
        size_t num_of_players;
        vector<string> players_names;
        vector<string> players_state;

    public:
        Game()
        {
            curr_player = 0;
            num_of_players = 0;
            players_names = vector<string>(6);
            players_state = vector<string>(6);
        };

        string turn();
        vector<string> players();
        string winner();
        size_t add_player(string name);
        void eliminate(size_t id);
        void remove_player(size_t id);
        void revive(size_t id);
        
    };

};