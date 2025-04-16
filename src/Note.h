//
// Created by Alessio Ceccherini on 12/12/24.
//

#ifndef NOTE_H
#define NOTE_H
#include <string>
#include <set>
#include "NoteCollection.h"
using namespace std;

class NoteCollection; // Forward declaration perché Note usa weak_ptr<NoteCollection>

class Note {
public:
    Note(const string& title, const string& content, bool locked = false);
    string getTitle() const;
    void setTitle(const string& title);
    string getContent() const;
    void setContent(const string& content);
    bool getLocked() const;
    void setLocked(const bool& locked);
    void setOwner(const shared_ptr<NoteCollection>& collection);
    void removeOwner(const shared_ptr<NoteCollection>& collection);
    vector<weak_ptr<NoteCollection>> getOwner() const;

private:
    string title;
    string content;
    bool locked;
    vector<weak_ptr<NoteCollection>> ownerCollection;
};


#endif //NOTE_H
