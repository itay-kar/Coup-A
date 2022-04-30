#include "Player.hpp"

#pragma once

namespace coup
{
    class Game;

    class Assassin : public Player
    {
    public:
        Assassin(Game& game, string name) : Player(game, name){};
        void coup(Player& player){
            if (wallet>=3){
                game.eliminate(player.get_id());
                wallet-=3;
            }
        };

        TYPE get_type();
    };
};