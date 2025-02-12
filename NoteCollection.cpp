//
// Created by Alessio Ceccherini on 12/12/24.
//

#include "NoteCollection.h"
#include <iostream>
#include <optional>
using namespace std;

NoteCollection::NoteCollection(const string &collectionName) {
    this->collectionName = collectionName;
}

void NoteCollection::addNote(const shared_ptr<Note>& newNote) {
    this->collection.push_back(newNote);
    notify();
}

void NoteCollection::removeNote(const string &title) {
    const auto it = find_if(this->collection.begin(), this->collection.end(), [&title](const auto note) {
        return note->getTitle() == title;
    });

    if (it != this->collection.end()) {
        if (it -> get() -> getLocked() == false) {
            this->collection.erase(it);
            cout << "La nota " << title << " è stata rimossa dalla collezione " << this->collectionName << endl;
            notify();
        } else {
            cout << "La nota " << title << " è bloccata e non può essere cancellata " << endl;
        }
    }else {
        cout << "La nota " << title <<" non è stata trovata!" << endl;
    }
}

void NoteCollection::editNote(const string &title, const optional<string>& newTitle = nullopt, const optional<string>& newContent = nullopt) {
    const auto it = find_if(this->collection.begin(), this->collection.end(), [&title](const auto note) {
        return note->getTitle() == title;
    });

    if (it != this->collection.end()) {
        if (it -> get() -> getLocked() == false) {
            if (newTitle) {
                it -> get() -> setTitle(*newTitle);
            }
            if (newContent) {
                it -> get() -> setContent(*newContent);
            }
        }else {
            cout << title << " è bloccata e non può essere modificata" << endl;
        }
    }
}


const Note* NoteCollection::getNote(const string &title) const {
    const auto it = find_if(this->collection.begin(), this->collection.end(), [&title](const auto note) {
        return note->getTitle() == title;
    });

    if (it != this->collection.end()) {
        return &(**it);
    }
    return nullptr;
}

void NoteCollection::printNote(string title) const {
    const auto it = find_if(this->collection.begin(), this->collection.end(), [&title](const auto note) {
        return note->getTitle() == title;
    });

    if (it != this->collection.end()) {
        cout << "Title: " << it->get()->getTitle() << endl;
        cout << "Content: " << it->get()->getContent() << endl;
        cout << "Locked: " << it->get()->getLocked() << endl << endl;
    }
}

unsigned long NoteCollection::getNumberOfNotes() const {
    return this->collection.size();
}

string NoteCollection::getCollectionName() const {
    return this->collectionName;
}

void NoteCollection::attach(Observer *observer) {
    observers.push_back(observer);
}

void NoteCollection::detach(Observer *observer) {
    if (auto it = find(observers.begin(), observers.end(), observer); it != observers.end()) {
        observers.erase(it);
    }
}

void NoteCollection::notify() {
    for (const auto observer : observers) {
        observer->update(this->collectionName, this->getNumberOfNotes());
    }
}


