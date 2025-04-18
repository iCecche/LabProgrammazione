//
// Created by Alessio Ceccherini on 12/12/24.
//

#include "Note.h"
using namespace std;

Note::Note(const string& title, const string& content, const bool locked, const bool pinned) {
    this->title = title;
    this->content = content;
    this->locked = locked;
    this->pinned = pinned;
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

void Note::setPinned(bool value) {
    this -> pinned = value;
}

bool Note::getPinned() const {
    return pinned;
}

