//
// Created by gilad on 09/01/2022.
//

#include "PlayersManager.h"

PlayersManager::PlayersManager(int k, int scale) : k(k), scale(scale), groups(nullptr), players(nullptr),
                                                   all_game(nullptr) {
    if (k <= 0 || scale <= 0 || scale > 200)
        throw std::exception();
    //TODO: catch the exception in library

    all_game = new Group(0);
    groups = new UnionFind(k + 1);
    players = new HashTable<Player>();
}

StatusType PlayersManager::mergeGroups(int groupID1, int groupID2) {
    if (groupID1 <= 0 || groupID2 <= 0 || groupID1 > k || groupID2 > k) {
        return INVALID_INPUT;
    }

    groups->Union(groups->Find(groupID1), groups->Find(groupID2));
    return SUCCESS;
}

StatusType PlayersManager::addPlayer(int playerID, int groupID, int score) {
    if (groupID <= 0 || groupID > k || playerID <= 0 || score <= 0 || score > this->scale) {
        return INVALID_INPUT;
    }
    if (players->findItem(playerID) != NULL) {
        return FAILURE;
    }

    // notice that we didn't insert the new player into the AVL trees, because of the
    // required time limits of the function.

    all_game->counter_level0++;
    all_game->level0_score_histogram[score]++;

    Group *group = groups->Find(groupID);
    group->counter_level0++;
    group->level0_score_histogram[score]++;

    Player *player = new Player(playerID, score, groupID);
    players->insertItem(player->id, player);

    return SUCCESS;
}

StatusType PlayersManager::removePlayer(int playerID) {
    if (playerID <= 0) {
        return INVALID_INPUT;
    }

    Player *player = players->findItem(playerID);
    if (player == NULL) {
        return FAILURE;
    }

    all_game->deletePlayer(player);
    Group *group = groups->Find(player->group_id);
    group->deletePlayer(player);

    players->deleteItem(playerID);

    return SUCCESS;
}

StatusType PlayersManager::increasePlayerIDLevel(int playerID, int levelIncrease) {
    if (playerID <= 0 || levelIncrease <= 0) {
        return INVALID_INPUT;
    }

    Player *player = players->findItem(playerID);
    if (player == NULL) {
        return FAILURE;
    }

    all_game->deletePlayer(player);
    Group *group = groups->Find(player->group_id);
    group->deletePlayer(player);

    player->level += levelIncrease;

    all_game->addPlayer(player);
    group->addPlayer(player);

    return SUCCESS;
}

StatusType PlayersManager::changePlayerIDScore(int playerID, int newScore) {
    if (playerID <= 0 || newScore <= 0 || newScore > scale) {
        return INVALID_INPUT;
    }

    Player *player = players->findItem(playerID);
    if (player == NULL) {
        return FAILURE;
    }

    all_game->deletePlayer(player);
    Group *group = groups->Find(player->group_id);
    group->deletePlayer(player);
    //group->changeScorePlayer(player, newScore);

    player->score = newScore;

    all_game->addPlayer(player);
    group->addPlayer(player);

    return SUCCESS;
}

