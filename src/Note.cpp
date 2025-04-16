//
// Created by Alessio Ceccherini on 12/12/24.
//

#include "Note.h"
using namespace std;

Note::Note(const string& title, const string& content, const bool locked) {
    this->title = title;
    this->content = content;
    this->locked = locked;
}

void Note::setTitle(const string &title) {
    if (this -> locked == false) {
        this->title = title;
    }
}

string Note::getTitle() const {
    return title;
}

void Note::setContent(const string &content) {
    if (this -> locked == false) {
        this->content = content;
    }
}

string Note::getContent() const{
    return content;
}

void Note::setLocked(const bool& locked) {
    this->locked = locked;
}

bool Note::getLocked() const {
    return locked;
}

void Note::setOwner(const shared_ptr<NoteCollection>& collection) {
    ownerCollection.push_back(collection);
}

void Note::removeOwner(const shared_ptr<NoteCollection> &collection) {
    const auto it = std::find_if(ownerCollection.begin(), ownerCollection.end(),[collection](const weak_ptr<NoteCollection>& member) {
        if (member.lock() == collection) {
            return true;
        }
    });
    ownerCollection.erase(it);
}

vector<weak_ptr<NoteCollection>> Note::getOwner() const {
    return ownerCollection;
}
