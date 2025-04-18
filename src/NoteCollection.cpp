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

void NoteCollection::addNote(const shared_ptr<Note>& newNote) {
    collection.push_back(newNote);
    notify(); // notifica observer del cambiamento
}

void NoteCollection::removeNote(const int &index) {

    if (index >= 0 && index < collection.size()) {

        auto note = collection.at(index);
        if (note -> getLocked() == false) {
            collection.erase(collection.begin() + index);
            notify();
        }else {
            throw std::invalid_argument("La nota è bloccata e non può essere rimossa!");
        }
    }else {
        throw std::out_of_range("La nota non è stata trovata");
    }
}

void NoteCollection::moveNote(const int& index,  const shared_ptr<NoteCollection>& origin, const shared_ptr<NoteCollection>& destination) {
    if (index < 0 || index >= collection.size()) {
        throw std::out_of_range("La nota non è stata trovata");
    }
    auto note = collection.at(index);
    if (note -> getLocked() == true) {
        throw std::invalid_argument("La nota è bloccata e non può essere spostata!");
    }
    const bool is_duplicated = destination -> isDuplicated(note);
    if (destination -> isValidMove(origin) && !is_duplicated) {  // se la collezione di destinazione è valida e la nota non è già al suo interno
        destination -> addNote(note);
    }else {
        if (is_duplicated ) {
            throw std::invalid_argument("La nota è già presente nella collezione!");
        }
        if (collectionName == preferredCollectionName) {  // se la collezione di origine è la Important lancia errore.
            throw std::invalid_argument("Non puoi spostare una nota da questa collezione, ma solo rimuoverla!");
        }
        removeNote(index);  // rimuovi da collezione a cui appartiene
        destination -> addNote(note);  // assegna alla collezione di destinazione
    }
}

void NoteCollection::editNote(const int &index, const optional<string>& newTitle, const optional<string>& newContent) const {

    if (index < 0 || index >= collection.size()) {
        throw std::out_of_range("La nota non è stata trovata");
    }
    auto note = collection.at(index);
    if (note -> getLocked() == true) {
        throw std::invalid_argument("La nota è bloccata e non può essere modificata!");
    }
    if (newTitle != nullopt) {
        note -> setTitle(*newTitle);
    }
    if (newContent != nullopt) {
        note -> setContent(*newContent);
    }
}

void NoteCollection::lockNote(const int &index) const {
    if (index < 0 || index >= collection.size()) {
        throw std::out_of_range("La nota non è stata trovata");
    }

    const auto note = collection.at(index);
    const bool isLocked = note->getLocked();
    note -> setLocked(!isLocked);
    cout << (isLocked ? "Unlocked" : "Locked") << " note " << note -> getTitle() << endl;
}


shared_ptr<Note> NoteCollection::getNote(const int& index) const {

    if (index >= 0 && index < collection.size()) {
        return collection.at(index);
    }
    return nullptr;
}

void NoteCollection::printNote(const int& index) const {
    cout << endl;
    if (index >= 0 && index < collection.size()) {
        const auto note = collection.at(index);
        cout << "Title: " << note->getTitle() << endl;
        cout << "Content: " << note->getContent() << endl;
        cout << "Locked: " << note->getLocked() << endl << endl;
    }else {
        throw std::out_of_range("La nota non è stata trovata");
    }
}

void NoteCollection::printAllNotes() const {
    cout << endl;
    for (int i = 0; i < collection.size(); i++) {
        const auto note = collection.at(i);
        cout << "Note " << i << ": " << note->getTitle() << endl;
    }
}

unsigned long NoteCollection::getNumberOfNotes() const {
    return collection.size();
}

string NoteCollection::getCollectionName() const {
    return collectionName;
}

bool NoteCollection::isValidMove(const shared_ptr<NoteCollection>& origin) const {
    // se origine == important -> no valid move: non si può spostare da important -> solo aggiungere/rimuovere/modificare
    if (origin -> getCollectionName() == preferredCollectionName) {
        return false;
    }

    // se origine != destinazione e se destinazione != important -> necessario prima rimuovere da origin e poi aggiungere a destination -> no valid move
    if (origin -> getCollectionName() != collectionName && collectionName != preferredCollectionName) {
        return false;
    }
    return true;
}

bool NoteCollection::isDuplicated(const shared_ptr<Note>& note) const {
    const auto& it = std::find(collection.begin(), collection.end(), note);
    if (it == collection.end()) {
        return false;
    }
    return true;
}

void NoteCollection::attach(shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void NoteCollection::detach(shared_ptr<Observer> observer) {
    if (const auto& it = find(observers.begin(), observers.end(), observer); it != observers.end()) {
        observers.erase(it);
    }
}

void NoteCollection::notify() {
    for (const auto& observer : observers) {
        observer->update(collectionName, getNumberOfNotes());
    }
}