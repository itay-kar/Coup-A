#pragma once

#include "Player.hpp"
using namespace coup;

namespace coup
{
    class Game;
    class Contessa : public Player
    {
    public:
        Contessa(Game& game, string name) : Player(game, name){};
        void block(Player &player);
        TYPE get_type();
    };
};