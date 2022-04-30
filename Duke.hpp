#pragma once

#include "Player.hpp"
using namespace coup;

namespace coup
{
    class Game;

    class Duke : public Player
    {
    public:
        Duke(Game& game, string name) : Player(game, name){};
        void block(Player &player);
        void tax();
        TYPE get_type();
    };
};