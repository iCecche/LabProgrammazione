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
    this->title = title;
}

string Note::getTitle() const {
    return title;
}

void Note::setContent(const string &content) {
    this->content = content;
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

bool Note::operator==(const Note& rightNote) const {
    if (this->title == rightNote.getTitle()) {
        return true;
    }
    return false;
}



