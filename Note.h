//
// Created by Alessio Ceccherini on 12/12/24.
//

#ifndef NOTE_H
#define NOTE_H
#include <string>
using namespace std;

class Note {
public:
    explicit Note(const string& title, const string& content, bool locked = false);

    string getTitle() const;
    void setTitle(const string& title);
    string getContent() const;
    void setContent(const string& content);
    bool getLocked() const;
    void setLocked(const bool& locked);
    bool operator==(const Note&) const;
private:
    string title;
    string content;
    bool locked;
};


#endif //NOTE_H
