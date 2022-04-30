#include "Player.hpp"
#pragma once

using namespace coup;

namespace coup
{
    class Game;
    class Ambassador : public Player
    {
    public:
        Ambassador(Game& game, string name) : Player(game, name){};
        void block(Player &player);
        void transfer(Player &player, Player &player_b);
        TYPE get_type();
    };
};