//
// Created by Alessio Ceccherini on 15/12/24.
//

#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"


class Observable {
public:
    virtual ~Observable();
    virtual void attach(shared_ptr<Observer> observer) = 0;
    virtual void detach(shared_ptr<Observer> observer) = 0;
    virtual void notify() = 0;
};



#endif //SUBJECT_H
