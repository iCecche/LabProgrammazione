//
// Created by Alessio Ceccherini on 15/12/24.
//

#ifndef OBSERVER_H
#define OBSERVER_H
#include <string>
using namespace std;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const string& collectionName, const unsigned long& size) = 0;
};



#endif //OBSERVER_H
