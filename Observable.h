//
// Created by Alessio Ceccherini on 15/12/24.
//

#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"


class Observable {
public:
    virtual ~Observable();
    virtual void attach(Observer *observer) = 0;
    virtual void detach(Observer *observer) = 0;
    virtual void notify() = 0;
};



#endif //SUBJECT_H
