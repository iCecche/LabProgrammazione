#include <iostream>
#include "CollectionGroup.h"
#include "NoteCollection.h"
#include "Note.h"
#include <string>
using namespace std;

shared_ptr<Note> create_note();
shared_ptr<NoteCollection> create_note_collection();
int int_prompt(const string& message);
string string_prompt(const string& message);
void print_collections(const vector<shared_ptr<NoteCollection>> &collections);

int main() {
    vector<shared_ptr<NoteCollection>> collections;
    const auto observer = make_shared<CollectionGroup>();

    string collection_name = std::getenv("PreferredCollection");
    auto important_collection = make_shared<NoteCollection>(collection_name);
    important_collection -> attach(observer);

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
        cout << endl;

        try {
            switch (choice) {
                case 1: {
                    auto collection = create_note_collection();
                    collection -> attach(observer);
                    collections.push_back(collection);
                    break;
                }
                case 2: {
                    auto note = create_note();
                    if (collections.size() == 1) {
                        const auto& collection = collections.at(0);
                        collection -> addNote(note);
                    }else {
                        print_collections(collections);
                        const int collection_index = int_prompt("Select Collection index: ");

                        if (collection_index < 0 || collection_index >= collections.size()) {
                            throw std::out_of_range("Invalid collection index");
                        }

                        const auto& collection = collections[collection_index];
                        collection -> addNote(note);

                    }
                    break;
                }
                case 3: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    break;
                }
                case 4: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    int collection_index = int_prompt("Select Collection index: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes(); // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Select note index: ");
                    collection -> printNote(note_index);

                    break;
                }
                case 5: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    const int collection_index = int_prompt("Select Collection Index: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes(); // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Note index: ");
                    const string new_title = string_prompt("New Title: ");
                    const string new_content = string_prompt("New Content: ");

                    collection -> editNote(note_index, new_title, new_content);
                    break;
                }
                case 6: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    const int collection_index = int_prompt("Collection Index: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes(); // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Note index to Remove: ");
                    collection -> removeNote(note_index);
                    break;
                }
                case 7: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    const int collection_index = int_prompt("Collection Index: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes();  // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Note Index to Lock/Unlock: ");
                    collection -> lockNote(note_index);
                    break;
                }
                case 8: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    const int collection_index = int_prompt("Collection Index: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];

                    collection -> printAllNotes(); // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Note index to Move: ");
                    const int destination_index = int_prompt("Destination Collection Index: ");
                    const auto& destination_collection = collections[destination_index];

                    collection -> moveNote(note_index, collection, destination_collection);
                    break;
                }
                case 0: {
                    running = false;
                    cout << "Exiting program.\n";
                    break;
                }
                default:
                    throw std::invalid_argument("Invalid option");
            }
        }catch (const exception& e) {
            cout << "\033[31m" << "Error: " << e.what()  << "\033[0m" << endl;
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


void print_collections(const vector<shared_ptr<NoteCollection>> &collections) {
    cout << endl;
    for (int i = 0; i < collections.size(); ++i) {
        cout << i << ") " << collections[i]->getCollectionName() << endl;
    }
}

shared_ptr<Note> create_note() {
    string title = string_prompt("Insert note title: ");
    string content = string_prompt("Insert note content: ");
    return make_shared<Note>(title, content, false);
}

shared_ptr<NoteCollection> create_note_collection() {
    string collection_title = string_prompt("Insert collection name: ");
    return make_shared<NoteCollection>(collection_title);
}