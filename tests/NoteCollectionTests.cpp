//
// Created by Alessio Ceccherini on 17/04/25.
//

#include "../src/Note.h"
#include "../src/NoteCollection.h"
#include "gtest/gtest.h"

TEST(NoteCollection, Remove_Note_Unseccessfully) {
    auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
    EXPECT_EQ(noteCollection -> getNote(0), nullptr);

    EXPECT_THROW(noteCollection -> removeNote(0), std::out_of_range);
    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
}

TEST(NoteCollection, Add_Note_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note = make_shared<Note>("Note1", "Content1");
    noteCollection->addNote(note);

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 1);
    EXPECT_NE(noteCollection -> getNote(0), nullptr);
    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), note -> getTitle());
}

TEST(NoteCollection, Add_and_Remove_Note_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note = make_shared<Note>("Note1", "Content1");
    noteCollection -> addNote(note);
    noteCollection -> removeNote(0);

    EXPECT_EQ(noteCollection -> getNumberOfNotes(), 0);
    EXPECT_EQ(noteCollection -> getNote(0), nullptr);
}

TEST(NoteCollection, Edit_Note_Unsuccessfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", true);

    noteCollection->addNote(note1);
    EXPECT_THROW(noteCollection -> editNote(0, "Note4", "Content4"), std::invalid_argument);

    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), "Note1");
    EXPECT_EQ(noteCollection -> getNote(0) -> getContent(), "Content1");

    EXPECT_NE(noteCollection -> getNote(0) -> getTitle(), "Note4");
    EXPECT_NE(noteCollection -> getNote(0) -> getContent(), "Content4");
}

TEST(NoteCollection, Edit_Note_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1");

    noteCollection->addNote(note1);
    noteCollection -> editNote(0, "Note3", "Content3");

    EXPECT_EQ(noteCollection -> getNote(0) -> getTitle(), "Note3");
    EXPECT_EQ(noteCollection -> getNote(0) -> getContent(), "Content3");
}

TEST(NoteCollection, Toggle_Lock_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", false);

    noteCollection -> addNote(note1);

    noteCollection -> lockNote(0);
    EXPECT_EQ(noteCollection -> getNote(0) -> getLocked(), true);
    EXPECT_EQ(note1 -> getLocked(), true);

    noteCollection -> lockNote(0);
    EXPECT_EQ(noteCollection -> getNote(0) -> getLocked(), false);
    EXPECT_EQ(note1 -> getLocked(), false);
}

TEST(NoteCollection, Toggle_Lock_Unsuccessfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", false);

    noteCollection -> addNote(note1);

    EXPECT_THROW(noteCollection -> lockNote(-1), std::out_of_range);
}

TEST(NoteCollection, TogglePin_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", false, false);

    noteCollection -> addNote(note1);

    noteCollection -> pinNote(0);
    EXPECT_EQ(noteCollection -> getNote(0) -> getPinned(), true);

    noteCollection -> pinNote(0);
    EXPECT_EQ(noteCollection -> getNote(0) -> getPinned(), false);
}

TEST(NoteCollection, TogglePin_Unsuccessfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", false, false);

    noteCollection -> addNote(note1);

    EXPECT_THROW(noteCollection -> pinNote(-1), std::out_of_range);
    EXPECT_THROW(noteCollection -> pinNote(1), std::out_of_range);
}

TEST(NoteCollection, Search_Locked_Note_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", false, false);
    const auto note2 = make_shared<Note>("Note2", "Content2", true, false);

    noteCollection -> addNote(note1);
    noteCollection -> addNote(note2);

    const auto result = noteCollection -> searchLocked();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], note2);
}

TEST(NoteCollection, Search_Locked_Note_Unsuccessfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", false, false);
    const auto note2 = make_shared<Note>("Note2", "Content2", false, false);

    noteCollection -> addNote(note1);
    noteCollection -> addNote(note2);

    const auto result = noteCollection -> searchLocked();
    EXPECT_EQ(result.size(), 0);
}

TEST(NoteCollection, Search_Pinned_Note_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", false, false);
    const auto note2 = make_shared<Note>("Note2", "Content2", false, true);

    noteCollection -> addNote(note1);
    noteCollection -> addNote(note2);

    const auto result = noteCollection -> searchPinned();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], note2);
}

TEST(NoteCollection, Search_Pinned_Note_Unsuccessfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "Content1", false, false);
    const auto note2 = make_shared<Note>("Note2", "Content2", false, false);

    noteCollection -> addNote(note1);
    noteCollection -> addNote(note2);

    const auto result = noteCollection -> searchPinned();
    EXPECT_EQ(result.size(), 0);
}

TEST(NoteCollection, Search_Not_Empty_Note_Successfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "", false, false);
    const auto note2 = make_shared<Note>("Note2", "Content2", false, false);

    noteCollection -> addNote(note1);
    noteCollection -> addNote(note2);

    const auto result = noteCollection -> searchNEmpty();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], note2);
}

TEST(NoteCollection, Search_Not_Empty_Note_Unsuccessfully) {
    const auto noteCollection = make_shared<NoteCollection>("NoteCollection1");
    const auto note1 = make_shared<Note>("Note1", "", false, false);
    const auto note2 = make_shared<Note>("Note2", "", false, false);

    noteCollection -> addNote(note1);
    noteCollection -> addNote(note2);

    const auto result = noteCollection -> searchNEmpty();
    EXPECT_EQ(result.size(), 0);
}
