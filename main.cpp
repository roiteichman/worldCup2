#include <iostream>
#include "dynamicArray.h"
#include "DoubleHashing.h"
#include "unionFind.h"
#include "Team.h"
#include "Player.h"
#include "worldcup23a2.h"

int main() {
    world_cup_t wc;
    int a[5]  = {0,1,3,4,2};
    int b[5]  = {1,2,3,4,2};
    int c[5]  = {1,2,3,4,0};
    wc.add_team(2);
    wc.add_player(7, 2, a, 3, 4, 5, true);
    wc.add_player(8, 2, b, 3, 4, 5, true);
    wc.add_team(3);
    wc.add_player(15, 3, b, 3, 4, 5, true);
    wc.add_player(9, 3, c, 3, -2, 5, true);
    wc.add_team(4);
    wc.add_player(12, 4, c, 3, 4, 5, true);
    wc.add_player(10, 4, b, 3, 4, 5, true);
    wc.add_team(6);
    wc.add_player(83, 6, c, 3, 4, 5, true);
    wc.add_player(105, 5, a, 3, 4, 5, true);
    wc.add_team(5);
    wc.add_player(7, 6, a, 3, 4, 5, true);
    wc.add_player(7, 6, a, 3, 4, 5, true);
    wc.print();
    shared_ptr<Player> p15 = wc.getPlayer(15);
    wc.add_player_cards(7, 4);
    output_t<int> cards = wc.get_player_cards(7);
    output_t<int> winnerBy = wc.play_match(2, 4);
    output_t<int> ou = wc.get_team_points(2);
    StatusType st = wc.remove_team(2);
    StatusType st1 = wc.remove_team(2);




}
