#include "doctest.h"

#include "Player.hpp"
#include "Duke.hpp"
#include "Assassin.hpp"
#include "Ambassador.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"
#include "Game.hpp"
using namespace coup;

#include <vector>
using namespace std;

TEST_CASE("Good Scenario")
{
    Game game;
    Captain rick{game, "rick"};
    Ambassador avi{game, "avi"};
    Contessa cont{game, "cont"};
    Duke duke(game, "guy");
    Assassin assassin(game, "asa");

    // init all players with 4 coins.
    for (size_t j = 0; j < 4; j++)
    {
        rick.income();
        avi.income();
        cont.income();
        duke.income();
        assassin.income();
    }
    // CHECK income function works.
    CHECK_EQ(rick.coins(), 4);

    rick.foreign_aid();
    // CHECK foreign_aid function works.
    CHECK_EQ(rick.coins(), 6);

    avi.transfer(assassin, rick);
    // rick should have 7 coins now.

    // Checking assassin coins is down by 1 and rick coins is up by 1, caused by transfer action.
    CHECK_EQ(rick.coins(), 7);
    CHECK_EQ(assassin.coins(), 3);

    cont.foreign_aid();
    CHECK_EQ(cont.coins(), 6);
    // Checking duke block action, and cont coins after this action.
    CHECK_NOTHROW(duke.block(cont));
    CHECK_EQ(cont.coins(), 4);

    // Checking assassin virtual coup with only 3 coins.
    CHECK_NOTHROW(assassin.coup(rick));
    CHECK_EQ(assassin.coins(), 0);

    // Rick is out of the game;;

    CHECK_EQ(game.players().size(), 5);

    avi.foreign_aid();
    cont.foreign_aid();
    CHECK_EQ(cont.coins(), 6);

    CHECK_NOTHROW(duke.block(cont));
    CHECK_EQ(cont.coins(), 4);
    CHECK_EQ(avi.coins(), 6);
    assassin.income();

    avi.income();
    cont.income();
    duke.tax();
    CHECK_EQ(duke.coins(), 7);
    assassin.foreign_aid();
    CHECK_NOTHROW(duke.block(assassin));
    CHECK_NOTHROW(avi.coup(duke));
    CHECK_EQ(avi.coins(), 0);
    cont.foreign_aid();

    CHECK(cont.coins() == 7);
    assassin.foreign_aid();
    CHECK_EQ(assassin.coins(), 3);

    avi.foreign_aid();
    CHECK_NOTHROW(cont.coup(assassin));
    avi.foreign_aid();
    cont.foreign_aid();
    avi.foreign_aid();
    cont.foreign_aid();
    avi.foreign_aid();
    cont.foreign_aid();
    avi.coup(cont);

    CHECK(game.winner() == avi.get_name());
};

