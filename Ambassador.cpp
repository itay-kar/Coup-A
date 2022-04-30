#include "Ambassador.hpp"
using namespace coup;

    void Ambassador::block(Player& player){};
    void Ambassador::transfer(Player& player,Player& player_b){
        if(player.coins()>0){
            Player::move(player,player_b);
        }
    };
    TYPE Ambassador::get_type(){return TYPE::Ambassador;};