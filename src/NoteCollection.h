//
// Created by Alessio Ceccherini on 12/12/24.
//

#ifndef NOTECOLLECTION_H
#define NOTECOLLECTION_H
#include "Note.h"
#include <string>
#include <vector>
#include <set>

#include "Observable.h"
using namespace std;

class NoteCollection final : public Observable {
    public:
    explicit NoteCollection(const string& collectionName);
    ~NoteCollection() override = default;
    void addNote(const shared_ptr<Note> &newNote);
    void removeNote(const int &index);
    void moveNote(const int& index,  const shared_ptr<NoteCollection>& origin, const shared_ptr<NoteCollection>& destination);

    shared_ptr<Note> getNote(const int &index) const;
    void printNote(const int &index) const;
    void printAllNotes() const;

    void editNote(const int &index, const optional<string> &newTitle = nullopt, const optional<string> &newContent = nullopt) const;
    void lockNote(const int &index) const;
    void pinNote(const int &index) const;

    unsigned long getNumberOfNotes() const;
    string getCollectionName() const;

    bool isValidMove(const shared_ptr<NoteCollection> &origin) const;
    bool isDuplicated(const shared_ptr<Note> &note) const;

    vector<shared_ptr<Note>> searchLocked() const;
    vector<shared_ptr<Note>> searchPinned() const;
    vector<shared_ptr<Note>> searchNEmpty() const;

    void printSearchResult(const vector<shared_ptr<Note>> &searchResult) const;

    void attach(shared_ptr<Observer> observer) override;
    void detach(shared_ptr<Observer> observer) override;
    void notify() override;

private:

    vector<shared_ptr<Note>> searchBy(function<bool(const shared_ptr<Note>&)> predicate) const;

    string collectionName;
    vector<shared_ptr<Note>> collection;
    vector<shared_ptr<Observer>> observers;
    string preferredCollectionName;
};



#endif //NOTECOLLECTION_H
