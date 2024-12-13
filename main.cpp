#include <iostream>
#include "NoteCollection.h"
#include "Note.h"
using namespace std;

shared_ptr<Note> createNode();
unique_ptr<NoteCollection> createNoteCollection();

int main() {

    const auto collection1 = make_unique<NoteCollection>("Preferiti");
    const auto collection2 = createNoteCollection();
    const auto note1 = createNode();

    collection1->addNote(note1);
    collection2->addNote(note1);
    collection1->getNoteCount();
    collection2->getNoteCount();
    collection1->removeNote(note1->getTitle());
    collection1->getNoteCount();
    collection2->printNote(note1->getTitle());
    return 0;
}

shared_ptr<Note> createNode() {
    string title, content;
    cout << "Insert note title: " << endl;
    getline(cin, title);
    cout << "Insert note content: " << endl;
    getline(cin, content);
    return make_shared<Note>(title, content, false);
}

unique_ptr<NoteCollection> createNoteCollection() {
    string collectionTitle;
    cout << "Insert collection name: " << endl;
    getline(cin, collectionTitle);
    return make_unique<NoteCollection>(collectionTitle);
}
