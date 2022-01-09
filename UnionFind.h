//
// Created by gilad on 07/01/2022.
//

#ifndef HW2_WET_UNIONFIND_H
#define HW2_WET_UNIONFIND_H

#include "Group.h"

class UnionFind {
    int size;
    int *parents;
    Group **pointers;

public:
    explicit UnionFind(int size) : size(size) {
        parents = new int[size];
        pointers = new Group *[size];

        for (int i = 0; i < size; ++i) {
            parents[i] = -1;
            pointers[i] = new Group(i);
        }
    }

    Group *Find(int group_id) {
        if (parents[group_id] == -1) {
            return pointers[group_id];
        }

        Group *res = Find(parents[group_id]);

        if (parents[parents[group_id]] != -1) {
            parents[group_id] = parents[parents[group_id]];
        }

        return res;
    }

    void Union(Group *g1, Group *g2) {
        if (g1 == g2) {
            return;
        }

        if (g1->size_uf < g2->size_uf) {
            parents[g1->id] = g2->id;
            g2->mergeData(g1);
            pointers[g1->id] = NULL;
            delete g1;
        } else {
            parents[g2->id] = g1->id;
            g1->mergeData(g2);
            pointers[g2->id] = NULL;
            delete g2;
        }
    }
};


#endif //HW2_WET_UNIONFIND_H
