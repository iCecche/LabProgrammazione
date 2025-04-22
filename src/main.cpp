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
void print_collections(const vector<shared_ptr<NoteCollection>> &collections, const int &from_index = 0);

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
        cout << "4. Print Note by Index\n";
        cout << "5. Search Note by (condition)\n";
        cout << "6. Edit Note\n";
        cout << "7. Remove Note from Collection\n";
        cout << "8. Lock/Unlock Note\n";
        cout << "9. Pin/Unpin Note\n";
        cout << "10. Move Note\n";
        cout << "0. Exit\n";
        cout << "Select an option: ";

        int choice;
        cin >> choice;
        cin.ignore(); // pulire il buffer

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
                        throw std::runtime_error("Nessuna collezione creata! Creane una prima di aggiungere note!");
                    }

                    print_collections(collections, 1);
                    const int collection_index = int_prompt("Seleziona l'indice della collezione a cui aggiungere la nota: ");

                    if (collection_index < 1 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> addNote(note);
                    break;
                }
                case 3: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    break;
                }
                case 4: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    const int collection_index = int_prompt("Seleziona l'indice della collezione: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes(); // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Seleziona l'indice della note da visualizzare: ");
                    collection -> printNote(note_index);

                    break;
                }
                case 5: {
                    print_collections(collections);
                    const int collection_index = int_prompt("Seleziona l'indice della collezione: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];

                    cout <<endl;
                    cout << "Seleziona la modalità di ricerca da eseguire: " << endl;
                    cout << "1) Locked notes" << endl;
                    cout << "2) Pinned notes" << endl;
                    cout << "3) Not empty content notes" << endl;
                    cout <<endl;

                    const int search_option = int_prompt("Inserisci opzione scelta: ");

                    vector<shared_ptr<Note>> result;
                    switch (search_option) {
                        case 1:
                            result = collection -> searchLocked();
                            collection -> printSearchResult(result);
                            break;
                        case 2:
                            result = collection -> searchPinned();
                            collection -> printSearchResult(result);
                            break;
                        case 3:
                            result = collection -> searchNEmpty();
                            collection -> printSearchResult(result);
                            break;
                        default:
                            throw std::invalid_argument("Invalid search option");
                    }
                    break;
                }
                case 6: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    const int collection_index = int_prompt("Seleziona l'indice della collezione: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes(); // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Inserisci indice della nota da modificare: ");
                    const string new_title = string_prompt("New Title: ");
                    const string new_content = string_prompt("New Content: ");

                    collection -> editNote(note_index, new_title, new_content);
                    break;
                }
                case 7: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    const int collection_index = int_prompt("Seleziona l'indice della collezione: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes(); // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Inserisci indice della nota da rimuovere: ");
                    collection -> removeNote(note_index);
                    break;
                }
                case 8: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    const int collection_index = int_prompt("Seleziona l'indice della collezione: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes();  // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Inserisci indice della nota sui cui eseguire lock/unlock: ");
                    collection -> lockNote(note_index);
                    break;
                }
                case 9: {
                    print_collections(collections);
                    const int collection_index = int_prompt("Seleziona l'indice della collezione: ");
                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];
                    collection -> printAllNotes();

                    const int note_index = int_prompt("Inserisci indice della nota su cui eseguire pin/unpin: ");
                    collection -> pinNote(note_index);
                    break;
                }
                case 10: {
                    print_collections(collections); // visualizza nome collezioni con indice associato
                    const int collection_index = int_prompt("Seleziona l'indice della collezione: ");

                    if (collection_index < 0 || collection_index >= collections.size()) {
                        throw std::out_of_range("Invalid collection index");
                    }

                    const auto& collection = collections[collection_index];

                    collection -> printAllNotes(); // visualizza titolo delle note con indice associato

                    const int note_index = int_prompt("Inserisci indice della nota da spostare: ");
                    const int destination_index = int_prompt("Inserisci indice della collezione di destinazione: ");
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

// indice necessario per non stampare collezione importante tra i possibili owners quando si crea una nuova nota ->
// 'important' non può possedere una nota ma può solo 'ospitarla'
void print_collections(const vector<shared_ptr<NoteCollection>> &collections, const int &from_index) {
    cout << endl;
    for (int i = from_index; i < collections.size(); ++i) {
        cout << i << ") " << collections[i]->getCollectionName() << endl;
    }
}

shared_ptr<Note> create_note() {
    cout << endl;
    string title = string_prompt("Inserisci nome della nota: ");
    string content = string_prompt("Inserisci contenuto della nota: ");
    return make_shared<Note>(title, content, false, false);
}

shared_ptr<NoteCollection> create_note_collection() {
    cout << endl;
    string collection_title = string_prompt("Inserisci nome della collezione: ");
    return make_shared<NoteCollection>(collection_title);
}