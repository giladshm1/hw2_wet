//
// Created by gilad on 09/01/2022.
//

#include "Group.h"

Group::Group(int id) : id(id), size_uf(1), counter_level0(0), players_by_level(Player::compareByLevel) {
    level0_score_histogram = new int[max_score];

    for (int i = 0; i < max_score; ++i) {
        arr_score_players_by_level[i] = new AVLTree<Player>(Player::compareByLevel);
        level0_score_histogram[i] = 0;
    }
}

void Group::mergeData(Group *other) {

}

void Group::deletePlayer(Player *player) {
    if (player->level != 0) {
        players_by_level.Remove(player);
        arr_score_players_by_level[player->score]->Remove(player);
    } else {
        counter_level0--;
        level0_score_histogram[player->score]--;
    }
}

void Group::addPlayer(Player *player) {

}