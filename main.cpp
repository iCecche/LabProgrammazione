#include <iostream>
#include "CollectionGroup.h"
#include "NoteCollection.h"
#include "Note.h"
using namespace std;

shared_ptr<Note> createNote();
unique_ptr<NoteCollection> createNoteCollection();

int main() {

    const auto observer = new CollectionGroup();
    const auto collection1 = make_unique<NoteCollection>("Importanti");
    const auto collection2 = createNoteCollection();
    const auto collection3 = createNoteCollection();

    // add collections to observer pattern
    collection1 -> attach(observer);
    collection2 -> attach(observer);
    collection3 -> attach(observer);

    const auto note1 = createNote();
    collection1 -> addNote(note1);
    collection2 -> addNote(note1);
    collection3 -> addNote(note1);

    const auto note2 = createNote();
    collection2 -> addNote(note2);

    const auto note3 = createNote();
    collection3 -> addNote(note3);

    // block notes
    note1 -> setLocked(true);
    note3 -> setLocked(true);

    cout << "PRINT ALL NOTES" << endl << endl;
    // print collections notes
    cout << collection1 -> getCollectionName() << endl;
    collection1 -> printNote(note1 -> getTitle());

    cout << collection2 -> getCollectionName() << endl;
    collection2 -> printNote(note1 -> getTitle());
    collection2 -> printNote(note2 -> getTitle());

    cout << collection3 -> getCollectionName() << endl;
    collection3 -> printNote(note1 -> getTitle());
    collection3 -> printNote(note3 -> getTitle());

    cout << "EDIT NOTES" << endl << endl;

    collection2 -> editNote(note2 -> getTitle(), "New Title", "NewContent");
    collection3 -> editNote(note3 -> getTitle(), "New Title", "NewContent");

    cout << collection2 -> getCollectionName() << endl;
    collection2 -> printNote(note2 -> getTitle());
    cout << collection3 -> getCollectionName() << endl;
    collection3 -> printNote(note3 -> getTitle());

    cout << "DELETE NOTES" << endl << endl;
    // delete notes
    collection1 -> removeNote(note1 -> getTitle());
    collection2 -> removeNote(note1 -> getTitle());
    collection2 -> removeNote(note2 -> getTitle());
    collection3 -> removeNote(note1 -> getTitle());
    collection3 -> removeNote(note3 -> getTitle());

    return 0;
}

shared_ptr<Note> createNote() {
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