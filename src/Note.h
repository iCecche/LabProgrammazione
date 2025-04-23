//
// Created by Alessio Ceccherini on 12/12/24.
//

#ifndef NOTE_H
#define NOTE_H
#include <string>
#include <set>
using namespace std;

class Note {
public:
    Note(const string& title, const string& content, bool locked = false, bool pinned = false);

    string getTitle() const;
    void setTitle(const string& title);

    string getContent() const;
    void setContent(const string& content);

    bool getLocked() const;
    void setLocked(bool locked);

    void setPinned(bool value);
    bool getPinned() const;

private:
    string title;
    string content;
    bool locked;
    bool pinned;
};


#endif //NOTE_H
