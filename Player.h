//
// Created by oriya on 05/12/2021.
//

#ifndef WET2_PLAYER_H
#define WET2_PLAYER_H

#include "Comparator.h"

struct Player {
    int id;
    int score;
    int group_id;
    int level;

    Player(int id, int score, int group_id, int level = 0) : id(id), score(score), group_id(group_id), level(level) {}

    static int compareById(const Player *p1, const Player *p2) {
        return Compare(p1->id, p2->id);
    }

    static int compareByLevel(const Player *p1, const Player *p2) {
        return p1->level == p2->level ? compareById(p2, p1) : Compare(p1->level, p2->level);
    }
};

#endif //WET2_PLAYER_H
