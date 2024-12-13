//
// Created by Alessio Ceccherini on 12/12/24.
//

#ifndef NOTECOLLECTION_H
#define NOTECOLLECTION_H
#include "Note.h"
#include <string>
#include <vector>
using namespace std;

class NoteCollection {
    public:
    explicit NoteCollection(const string& collectionName);
    void addNote(const shared_ptr<Note>& newNote);
    void removeNote(const string& title);
    const Note* getNote(const string& title) const;
    void printNote(string title) const;
    void getNoteCount() const;
    private:
    string collectionName;
    vector<shared_ptr<Note>> collection;
};



#endif //NOTECOLLECTION_H
