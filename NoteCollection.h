//
// Created by Alessio Ceccherini on 12/12/24.
//

#ifndef NOTECOLLECTION_H
#define NOTECOLLECTION_H
#include "Note.h"
#include <string>
#include <vector>

#include "Observable.h"
using namespace std;

class NoteCollection : public Observable {
    public:
    explicit NoteCollection(const string& collectionName);
    ~NoteCollection() override = default;
    void addNote(const shared_ptr<Note>& newNote);
    void removeNote(const string& title);
    const Note* getNote(const string& title) const;
    void printNote(string title) const;
    void editNote(const string& title, const optional<string>& newTitle = nullopt, const optional<string>& newContent = nullopt);
    unsigned long getNumberOfNotes() const;
    string getCollectionName() const;
    void attach(Observer *observer) override;
    void detach(Observer *observer) override;
    void notify() override;
    private:
    string collectionName;
    vector<shared_ptr<Note>> collection;
    vector<Observer *> observers;
};



#endif //NOTECOLLECTION_H
