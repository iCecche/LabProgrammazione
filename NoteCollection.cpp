//
// Created by Alessio Ceccherini on 12/12/24.
//

#include "NoteCollection.h"
#include <iostream>
#include <optional>
#include <cstdlib>
using namespace std;

NoteCollection::NoteCollection(const string &collectionName) {
    this->collectionName = collectionName;
    this->preferredCollectionName = std::getenv("PreferredCollection");
}

void NoteCollection::addNote(const shared_ptr<Note>& newNote, const shared_ptr<NoteCollection>& collection) {
    newNote -> setOwner(collection); // setto me stesso come owner
    this -> collection.push_back(newNote);
    notify();
}

void NoteCollection::removeNote(const int &index, const shared_ptr<NoteCollection>& origin_collection) {

    if (index >= 0 && index < this->collection.size()) {

        auto note = this->collection.at(index);
        if (note -> getLocked() == false) {
            note -> removeOwner(origin_collection);
            this->collection.erase(this->collection.begin() + index);
            cout << note->getTitle() << " è stata rimossa da " << this -> collectionName << endl;
            notify();
        }else {
            cout << note->getTitle() << " è bloccata e non può essere rimossa" << endl;
        }
    }else {
        cout << "La nota non è stata trovata!" << endl;
    }
}

void NoteCollection::moveNote(const int& index,  const shared_ptr<NoteCollection>& origin, const shared_ptr<NoteCollection>& destination) {
    if (index >= 0 && index < this->collection.size()) {
        auto note = this->collection.at(index);
        if (note -> getLocked() == false) {
            bool is_duplicated = destination -> duplicated(note);
            if (destination -> isValidOwner(note) && !is_duplicated) {
                destination -> addNote(note, destination);
            }else {
                if (!is_duplicated && this -> collectionName != preferredCollectionName) {
                    this -> removeNote(index, origin);
                    destination -> addNote(note, destination);
                }else {
                    cout << "La nota è già presente nella collezione!" << endl;
                }
            }
        }else {
            cout << "La nota " << note -> getTitle() << " è bloccata e non può essere mossa!" << endl;
        }
    }else {
        cout << "La nota non è stata trovata!" << endl;
    }
}

void NoteCollection::editNote(const int &index, const optional<string>& newTitle, const optional<string>& newContent) const {

    if (index >= 0 && index < this->collection.size()) {
        auto note = this->collection.at(index);
        if (note -> getLocked() == false) {
            if (newTitle != nullopt) {
                note -> setTitle(*newTitle);
            }
            if (newContent != nullopt) {
                note -> setContent(*newContent);
            }
        }else {
            cout << note -> getContent() << " è bloccata e non può essere modificata" << endl;
        }
    }else {
        cout << "La nota non è stata trovata!" << endl;
    }
}


shared_ptr<Note> NoteCollection::getNote(const int& index) const {

    if (index >= 0 && index < this->collection.size()) {
        return this->collection.at(index);
    }
    return nullptr;
}

void NoteCollection::printNote(const int& index) const {

    if (index >= 0 && index < this->collection.size()) {
        const auto note = this->collection.at(index);
        cout << "Title: " << note->getTitle() << endl;
        cout << "Content: " << note->getContent() << endl;
        cout << "Locked: " << note->getLocked() << endl << endl;
    }
}

void NoteCollection::printAllNotes() const {
    for (int i = 0; i < this->collection.size(); i++) {
        const auto note = this->collection.at(i);
        cout << "Note " << i << ": " << note->getTitle() << endl;
    }
}

unsigned long NoteCollection::getNumberOfNotes() const {
    return this->collection.size();
}

string NoteCollection::getCollectionName() const {
    return this->collectionName;
}

bool NoteCollection::isValidOwner(const shared_ptr<Note> &note) const {
    const auto currentOwners = note -> getOwner();
    if (currentOwners.size() > 1) {
        for (const auto& currentOwner : currentOwners) {
            if (currentOwner.lock() -> getCollectionName() == preferredCollectionName) {
                return false;
            }
        }
    }
    return true;
}

bool NoteCollection::duplicated(const shared_ptr<Note>& newNote) const {
    const auto currentOwners = newNote -> getOwner();
    for (const auto& currentOwner : currentOwners) {
        if (currentOwner.lock() -> getCollectionName() == this -> collectionName) {
            return true;
        }
    }
    return false;
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