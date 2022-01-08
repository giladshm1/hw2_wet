//
// Created by oriya on 05/12/2021.
//

#ifndef WET1_COMPARATOR_H
#define WET1_COMPARATOR_H

template<typename T>
int Compare(T val1, T val2)
{
    if(val1 < val2)
        return -1;
    if(val2 < val1)
        return 1;
    return 0;
}

#endif //WET1_COMPARATOR_H
