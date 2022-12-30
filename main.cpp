#include <iostream>
#include "dynamicArray.h"
#include "DoubleHashing.h"
#include "unionFind.h"
#include "Team.h"
#include "Player.h"
#include "worldcup23a2.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Vector<int> a(0);
    int b =0, c=3, f=4;
    c+2>f? c=0: 4;
    5;
    world_cup_t wc;
    permutation_t* t = new permutation_t();
    Player* player = new Player(7, 2, *t, 3, 4, 5, true);
    DoubleHashing<int,int> dh;
    unionFind<int, Player, Team> uf;
    wc.add_player(7, 2, *t, 3, 4, 5, true);
    uf.insertValue(player, 7);
    dh.put(1, c);
    //dh.print();
    dh.put(2, c);
    dh.put(3, c);
    dh.put(4, c);
    dh.put(5, c);
    dh.put(7, c);
    //dh.print();
    int aa = *dh.get(5);
    dh.put(199, c);
    dh.put(9, c);
    dh.print();



    int i = a[2];
    return 0;
}
