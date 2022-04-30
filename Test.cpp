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
    CHECK_EQ(rick.coins(), 4);

    rick.foreign_aid();

    CHECK_EQ(rick.coins(), 6);

    avi.transfer(assassin, rick);
    // rick should have 7 coins now.

    CHECK_EQ(rick.coins(), 7);
    CHECK_EQ(assassin.coins(), 3);

    cont.foreign_aid();
    CHECK_EQ(cont.coins(), 6);

    CHECK_NOTHROW(duke.block(cont));
    CHECK_EQ(cont.coins(), 4);

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

TEST_CASE("Bad Operations")
{
    Game bad_game;
    Captain rick{bad_game, "rick"};
    Ambassador avi{bad_game, "avi"};
    Contessa cont{bad_game, "cont"};
    Duke duke(bad_game, "guy");
    Assassin assassin(bad_game, "asa");
    Assassin assassin2(bad_game, "asa2");

    CHECK_THROWS(assassin.income());
    CHECK_THROWS(duke.tax());
    CHECK_THROWS(avi.transfer(duke, cont));
    CHECK_THROWS(rick.block(avi));

    // Round 1;
    rick.income();
    avi.foreign_aid();
    CHECK_NOTHROW(duke.block(avi));
    cont.income();
    duke.tax();
    assassin.foreign_aid();
    assassin2.foreign_aid();

    // Round 2;
    rick.foreign_aid();
    CHECK_NOTHROW(duke.block(assassin));
    CHECK_NOTHROW(duke.block(rick));
    avi.income();
    cont.income();
    duke.tax();
    assassin.income();
    assassin2.foreign_aid();
    CHECK_THROWS(duke.block(assassin));

    // Round 3
    CHECK_THROWS(assassin.coup(duke));
    rick.income();
    avi.transfer(assassin2, avi);
    CHECK_EQ(assassin2.coins(), 3);
    cont.foreign_aid();
    duke.tax();
    assassin.income();
    assassin2.coup(avi);
    CHECK_EQ(assassin2.coins(), 0);
    CHECK_NOTHROW(cont.block(assassin2));

    // Round 4
    rick.income();
    avi.income();
    duke.coup(assassin2);
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
    CHECK_THROWS(cont.block(assassin));
    assassin.foreign_aid();
    cout << rick.coins() << avi.coins() << cont.coins() << assassin.coins()<< endl;

    // Round 7
    rick.foreign_aid();
    avi.foreign_aid();
    CHECK_THROWS(cont.income());
    CHECK_THROWS(cont.foreign_aid());
    cont.coup(rick);
    assassin.foreign_aid();

    //Round 8
    CHECK_THROWS(avi.income());
    CHECK_THROWS(avi.foreign_aid());
    CHECK_THROWS(avi.transfer(assassin,cont));
    avi.coup(cont);
    CHECK_THROWS(cont.block(avi));
    assassin.coup(avi);
    CHECK_THROWS(cont.block(assassin));
    CHECK_EQ(bad_game.winner(),assassin.get_name());

}