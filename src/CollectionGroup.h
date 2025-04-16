//
// Created by Alessio Ceccherini on 13/12/24.
//

#ifndef COLLECTIONGROUP_H
#define COLLECTIONGROUP_H
#include <iostream>

#include "NoteCollection.h"
#include "Observable.h"
using namespace std;


class CollectionGroup : public Observer {
public:
    ~CollectionGroup() override = default;
    void update(const string& collectionName, const unsigned long& size) override;
};



#endif //COLLECTIONGROUP_H
