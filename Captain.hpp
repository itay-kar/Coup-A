#include "Player.hpp"
#pragma once

using namespace coup;

namespace coup
{
    class Game;
class Captain: public Player{
    public:
    Captain(Game& game,string name) : Player(game,name){};
    void block(Player& player);
    void steal(Player& player);
    TYPE get_type();
};
};