#include "Game.hpp"
using namespace coup;

string Game::turn()
{
    cout << players_names.size() << " Curr Player : " << curr_player << endl;
    return players_names.at(curr_player);
};

vector<string> Game::players()
{
    vector<string> vec;
    for (size_t i = 0; i < players_names.size(); i++)
    {
        if (players_state[i] != "Eliminated" && players_state[i] != "Removed")
        {
            vec.push_back(players_names[i]);
        }
    }
    // cout << "players() size is " << players_names.size() << endl;
    return vec;
};

string Game::winner()
{
    int count = 0;
    size_t winner;
    for (size_t i = 0; i < players_state.size(); i++)
    {
        cout <<players_state[i] <<endl;
        if (players_state[i]!="Removed")
        {
            count+=1;
            winner=i;
        }
    }

    if (count!=1){throw invalid_argument("game still active.\n");}

    return players_names[winner];
    
};

size_t Game::add_player(string name)
{
    if (num_of_players < MAX_PLAYERS)
    {
        players_names[num_of_players] = name;

        num_of_players += 1;
        // cout << "Added Player " << name << " Successfully." <<endl;
        return num_of_players - 1;
    }

    throw invalid_argument("Game is for 6 pepole in max.\n");
};

void Game::eliminate(size_t id)
{
    players_state[id] = "Eliminated";
};

void Game::remove_player(size_t id)
{
    if (players_state[id] == "Removed" || players_state[id] == "Eliminated")
    {
        throw invalid_argument("Player was already couped.\n");
    }

    players_state[id] = "Removed";
};

void Game::revive(size_t id)
{
    if (players_state[id] == "Eliminated")
    {
        players_state[id] = "Active";
    }

    else throw invalid_argument("Cannot block ");
};
