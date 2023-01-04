#include <iostream>
#include "dynamicArray.h"
#include "DoubleHashing.h"
#include "unionFind.h"
#include "Team.h"
#include "Player.h"
#include "worldcup23a2.h"

int main() {
    world_cup_t *obj = new world_cup_t();
    int basePerm1[5] = {1, 2, 3, 4, 0};
    permutation_t perm1(basePerm1);
    int basePerm6[5] = {3, 3, 2, 3, 1};
    permutation_t not_good_perm(basePerm6);
    obj->add_player(0, 1, perm1, 1, 1, 1, true);
    StatusType t = obj->add_player(1, 1, not_good_perm, 1, 1, 1, true);
}
