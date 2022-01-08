//
// Created by oriya on 05/12/2021.
//

#ifndef WET1_GROUP_H
#define WET1_GROUP_H


#include "AVLTree.h"
#include "Player.h"

struct Group {
    int id;
    int size;
    Player *playerWithMaxLevel;
    AVLTree<Player> players;

    explicit Group(int id) : id(id), size(0), playerWithMaxLevel(nullptr), players(Player::compareByLevel) {}

    Group() = default;

    static int compareById(const Group *g1, const Group *g2) {
        return Compare(g1->id, g2->id);
    }
};


#endif //WET1_GROUP_H
