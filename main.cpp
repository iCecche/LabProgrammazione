#include <iostream>
#include "CollectionGroup.h"
#include "NoteCollection.h"
#include "Note.h"
#include <string>
using namespace std;

shared_ptr<Note> createNote();
shared_ptr<NoteCollection> createNoteCollection();
int int_prompt(const string& message);
string string_prompt(const string& message);
void PrintCollections(const vector<shared_ptr<NoteCollection>> &collections);

int main() {
    vector<shared_ptr<NoteCollection>> collections;
    const auto observer = new CollectionGroup();

    string collection_name = std::getenv("PreferredCollection");
    auto important_collection = make_shared<NoteCollection>(collection_name);
    important_collection->attach(observer);
    collections.push_back(important_collection);

    bool running = true;
    while (running) {
        cout << "\n---- MENU ----\n";
        cout << "1. Create Collection\n";
        cout << "2. Create Note\n";
        cout << "3. Print Collections\n";
        cout << "4. Print Note\n";
        cout << "5. Edit Note\n";
        cout << "6. Remove Note from Collection\n";
        cout << "7. Lock/Unlock Note\n";
        cout << "8. Move Note\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";

        int choice;
        cin >> choice;
        cin.ignore(); // pulire il buffer

        switch (choice) {
            case 1: {
                auto collection = createNoteCollection();
                collection->attach(observer);
                collections.push_back(collection);
                break;
            }
            case 2: {
                auto note = createNote();
                if (collections.size() == 1) {
                    const auto& collection = collections.at(0);
                    collection -> addNote(note, collection);
                }else {
                    PrintCollections(collections);
                    int collection_index = int_prompt("Select Collection index: ");

                    if (collection_index >= 0 && collection_index < collections.size()) {
                        const auto& collection = collections[collection_index];
                        collection -> addNote(note, collection);
                    }else {
                        cout << "Collection index out of range.\n";
                    }
                }
                break;
            }
            case 3: {
                PrintCollections(collections);
                break;
            }
            case 4: {
                PrintCollections(collections);
                int collection_index = int_prompt("Select Collection index: ");
                if (collection_index >= 0 && collection_index < collections.size()) {
                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes();
                    int node_index = int_prompt("Select Node index: ");
                    collection -> printNote(node_index);
                }
                break;
            }
            case 5: {
                PrintCollections(collections);
                const int collection_index = int_prompt("Select Collection Index: ");
                if (collection_index >= 0 && collection_index < collections.size()) {
                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes();

                    int note_index = int_prompt("Note index: ");
                    string newTitle = string_prompt("New Title: ");
                    string newContent = string_prompt("New Content: ");

                    collection -> editNote(note_index, newTitle, newContent);

                }else {
                    cout << "Invalid Collection Index.\n";
                }
                break;
            }
            case 6: {
                PrintCollections(collections);
                const int collection_index = int_prompt("Collection Index: ");
                if (collection_index >= 0 && collection_index < collections.size()) {
                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes();
                    int note_index = int_prompt("Note index to Remove: ");

                    collection -> removeNote(note_index, collection);
                }
                break;
            }
            case 7: {
                PrintCollections(collections);
                int collection_index = int_prompt("Collection Index: ");
                if (collection_index >= 0 && collection_index < collections.size()) {
                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes();
                    int note_index = int_prompt("Note Index to Lock/Unlock: ");

                    const auto note = collection -> getNote(note_index);
                    const bool lockStatus = note -> getLocked();
                    note -> setLocked(!lockStatus);
                    cout << (lockStatus ? "Unlocked" : "Locked") << " note " << note -> getTitle() << endl;
                }
                break;
            }
            case 8: {
                PrintCollections(collections);
                const int collection_index = int_prompt("Collection Index: ");
                if (collection_index >= 0 && collection_index < collections.size()) {
                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes();
                    int note_index = int_prompt("Note index to Move: ");
                    const int destination_index = int_prompt("Destination Collection Index: ");
                    const auto& destinationCollection = collections[destination_index];
                    collection -> moveNote(note_index, collection, destinationCollection);
                }
                break;
            }
            case 0: {
                running = false;
                cout << "Exiting program.\n";
                break;
            }
            default:
                cout << "Invalid option.\n";
        }
    }
    return 0;
}

int int_prompt(const string& message) {
    int value = 0;
    cout << message;
    cin >> value;
    cin.ignore();
    return value;
}

string string_prompt(const string& message) {
    string value;
    cout << message;
    getline(cin, value);
    return value;
}


void PrintCollections(const vector<shared_ptr<NoteCollection>> &collections) {
    for (int i = 0; i < collections.size(); ++i) {
        cout << "Collection " << i << ": " << collections[i]->getCollectionName() << endl;
    }
}

shared_ptr<Note> createNote() {
    string title = string_prompt("Insert note title: ");
    string content = string_prompt("Insert note content: ");
    return make_shared<Note>(title, content, false);
}

shared_ptr<NoteCollection> createNoteCollection() {
    string collectionTitle = string_prompt("Insert collection name: ");
    return make_shared<NoteCollection>(collectionTitle);
}