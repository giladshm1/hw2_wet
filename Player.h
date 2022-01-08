//
// Created by oriya on 05/12/2021.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H

#include "Comparator.h"

struct Group;

struct Player {
    int id;
    int level;
    Group* group;

    Player(int id, int level, Group* group) : id(id), level(level), group(group) {}

    static int compareById(const Player* p1, const Player* p2)
    {
        return Compare(p1->id, p2->id);
    }
    static int compareByLevel(const Player* p1, const Player* p2)
    {
            return p1->level == p2->level ? compareById(p2, p1) : Compare(p1->level, p2->level);
    }
};

#endif //WET1_PLAYER_H
