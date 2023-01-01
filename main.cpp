#include <iostream>
#include "dynamicArray.h"
#include "DoubleHashing.h"
#include "unionFind.h"
#include "Team.h"
#include "Player.h"
#include "worldcup23a2.h"

int main() {
    world_cup_t wc;
    permutation_t* t = new permutation_t();
    wc.add_team(2);
    wc.add_player(7, 2, *t, 3, 4, 5, true);
    wc.add_player(8, 2, *t, 3, 4, 5, true);
    wc.add_team(3);
    wc.add_player(15, 3, *t, 3, 4, 5, true);
    wc.add_player(9, 3, *t, 3, -2, 5, true);
    wc.add_team(4);
    wc.add_player(7, 4, *t, 3, 4, 5, true);
    wc.add_player(10, 4, *t, 3, 4, 5, true);
    wc.add_team(6);
    wc.add_player(83, 6, *t, 3, 4, 5, true);
    wc.add_player(105, 5, *t, 3, 4, 5, true);
    wc.add_team(5);
    wc.add_player(7, 6, *t, 3, 4, 5, true);
    wc.add_player(7, 6, *t, 3, 4, 5, true);
    wc.print();
    shared_ptr<Player> p15 = wc.getPlayer(15);
    StatusType st = wc.remove_team(2);
    StatusType st1 =wc.remove_team(2);
}
