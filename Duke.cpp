#include "Duke.hpp"
using namespace coup;

void Duke::block(Player &player){
    player.remove_coins(2);
};
void Duke::tax(){wallet+=3;};
TYPE Duke::get_type(){return TYPE::Duke;};