#include "Captain.hpp"
using namespace coup;

void Captain::block(Player &player)
{
    if (player.get_type() == TYPE::Captain)
    {
        game.turn();
        cout << "Class is Captain" << endl;
    }

    else
    {
        cout << "Class is not Captain" << endl;
    }
};
void Captain::steal(Player &player){};

TYPE Captain::get_type() { return TYPE::Captain; };