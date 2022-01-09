//
// Created by gilad on 09/01/2022.
//

#ifndef HW2_WET_PLAYERSMANAGER_H
#define HW2_WET_PLAYERSMANAGER_H

#include "library2.h"
#include "UnionFind.h"
#include "HashTable.h"
#include "Group.h"
#include "Player.h"
#include "AVLTree.h"

class PlayersManager {
public:
    int k;
    int scale;
    UnionFind *groups;
    HashTable<Player> *players;
    Group *all_game;

    PlayersManager(int k, int scale);

    StatusType mergeGroups(int GroupID1, int GroupID2);

    StatusType addPlayer(int PlayerID, int GroupID, int score);

    StatusType removePlayer(int PlayerID);

    StatusType increasePlayerIDLevel(int PlayerID, int LevelIncrease);

    StatusType changePlayerIDScore(int PlayerID, int NewScore);
};

#endif //HW2_WET_PLAYERSMANAGER_H