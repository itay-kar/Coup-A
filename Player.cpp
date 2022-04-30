#include "Player.hpp"
using namespace coup;

void Player::income() { this->wallet += 1; };
void Player::foreign_aid()
{
    this->wallet += 2;
    last = Action::foreign_aid;
};
void Player::coup(Player &player)
{
    if (wallet >= SEVEN)
    {
        cout << player.id << endl;
        game.remove_player(player.id);
        wallet-= SEVEN;
        last = Action::coup;
    }
};
int Player::coins() const { return wallet; };

TYPE Player::get_type() { return TYPE::Player; };

string Player::get_name() { return name; };

Action Player::get_last_action() { return last; }

void Player::move(Player &player_a, Player &player_b)
{
    game.turn();
    player_a.wallet -= 1;
    player_b.wallet += 1;
};

void Player::remove_coins(int n)
{
    if (last != Action::foreign_aid)
    {
        throw invalid_argument("Cannot Block this operation.\n");
    }

    wallet -= 2;
};
