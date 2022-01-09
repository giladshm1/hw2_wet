//
// Created by oriya on 05/12/2021.
//

#ifndef WET2_GROUP_H
#define WET2_GROUP_H


#include "AVLTree.h"
#include "Player.h"

struct Group {
    static const int max_score = 201;

    int id;
    int size_uf;
    int counter_level0;
    int *level0_score_histogram;
    AVLTree<Player> players_by_level;
    AVLTree<Player> *arr_score_players_by_level[max_score];

    explicit Group(int id);

    Group() = default;

    void mergeData(Group *other);

    void deletePlayer(Player* player);

    void addPlayer(Player* player);

   /* static int compareById(const Group *g1, const Group *g2) {
        return Compare(g1->id, g2->id);
    }*/
};


#endif //WET2_GROUP_H
