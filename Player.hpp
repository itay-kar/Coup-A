#pragma once
#include "Game.hpp"
using namespace coup;

const int SEVEN = 7;

namespace coup
{
    class Game;

    enum class TYPE
    {
        Contessa,
        Captain,
        Ambassador,
        Assassin,
        Duke,
        Player
    };

    enum class Action
    {
        block,
        tax,
        income,
        coup,
        foreign_aid,
        steal
    };

    class Player
    {

    protected:
        size_t id;
        int wallet;
        string name;
        Game &game;
        Action last;

        void move(Player &player_a, Player &player_b);

    public:
        Player();
        Player(Game &new_game, string name) : game(new_game), name(name)
        {
            id = new_game.add_player(name);
            wallet = 0;
        };
        void income();
        void foreign_aid();
        virtual void coup(Player &player);
        int coins() const;

        size_t get_id() { return id; }

        virtual TYPE get_type();

        string get_name();

        void remove_coins(int n);

        Action get_last_action();
    };
};