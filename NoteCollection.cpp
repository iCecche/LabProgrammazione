//
// Created by Alessio Ceccherini on 12/12/24.
//

#include "NoteCollection.h"
#include <iostream>
using namespace std;

NoteCollection::NoteCollection(const string &collectionName) {
    this->collectionName = collectionName;
}

void NoteCollection::addNote(const shared_ptr<Note>& newNote) {
    this->collection.push_back(newNote);
}

void NoteCollection::removeNote(const string &title) {
    const auto it = find_if(this->collection.begin(), this->collection.end(), [&title](const Note& note) {
        return note.getTitle() == title;
    });

    if (it != this->collection.end() && it->get()->getLocked() == false) {
        this->collection.erase(it);
        cout << this->collectionName << " ha rimosso un elemento" << endl;
    }else {
        cout << title <<" is locked or not found!" << endl;
    }
}

const Note* NoteCollection::getNote(const string &title) const {
    const auto it = find_if(this->collection.begin(), this->collection.end(), [&title](const Note& note) {
        return note.getTitle() == title;
    });

    if (it != this->collection.end()) {
        return &(**it);
    }
    return nullptr;
}

void NoteCollection::printNote(string title) const {
    const auto it = find_if(this->collection.begin(), this->collection.end(), [&title](const Note& note) {
        return note.getTitle() == title;
    });

    if (it != this->collection.end()) {
        cout << "Title: " << it->get()->getTitle() << endl;
        cout << "Content: " << it->get()->getContent() << endl;
        cout << "Locked: " << it->get()->getLocked() << endl;
    }
}


void NoteCollection::getNoteCount() const {
    cout << this-> collectionName << " has " << this->collection.size() << " notes" << endl;
}



