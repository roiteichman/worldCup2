#include <iostream>
#include "dynamicArray.h"
#include "DoubleHashing.h"
#include "unionFinf.h"
#include "Team.h"
#include "Player.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    Vector<int> a(0);
    int b =0, c=3, f=4;
    c+2>f? c=0: 4;
    5;
    Player* player = new Player(7, 2, 3, 4, 5, 6);
    DoubleHashing<int,int> dh;
    unionFind<int, Player, Team> uf;
    uf.insert(player);
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
