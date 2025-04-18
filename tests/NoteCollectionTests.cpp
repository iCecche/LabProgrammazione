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