TEST_CASE("Scenario 2")
{
    Game bad_game;
    Captain rick{bad_game, "rick"};
    Ambassador avi{bad_game, "avi"};
    Contessa cont{bad_game, "cont"};
    Duke duke(bad_game, "guy");
    Assassin assassin(bad_game, "asa");
    Assassin assassin2(bad_game, "asa2");

    // Players not playing in their turn.
    CHECK_THROWS(assassin.income());
    CHECK_THROWS(duke.tax());
    CHECK_THROWS(avi.transfer(duke, cont));
    CHECK_THROWS(rick.block(avi));

    // Round 1;
    rick.income();
    avi.foreign_aid();
    // Duke blocks foreign aid action.
    CHECK_NOTHROW(duke.block(avi));
    cont.income();
    duke.tax();
    assassin.foreign_aid();
    assassin2.foreign_aid();

    // Round 2;
    rick.foreign_aid();
    // Duke blocks foreign aid actions.
    CHECK_NOTHROW(duke.block(assassin));
    CHECK_NOTHROW(duke.block(rick));
    avi.income();
    cont.income();
    duke.tax();
    assassin.income();
    assassin2.foreign_aid();
    // income action cannot be blocked by any player should throw.
    CHECK_THROWS(duke.block(assassin));

    // Round 3
    // assassin doesnt have enough coins to coup , and its not his turn.
    CHECK_THROWS(assassin.coup(duke));
    rick.income();
    avi.transfer(assassin2, avi);
    CHECK_EQ(assassin2.coins(), 3);
    cont.foreign_aid();
    duke.tax();
    assassin.income();
    // assassin2 can coup rick , already got 3 coins.
    CHECK_NOTHROW(assassin2.coup(rick));
    CHECK_EQ(assassin2.coins(), 0);
    CHECK_NOTHROW(cont.block(assassin2));
    CHECK(bad_game.turn() == rick.get_name());

    // Round 4
    rick.income();
    avi.income();
    duke.coup(assassin2);
    // Contessa cannot block regular coup actions.
    CHECK_THROWS(cont.block(duke));
    assassin.income();

    // Round 5
    rick.income();
    avi.transfer(rick, avi);
    cont.income();
    duke.tax();
    assassin.coup(duke);

    // Round 6
    rick.income();
    avi.foreign_aid();
    cont.foreign_aid();
    // Contessa cannot block assassin after duke already out of the game.
    CHECK_THROWS(cont.block(assassin));
    assassin.foreign_aid();
    cout << rick.coins() << avi.coins() << cont.coins() << assassin.coins() << endl;

    // Round 7
    rick.foreign_aid();
    avi.foreign_aid();
    // cont have 10+ coins and must coup , cannot perform any other action.
    CHECK_THROWS(cont.income());
    CHECK_THROWS(cont.foreign_aid());
    cont.coup(rick);
    assassin.foreign_aid();

    // Round 8
    // avi have 10+ coins and must coup , cannot perform any other action.
    CHECK_THROWS(avi.income());
    CHECK_THROWS(avi.foreign_aid());
    CHECK_THROWS(avi.transfer(assassin, cont));
    avi.coup(cont);
    // cont cannot block avi coup;
    CHECK_THROWS(cont.block(avi));
    assassin.coup(avi);
    // cont is already out of the game cannot perform actions;
    CHECK_THROWS(cont.block(assassin));
    CHECK_EQ(bad_game.winner(), assassin.get_name());
}

TEST_CASE("All Operations")
{
    Game igame;
    Ambassador ambassador(igame, "avi");
    Duke duke(igame, "natan");
    Assassin assassin(igame, "joe");
    Duke juke(igame, "moran");
    Captain captain(igame, "ronit");
    Contessa contessa(igame, "mor");

    // Trying to add more than 6 players - Should throw;
    CHECK_THROWS(Duke mora(igame, "mora"));
    vector<string> vec = igame.players();

    ambassador.foreign_aid();
    // Should Throw not assassin turn
    CHECK_THROWS(assassin.income());
    duke.tax();
    assassin.income();
    juke.block(ambassador);
    juke.foreign_aid();
    duke.block(juke);
    // Should throw captain cant steal from contessa cause contessa doesnt have coins.
    CHECK_THROWS(captain.steal(contessa));
    CHECK_EQ(igame.turn(), captain.get_name());
    captain.steal(duke);
    CHECK_THROWS(captain.block(captain));
    contessa.income();
}

TEST_CASE("More than 1 game is active.")
{
    Game game_one;
    Game game_two;

    Duke duke_one(game_one, "rami");
    Duke duke_two(game_two, "rami");
    Contessa contessa_one(game_one, "nofar");
    Contessa contessa_two(game_two, "nofar");
    CHECK_THROWS(Duke duke_throw(game_one, "rami"));
    CHECK_THROWS(Contessa contessa_throw(game_two, "nofar"));

    duke_one.tax();
    duke_two.foreign_aid();
    contessa_one.foreign_aid();
    CHECK_THROWS(duke_two.block(contessa_one));
    duke_one.block(contessa_one);
    CHECK_EQ(contessa_one.coins(), 0);
    contessa_two.foreign_aid();
    CHECK_THROWS(duke_one.block(contessa_two));
    CHECK_EQ(contessa_two.coins(), 0);
    duke_one.tax();
    duke_two.tax();
    contessa_one.foreign_aid();
    contessa_two.foreign_aid();
    duke_one.tax();
    duke_two.tax();
    contessa_one.income();
    contessa_two.income();
    //Trying to coup a player from another game should throw exception
    CHECK_THROWS(duke_one.coup(contessa_two));
    CHECK_NOTHROW(duke_one.coup(contessa_one));
    CHECK_NOTHROW(duke_one.income());
    CHECK_EQ(game_one.winner(),duke_one.get_name());
    CHECK_THROWS(duke_two.coup(duke_one));
    CHECK_NOTHROW(duke_two.coup(contessa_one));
    
}